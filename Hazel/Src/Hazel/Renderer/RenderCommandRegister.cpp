#include "hzpch.h"
#include "RenderCommandRegister.h"
#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/UniformBuffer.h"
#include <filesystem>

namespace Hazel
{
	// 对于不同的物体, MVP矩阵里的M都是不同的, 但是VP矩阵都是相同的
	// 所以这里归类在场景信息里
	struct SceneData
	{
		glm::mat4 ViewProjectionMatrix;
	};

	static SceneData s_SceneData;

	// 为了方便更改QuadVertex的数据, 直接设计一个Struct来代表QuadVertex的数据：
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec4 Color;			// 加了个Color
		uint32_t TextureId;
		float TilingFactor = 1.0f;
		int32_t GameObjectInstanceId;
		// TODO: texid, normal,.etc
	};


	// Renderer2D的cpp里
	struct Renderer2DData
	{
		static const uint32_t MaxQuadsCnt = 10000;			// 批处理一次DrawCall绘制的最大Quad个数
		static const uint32_t MaxVerticesCnt = MaxQuadsCnt * 4;
		static const uint32_t MaxIndicesCnt = MaxQuadsCnt * 6;

		const glm::vec4 QuadVertices[4] =
		{
			{ -0.5f, -0.5f, 0.0f, 1.0f },	// 设计成vec4是为了方便矩阵运算, 一定要注意, 点的w为1
			{  0.5f, -0.5f, 0.0f, 1.0f },
			{ -0.5f,  0.5f, 0.0f, 1.0f },
			{  0.5f,  0.5f, 0.0f, 1.0f } 
		};

		const glm::vec2 QuadTexCoords[4]
		{
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f }
		};

		std::shared_ptr<VertexArray> QuadVertexArray;	// 一个Mesh, 代表Quad
		std::shared_ptr<Shader> Shader;
		std::shared_ptr<Texture2D> WhiteTexture;
		std::unique_ptr<QuadVertex[]> Vertices;			// CPU这边用于批处理的临时数组, 用于在每次DrawCall时把Vertex数组数据填充到Vertex Buffer里

		uint32_t DrawedVerticesSize = 0;
		uint32_t DrawedVerticesCnt = 0;
		uint32_t DrawedTrianglesCnt = 0;

		std::unordered_map<std::shared_ptr<Texture2D>, uint32_t> AddedTextures;

		std::shared_ptr<UniformBuffer> CameraUniformBuffer;

		// Debug Stuff
		RenderCommandRegister::Statistics Stats;
	};

	static Renderer2DData s_Data;

	void RenderCommandRegister::Init()
	{
		// 创建Vertex Array前要先创建VertexBuffer和IndexBuffer

		// 1. 创建VertexBuffer
		auto quadVertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(sizeof(QuadVertex) * s_Data.MaxVerticesCnt));
		quadVertexBuffer->Bind();

		// 2. 创建VertexBuffer的Layout，会计算好Stride和Offset
		// 这里的命名其实只是为了Debug看的, 没啥实用性
		BufferLayout layout =
		{
			{ ShaderDataType::FLOAT3, "a_Pos" },
			{ ShaderDataType::FLOAT2, "a_Tex" },
			{ ShaderDataType::FLOAT4, "a_Col" },
			{ ShaderDataType::INT, "a_TexIndex" },
			{ ShaderDataType::FLOAT, "a_TilingFactor" },
			{ ShaderDataType::INT, "a_InstanceId" }
		};

		quadVertexBuffer->SetBufferLayout(layout);

		// 3. 创建Index Buffer
		std::unique_ptr<uint32_t[]> indices = std::make_unique<uint32_t[]>(s_Data.MaxIndicesCnt);
		uint32_t curVertexIndex = 0;
		for (size_t i = 0; i < s_Data.MaxIndicesCnt; i += 6)
		{
			indices[i] = curVertexIndex;
			indices[i + 1] = curVertexIndex + 1;
			indices[i + 2] = curVertexIndex + 2;

			indices[i + 3] = curVertexIndex + 1;
			indices[i + 4] = curVertexIndex + 3;
			indices[i + 5] = curVertexIndex + 2;

			curVertexIndex += 4;// 每经过6个index, 完成一个Quad的绘制, 也就是4个顶点
		}

		// TODO: 如果改成多线程渲染或者单纯放到CommandQueue里, 可能会有问题, 可能出现实际创建Buffer时, indices的内存被释放的情况
		auto quadIndexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(&indices[0], sizeof(uint32_t) * s_Data.MaxIndicesCnt));

		// 4. 创建Vertex Array, 填充VertexBuffer和IndexBuffer
		s_Data.QuadVertexArray.reset(VertexArray::Create());
		s_Data.QuadVertexArray->Bind();
		quadIndexBuffer->Bind();
		s_Data.QuadVertexArray->AddVertexBuffer(quadVertexBuffer);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

		std::string path = std::filesystem::current_path().string();
		std::string shaderPath = std::filesystem::current_path().string() + "\\Resources\\Shader2D.glsl";
		s_Data.Shader = Shader::Create(shaderPath);

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t texIndices[32];
		for (uint32_t i = 0; i < 32; i++)
			texIndices[i] = i;

		s_Data.Shader->Bind();
		s_Data.Shader->UploadUniformIntArr("u_Texture", 32, texIndices);

		s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(glm::mat4), 0);

		s_Data.AddedTextures[s_Data.WhiteTexture] = 0;

		s_Data.Vertices.reset(new QuadVertex[s_Data.MaxVerticesCnt]);// 好像跟shared_ptr的写法不一样, 不能用make_shared
	}

	void RenderCommandRegister::Shutdown()
	{
	}

	void RenderCommandRegister::BeginScene(const EditorCamera & camera)
	{
		s_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();

		s_Data.Shader->Bind();

		// Change from uniform to UniformBuffer
		//s_Data.Shader->UploadUniformMat4("u_ViewProjection", s_SceneData.ViewProjectionMatrix);
		s_Data.CameraUniformBuffer->SetData(glm::value_ptr(s_SceneData.ViewProjectionMatrix), sizeof(s_SceneData.ViewProjectionMatrix), 0);

		// Reset Batch
		ResetBatchParams();

		// Reset Renderer Stats, For Debugging, called only in BeginScene
		s_Data.Stats.DrawCallCnt = 0;
		s_Data.Stats.DrawQuadCnt = 0;

	}

	void RenderCommandRegister::BeginScene(const CameraComponent & camera, const glm::mat4& transform)
	{
		s_SceneData.ViewProjectionMatrix = camera.GetProjectionMatrix() * glm::inverse(transform);

		s_Data.Shader->Bind();

		// Change from uniform to UniformBuffer
		//s_Data.Shader->UploadUniformMat4("u_ViewProjection", s_SceneData.ViewProjectionMatrix);
		s_Data.CameraUniformBuffer->SetData(glm::value_ptr(s_SceneData.ViewProjectionMatrix), sizeof(s_SceneData.ViewProjectionMatrix), 0);

		// Reset Batch
		ResetBatchParams();

		// Reset Renderer Stats, For Debugging, called only in BeginScene
		s_Data.Stats.DrawCallCnt = 0;
		s_Data.Stats.DrawQuadCnt = 0;
	}


	void RenderCommandRegister::EndScene()
	{
		Flush();
	}

	// 这里的position的z值要注意在相机的near和far之间, 比如[-1,1]之间
	void RenderCommandRegister::DrawQuad(const glm::vec3 & globalPos, const glm::vec2 & size, const glm::vec4 & color)
	{
		DrawRotatedQuad2D(globalPos, size, 0.0f, color);
	}

	void RenderCommandRegister::DrawQuad(const glm::vec2 & globalPos, const glm::vec2 & size, const glm::vec4 & color)
	{
		DrawRotatedQuad2D({ globalPos.x, globalPos.y, 0 }, size, 0.0f, color);
	}

	void RenderCommandRegister::DrawQuad(const glm::vec3 & globalPos, const glm::vec2 & size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4 & tintColor)
	{
		DrawRotatedQuad2D(globalPos, size, 0.0f, texture, tilingFactor, tintColor);
	}

	void RenderCommandRegister::DrawQuad(const glm::vec2 & globalPos, const glm::vec2 & size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4 & tintColor)
	{
		DrawRotatedQuad2D({ globalPos.x, globalPos.y, 0.0f }, size, 0.0f, texture, tilingFactor, tintColor);
	}

	void RenderCommandRegister::DrawQuad(const glm::vec3 & globalPos, const glm::vec2 & size, const std::shared_ptr<SubTexture2D>& subTexture, float tilingFactor, const glm::vec4 & tintColor)
	{
		DrawRotatedQuad2D(globalPos, size, 0, subTexture, tilingFactor, tintColor);
	}

	void RenderCommandRegister::DrawSpriteRenderer(const SpriteRenderer & spriteRenderer, const glm::mat4 & transform, const glm::vec4 & tintColor)
	{
		DrawQuad(transform, spriteRenderer.GetColor(), spriteRenderer.InstanceId);
	}

	void RenderCommandRegister::DrawQuad(const glm::vec2& globalPos, const glm::vec2& size, const std::shared_ptr<SubTexture2D>& subTexture, float tilingFactor, const glm::vec4 & tintColor)
	{
		DrawRotatedQuad2D(glm::vec3(globalPos.x, globalPos.y, 0), size, 0, subTexture, tilingFactor, tintColor);
	}

	void RenderCommandRegister::DrawRotatedQuad2D(const glm::vec3 & globalPos, const glm::vec2 & size, float rotatedAngle, const glm::vec4 & color)
	{
		if (s_Data.DrawedVerticesCnt >= s_Data.MaxVerticesCnt)
		{
			ResetBatchParams();
			Flush();
		}

		s_Data.WhiteTexture->Bind(0);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), globalPos) * glm::rotate(glm::mat4(1.0f), rotatedAngle, {0, 0, 1}) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		QuadVertex vertices[4];
		for (size_t i = 0; i < 4; i++)
		{
			vertices[i].Color = color;
			glm::vec4 v0 = transform * s_Data.QuadVertices[i];
			vertices[i].Position = { v0.x, v0.y, v0.z };
			vertices[i].TexCoord = s_Data.QuadTexCoords[i];
			vertices[i].TextureId = 0;
		}

		for (size_t i = s_Data.DrawedVerticesCnt; i < s_Data.DrawedVerticesCnt + 4; i++)
			s_Data.Vertices[i] = vertices[i - s_Data.DrawedVerticesCnt];

		s_Data.DrawedVerticesCnt += 4;
		s_Data.DrawedVerticesSize += sizeof(QuadVertex) * 4;
		s_Data.DrawedTrianglesCnt += 2;

		// Debugging
		s_Data.Stats.DrawQuadCnt++;
	}

	void RenderCommandRegister::DrawRotatedQuad2D(const glm::vec2 & globalPos, const glm::vec2 & size, float rotatedAngle, const glm::vec4 & color)
	{
		DrawRotatedQuad2D({ globalPos.x, globalPos.y, 0 }, size, rotatedAngle, color);
	}
	
	void RenderCommandRegister::DrawRotatedQuad2D(const glm::vec3 & globalPos, const glm::vec2 & size, float rotatedAngle, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		if (s_Data.DrawedVerticesCnt >= s_Data.MaxVerticesCnt)
		{
			Flush();
			ResetBatchParams();
		}

		if (s_Data.AddedTextures.find(texture) == s_Data.AddedTextures.end())
		{
			uint32_t id = (uint32_t)s_Data.AddedTextures.size();
			s_Data.AddedTextures[texture] = id;
		}

		int texId = s_Data.AddedTextures[texture];
		texture->Bind(texId);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), globalPos) * glm::rotate(glm::mat4(1.0f), rotatedAngle, { 0, 0, 1 }) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		QuadVertex vertices[4];
		for (size_t i = 0; i < 4; i++)
		{
			vertices[i].Color = tintColor;
			glm::vec4 v0 = transform * s_Data.QuadVertices[i];// 一定要注意, 点的w为1
			vertices[i].Position = { v0.x, v0.y, v0.z };
			vertices[i].TexCoord = s_Data.QuadTexCoords[i];
			vertices[i].TextureId = texId;
			vertices[i].TilingFactor = tilingFactor;
		}

		for (size_t i = s_Data.DrawedVerticesCnt; i < s_Data.DrawedVerticesCnt + 4; i++)
			s_Data.Vertices[i] = vertices[i - s_Data.DrawedVerticesCnt];

		s_Data.DrawedVerticesCnt += 4;
		s_Data.DrawedVerticesSize += sizeof(QuadVertex) * 4;
		s_Data.DrawedTrianglesCnt += 2;

		// Debugging
		s_Data.Stats.DrawQuadCnt++;
	}

	RenderCommandRegister::Statistics RenderCommandRegister::GetStatistics()
	{
		return s_Data.Stats;
	}

	void RenderCommandRegister::Flush()
	{
		s_Data.QuadVertexArray->GetVertexBuffers()[0]->SetData(0, &s_Data.Vertices[0],
			s_Data.DrawedVerticesSize);

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.DrawedTrianglesCnt * 3);
		s_Data.Stats.DrawCallCnt++;
	}

	// 在每次的批处理完成绘制后, 调用此函数
	void RenderCommandRegister::ResetBatchParams()
	{
		s_Data.DrawedVerticesSize = 0;
		s_Data.DrawedTrianglesCnt = 0;
		s_Data.DrawedVerticesCnt = 0;
		s_Data.AddedTextures.clear();
		s_Data.AddedTextures[s_Data.WhiteTexture] = 0;
	}

	void RenderCommandRegister::DrawRotatedQuad2D(const glm::vec2& globalPos, const glm::vec2& size, float rotatedAngle, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad2D(glm::vec3(globalPos.x, globalPos.y, 0), size, rotatedAngle, texture, tilingFactor, tintColor);
	}

	void RenderCommandRegister::DrawRotatedQuad2D(const glm::vec2& globalPos, const glm::vec2& size, float rotatedAngle, const std::shared_ptr<SubTexture2D>& subTexture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad2D(glm::vec3(globalPos.x, globalPos.y, 0), size, rotatedAngle, subTexture, tilingFactor, tintColor);
	}

	void RenderCommandRegister::DrawRotatedQuad2D(const glm::vec3& globalPos, const glm::vec2& size, float rotatedAngle, const std::shared_ptr<SubTexture2D>& subTexture, float tilingFactor, const glm::vec4& tintColor)
	{
		if (s_Data.DrawedVerticesCnt >= s_Data.MaxVerticesCnt)
		{
			Flush();
			ResetBatchParams();
		}

		auto& atlas = subTexture->GetTextureAtlas();
		if (s_Data.AddedTextures.find(atlas) == s_Data.AddedTextures.end())
		{
			uint32_t id = (uint32_t)s_Data.AddedTextures.size();
			s_Data.AddedTextures[atlas] = id;
		}

		int texId = s_Data.AddedTextures[atlas];
		atlas->Bind(texId);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), globalPos) * glm::rotate(glm::mat4(1.0f), rotatedAngle, { 0, 0, 1 }) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		QuadVertex vertices[4];
		for (size_t i = 0; i < 4; i++)
		{
			vertices[i].Color = tintColor;
			glm::vec4 v0 = transform * s_Data.QuadVertices[i];// 一定要注意, 点的w为1
			vertices[i].Position = { v0.x, v0.y, v0.z };
			vertices[i].TexCoord = subTexture->GetTexCoords()[i];
			vertices[i].TextureId = texId;
			vertices[i].TilingFactor = tilingFactor;
		}

		for (size_t i = s_Data.DrawedVerticesCnt; i < s_Data.DrawedVerticesCnt + 4; i++)
			s_Data.Vertices[i] = vertices[i - s_Data.DrawedVerticesCnt];

		s_Data.DrawedVerticesCnt += 4;
		s_Data.DrawedVerticesSize += sizeof(QuadVertex) * 4;
		s_Data.DrawedTrianglesCnt += 2;

		// Debugging
		s_Data.Stats.DrawQuadCnt++;
	}

	void RenderCommandRegister::DrawQuad(const glm::mat4& transform, const glm::vec4& color, uint32_t goId)
	{
		if (s_Data.DrawedVerticesCnt >= s_Data.MaxVerticesCnt)
		{
			ResetBatchParams();
			Flush();
		}

		s_Data.WhiteTexture->Bind(0);

		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), globalPos) * glm::rotate(glm::mat4(1.0f), rotatedAngle, { 0, 0, 1 }) *
		//	glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		QuadVertex vertices[4];
		for (size_t i = 0; i < 4; i++)
		{
			vertices[i].Color = color;
			glm::vec4 v0 = transform * s_Data.QuadVertices[i];
			vertices[i].Position = { v0.x, v0.y, v0.z };
			vertices[i].TexCoord = s_Data.QuadTexCoords[i];
			vertices[i].TextureId = 0;
			vertices[i].GameObjectInstanceId = goId;
		}

		for (size_t i = s_Data.DrawedVerticesCnt; i < s_Data.DrawedVerticesCnt + 4; i++)
			s_Data.Vertices[i] = vertices[i - s_Data.DrawedVerticesCnt];

		s_Data.DrawedVerticesCnt += 4;
		s_Data.DrawedVerticesSize += sizeof(QuadVertex) * 4;
		s_Data.DrawedTrianglesCnt += 2;

		// Debugging
		s_Data.Stats.DrawQuadCnt++;
	}
}
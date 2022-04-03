#include "hzpch.h"
#include "Renderer2D.h"
#include "Hazel/Renderer/RenderCommand.h"
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

	// Renderer2D的cpp里
	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;			// 批处理一次DrawCall绘制的最大Quad个数
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		std::shared_ptr<VertexArray> QuadVertexArray;		// 一个Mesh, 代表Quad
		std::shared_ptr<Shader> Shader;
		std::shared_ptr<Texture2D> WhiteTexture;

		uint32_t* VertexBufferBaseP = nullptr;
		uint32_t* VertexBufferPtr = nullptr;
		uint32_t DrawedVerticesSize = 0;
		uint32_t DrawedTrianglesCnt = 0;
	};

	static Renderer2DData s_Data;

	// 为了方便更改QuadVertex的数据, 直接设计一个Struct来代表QuadVertex的数据：
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec4 Color;			// 加了个Color
		// TODO: texid, normal,.etc
	};

	void Renderer2D::Init()
	{
		// 创建Vertex Array前要先创建VertexBuffer和IndexBuffer

		// 1. 创建VertexBuffer
		auto quadVertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(sizeof(QuadVertex) * s_Data.MaxVertices));
		quadVertexBuffer->Bind();

		// 2. 创建VertexBuffer的Layout，会计算好Stride和Offset
		BufferLayout layout =
		{
			{ ShaderDataType::FLOAT3, "a_Pos" },
			{ ShaderDataType::FLOAT2, "a_Tex" },
			{ ShaderDataType::FLOAT4, "a_Col" }
		};

		quadVertexBuffer->SetBufferLayout(layout);

		// 3. 创建Index Buffer
		std::unique_ptr<uint32_t[]> indices = std::make_unique<uint32_t[]>(s_Data.MaxIndices);
		uint32_t curVertexIndex = 0;
		for (size_t i = 0; i < s_Data.MaxIndices; i += 6)
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
		auto quadIndexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(&indices[0], sizeof(uint32_t) * s_Data.MaxIndices));

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

		s_Data.Shader->UploadUniformI1("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera & camera)
	{
		s_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();

		s_Data.Shader->Bind();
		s_Data.Shader->UploadUniformMat4("u_ViewProjection", s_SceneData.ViewProjectionMatrix);

		s_Data.DrawedVerticesSize = 0;
		s_Data.DrawedTrianglesCnt = 0;
	}

	void Renderer2D::EndScene()
	{
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.DrawedTrianglesCnt * 3);
	}

	// 这里的position的z值要注意在相机的near和far之间, 比如[-1,1]之间
	void Renderer2D::DrawQuad(const glm::vec3 & globalPos, const glm::vec2 & size, const glm::vec4 & color)
	{
		s_Data.WhiteTexture->Bind(0);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), globalPos) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		QuadVertex vertices[4];
		// -0.5f, -0.5f, 0, 0.0f, 0.0f,
		//	0.5f, -0.5f, 0, 1.0f, 0.0f,
		//	-0.5f, 0.5f, 0, 0.0f, 1.0f,
		//	0.5f, 0.5f, 0, 1.0f, 1.0f
		vertices[0].Color = color;
		glm::vec4 v0 = transform * glm::vec4{ -0.5f, -0.5f , 0, 1 };// 一定要注意, 点的w为1
		vertices[0].Position = { v0.x, v0.y, v0.z };
		vertices[0].TexCoord = { 0.0f, 0.0f };

		vertices[1].Color = color;
		glm::vec4 v1 = transform * glm::vec4{ 0.5f, -0.5f , 0, 1 };
		vertices[1].Position = { v1.x, v1.y, v1.z };
		vertices[1].TexCoord = { 1.0f, 0.0f };

		vertices[2].Color = color;
		glm::vec4 v2 = transform * glm::vec4{ -0.5f, 0.5f , 0, 1 };
		vertices[2].Position = { v2.x, v2.y, v2.z };
		vertices[2].TexCoord = { 0.0f, 1.0f };

		vertices[3].Color = color;
		glm::vec4 v3 = transform * glm::vec4{ 0.5f, 0.5f , 0, 1 };
		vertices[3].Position = { v3.x, v3.y, v3.z };
		vertices[3].TexCoord = { 1.0f, 1.0f };

		// 添加4个顶点的Vertex数据
		s_Data.QuadVertexArray->GetVertexBuffers()[0]->SetData(s_Data.DrawedVerticesSize, &vertices,
			sizeof(QuadVertex) * 4);

		s_Data.DrawedVerticesSize += sizeof(QuadVertex) * 4;
		s_Data.DrawedTrianglesCnt += 2;
	}

	void Renderer2D::DrawQuad(const glm::vec2 & globalPos, const glm::vec2 & size, const glm::vec4 & color)
	{
		DrawQuad({ globalPos.x, globalPos.y, 0 }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3 & globalPos, const glm::vec2 & size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4 & tintColor)
	{
	//	//Texture绑定到0号槽位即可, shader里面自然会去读取对应的shader
	//	texture->Bind(0);
	//	s_Data.Shader->UploadUniformVec4("u_Color", tintColor);

	//	glm::mat4 transform = glm::translate(glm::mat4(1.0f), globalPos) *
	//		glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
	//	s_Data.Shader->UploadUniformMat4("u_Transform", transform);

	//	s_Data.Shader->UploadUniformF1("u_TilingFactor", tilingFactor);

	//	RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2 & position, const glm::vec2 & size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4 & tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3 & globalPos, const glm::vec2 & size, float rotatedAngle, const glm::vec4 & color)
	{
		s_Data.Shader->UploadUniformVec4("u_Color", color);
		s_Data.WhiteTexture->Bind(0);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), globalPos) * 
			glm::rotate(glm::mat4(1.0f),glm::radians(rotatedAngle), { 0, 0, 1 }) * 
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));


		QuadVertex vertices[4];
		vertices[0].Color = color;
		// -0.5f, -0.5f, 0, 0.0f, 0.0f,
		//	0.5f, -0.5f, 0, 1.0f, 0.0f,
		//	-0.5f, 0.5f, 0, 0.0f, 1.0f,
		//	0.5f, 0.5f, 0, 1.0f, 1.0f
		glm::vec4 v0 = transform * glm::vec4{ -0.5f, -0.5f , 0, 0 };
		vertices[0].Position = { v0.x, v0.y, v0.z };
		vertices[0].TexCoord = { 0.0f, 0.0f };

		vertices[1].Color = color;
		glm::vec4 v1 = transform * glm::vec4{ 0.5f, -0.5f , 0, 0 };
		vertices[1].Position = { v1.x, v1.y, v1.z };
		vertices[1].TexCoord = { 1.0f, 0.0f };

		vertices[2].Color = color;
		glm::vec4 v2 = transform * glm::vec4{ -0.5f, 0.5f , 0, 0 };
		vertices[2].Position = { v2.x, v2.y, v2.z };
		vertices[2].TexCoord = { 0.0f, 1.0f };

		vertices[3].Color = color;
		glm::vec4 v3 = transform * glm::vec4{ 0.5f, 0.5f , 0, 0 };
		vertices[3].Position = { v3.x, v3.y, v3.z };
		vertices[3].TexCoord = { 1.0f, 1.0f };

		// 添加4个顶点的Vertex数据
		s_Data.QuadVertexArray->GetVertexBuffers()[0]->SetData(s_Data.DrawedVerticesSize, &vertices,
			sizeof(QuadVertex) * 4);

		s_Data.DrawedVerticesSize += sizeof(QuadVertex) * 4;
		s_Data.DrawedTrianglesCnt += 2;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2 & globalPos, const glm::vec2 & size, float rotatedAngle, const glm::vec4 & color)
	{
		DrawRotatedQuad({ globalPos.x, globalPos.y, 0 }, size, rotatedAngle, color);
	}
	
	void Renderer2D::DrawRotatedQuad(const glm::vec3 & globalPos, const glm::vec2 & size, float rotatedAngle, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		////Texture绑定到0号槽位即可, shader里面自然会去读取对应的shader
		//texture->Bind(0);
		//s_Data.Shader->UploadUniformVec4("u_Color", tintColor);

		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), globalPos) *
		//	glm::rotate(glm::mat4(1.0f), glm::radians(rotatedAngle), { 0, 0, 1 }) *
		//	glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		//s_Data.Shader->UploadUniformMat4("u_Transform", transform);

		//s_Data.Shader->UploadUniformF1("u_TilingFactor", tilingFactor);

		//RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& globalPos, const glm::vec2& size, float rotatedAngle, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad(glm::vec3(globalPos.x, globalPos.y, 0), size, rotatedAngle, texture, tilingFactor, tintColor);
	}
}
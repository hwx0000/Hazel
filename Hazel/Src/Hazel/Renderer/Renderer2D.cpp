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

	static SceneData* s_SceneData;


	// Renderer2D的cpp里
	struct Renderer2DStorage
	{
		std::shared_ptr<VertexArray> QuadVertexArray;		// 一个Mesh, 代表Quad
		std::shared_ptr<Shader> FlatColorShader;			// 两个Shader
		std::shared_ptr<Shader> TextureShader;
		std::shared_ptr<Texture2D> WhiteTexture;			// 一个默认贴图, 用于Blend等
	};

	// 定义静态的Data, 这种static对象是不是不方便用shared_ptr?
	// 顺便问一句, shared_ptr是不是不适合用在static对象上
	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_SceneData = new SceneData();
		s_Data = new Renderer2DStorage();

		// 创建Vertex Array前要先创建VBO和EBO
		
		// 创建VBO
		float quadVertices[] =
		{
			-0.5f, -0.5f, 0, 0.0f, 0.0f,
			 0.5f, -0.5f, 0, 1.0f, 0.0f,
			-0.5f,  0.5f, 0, 0.0f, 1.0f,
			 0.5f,  0.5f, 0, 1.0f, 1.0f
		};

		auto quadVertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
		quadVertexBuffer->Bind();

		// 创建Layout，会计算好Stride和Offset
		BufferLayout layout =
		{
			{ ShaderDataType::FLOAT3, "a_Pos" },
			{ ShaderDataType::FLOAT2, "a_Tex" }
		};

		quadVertexBuffer->SetBufferLayout(layout);

		// 创建EBO
		int quadIndices[] = { 0,1,2,2,1,3 };
		auto quadIndexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(quadIndices, sizeof(quadIndices)));


		// 创建Vertex Array
		s_Data->QuadVertexArray.reset(VertexArray::Create());
		s_Data->QuadVertexArray->Bind();
		quadIndexBuffer->Bind();
		s_Data->QuadVertexArray->AddVertexBuffer(quadVertexBuffer);
		s_Data->QuadVertexArray->SetIndexBuffer(quadIndexBuffer);


		std::string path = std::filesystem::current_path().string();
		std::string shaderPath1 = std::filesystem::current_path().string() + "\\Resources\\FlatColorShader.glsl";
		s_Data->FlatColorShader = Shader::Create(shaderPath1);
	}

	void Renderer2D::Shutdown()
	{
		delete s_SceneData;
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera & camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2 & position, const glm::vec2 & size, const glm::vec4 & color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		s_Data->FlatColorShader->UploadUniformVec4("u_Color", color);
		glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		transform = glm::translate(transform, position);

		s_Data->FlatColorShader->UploadUniformMat4("u_Transform", transform);
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, std::shared_ptr<Texture> tex)
	{
		//Texture绑定到0号槽位即可, shader里面自然会去读取对应的shader
		tex->Bind(0);		
		s_Data->TextureShader->Bind();

		s_Data->TextureShader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		transform = glm::translate(transform, position);

		s_Data->TextureShader->UploadUniformMat4("u_Transform", transform);
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, std::shared_ptr<Texture> tex)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0), size, tex);
	}
}
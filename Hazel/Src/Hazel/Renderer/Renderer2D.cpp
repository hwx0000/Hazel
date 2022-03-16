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
		std::shared_ptr<Shader> Shader;
		std::shared_ptr<Texture2D> WhiteTexture;			
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
		std::string shaderPath = std::filesystem::current_path().string() + "\\Resources\\Shader2D.glsl";
		s_Data->Shader = Shader::Create(shaderPath);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		void* s = (void*)new int[1]{ (int)0xffffffff };
		uint32_t whiteTextureData = 0xffffffff;
		//s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->Shader->UploadUniformI1("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_SceneData;
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera & camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

		s_Data->Shader->Bind();
		s_Data->Shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
	}

	void Renderer2D::EndScene()
	{
	}

	// 这里的position的z值好像要在0到1之间
	void Renderer2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color)
	{
		s_Data->Shader->UploadUniformVec4("u_Color", color);
		s_Data->WhiteTexture->Bind(0);

		glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		transform = glm::translate(transform, position);
		s_Data->Shader->UploadUniformMat4("u_Transform", transform);

		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, std::shared_ptr<Texture> tex)
	{
		//Texture绑定到0号槽位即可, shader里面自然会去读取对应的shader
		tex->Bind(0);		
		s_Data->Shader->UploadUniformVec4("u_Color", { 1.0f, 1.0f, 1.0f, 1.0f });
		glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		transform = glm::translate(transform, position);

		s_Data->Shader->UploadUniformMat4("u_Transform", transform);
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, std::shared_ptr<Texture> tex)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0), size, tex);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0), size, color);
	}
}
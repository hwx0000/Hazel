#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"
#include <memory>
#include "glm/glm.hpp"
#include "OrthographicCamera.h"
#include "Shader.h"


namespace Hazel
{
	class Renderer
	{
	public:
		static inline RendererAPI::APIType GetAPI() { return RendererAPI::GetAPIType(); }

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		// �󶨶�Ӧ��VertexArray, Ȼ�����DrawCall
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
	private:
		// ���ڲ�ͬ������, MVP�������M���ǲ�ͬ��, ����VP��������ͬ��
		// ������������ڳ�����Ϣ��
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}

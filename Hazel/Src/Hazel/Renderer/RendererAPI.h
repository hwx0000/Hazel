#pragma once
#include "glm/glm.hpp"
#include "Hazel/Renderer/VertexArray.h"

namespace Hazel
{
	class RendererAPI
	{
	public:
		enum class APIType
		{
			None = 0, OpenGL//������ټ�
		};
	public:
		// ����ش����������������ӿڣ�����RenderAPI����, ��Щ���ǳ���ӿ�, �����ͨ������һ����ƽ̨��ص������
		// RendererAPI�ľ�̬����, ����OpenGLRenderer, Ȼ���RenderCommand��Ϊһ��Wrapper, ����ӿڱ�¶����
		virtual void Clear() const = 0;
		virtual void SetClearColor(const glm::vec4&) const = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) const = 0;

		inline static APIType GetAPIType() { return s_CurType; }
	private:
		static APIType s_CurType;
	};
}
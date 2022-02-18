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
			None = 0, OpenGL//后面会再加
		};
	public:
		// 把相关代码抽象成以下三个接口，放在RenderAPI类里, 这些都是抽象接口, 具体会通过创建一个与平台相关的子类的
		// RendererAPI的静态对象, 比如OpenGLRenderer, 然后把RenderCommand作为一个Wrapper, 将其接口暴露出来
		virtual void Init() const = 0;
		virtual void Clear() const = 0;
		virtual void SetClearColor(const glm::vec4&) const = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) const = 0;

		inline static APIType GetAPIType() { return s_CurType; }
	private:
		static APIType s_CurType;
	};
}
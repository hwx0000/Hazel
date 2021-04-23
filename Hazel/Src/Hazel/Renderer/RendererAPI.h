#pragma once
#include "glm/glm.hpp"
#include "Hazel/Renderer/VertexArray.h"

class RendererAPI
{
public:
	enum class APIType
	{
		None = 0, OpenGL//后面会再加
	};
public:
	// 把相关代码抽象成以下三个接口，放在RenderAPI类里
	virtual void Clear() const = 0;
	virtual void SetClearColor(const glm::vec4&) const = 0;
	virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) const = 0;

	inline static APIType GetAPIType() { return s_CurType; }
private:
	static APIType s_CurType;
};
#pragma once

class RendererAPI
{
public:
	enum class APIType
	{
		None = 0, OpenGL//后面会再加
	};
public:

	inline static APIType GetAPIType() { return s_CurType; }
private:
	static APIType s_CurType;
};
#pragma once

enum class RendererAPI 
{
	None = 0, OpenGL//������ټ�
};

class Renderer
{
public:
	static inline RendererAPI GetAPI() /*const*/{ return m_RendererAPI; }
private:
	static RendererAPI m_RendererAPI;
};

#include "hzpch.h"
#include "Renderer.h"

//这个参数可以在Runtime更改的，只要提供SetAPI函数就可以了
RendererAPI Renderer::m_RendererAPI = RendererAPI::OpenGL;


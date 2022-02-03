#include "hzpch.h"
#include "RendererAPI.h"

//这个参数可以在Runtime更改的，只要提供SetAPI函数就可以了
Hazel::RendererAPI::APIType Hazel::RendererAPI::s_CurType = RendererAPI::APIType::OpenGL;
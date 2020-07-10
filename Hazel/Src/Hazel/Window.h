#pragma once
#include "Core.h"

class HAZEL_API Window
{
public:
	virtual ~Window() {};
	virtual float const& GetWindowHeight() = 0;
	virtual float const& GetWindowWidth() = 0;


private:
	float m_width;
	float m_height;

};
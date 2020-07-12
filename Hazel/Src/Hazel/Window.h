#pragma once
#include "Core.h"

class HAZEL_API Window
{
public:
	virtual ~Window() {};
	virtual float const& GetWindowHeight() const = 0;
	virtual float const& GetWindowWidth() const = 0;
	virtual int GetVsync() const = 0;
	virtual void SetVsync(int) = 0;

private:
	float m_width;
	float m_height;

};
#pragma once
#include "hzpch.h"
#include "Hazel/Core.h"


class HAZEL_API Layer
{
public:
	virtual void OnEvent() = 0;
	virtual void OnUpdate() = 0;

protected:
	std::string m_DebugName;
};


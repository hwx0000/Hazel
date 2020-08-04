#pragma once
#include "hzpch.h"
#include "Hazel/Core.h"


class HAZEL_API Layer
{
public:
	virtual void OnAttach() = 0; //当layer添加到layer stack的时候会调用此函数，相当于Init函数
	virtual void OnDettach() = 0; //当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
	virtual void OnEvent() = 0;
	virtual void OnUpdate() = 0;

protected:
	bool isEnabled;	// 值为fasle时，该Layer会被禁用，不会绘制画面，也不会接收事件
	std::string m_DebugName;
};


#pragma once
#include "hzpch.h"
#include "Hazel/Core.h"


class HAZEL_API Layer
{
public:
	virtual void OnAttach() = 0; //��layer��ӵ�layer stack��ʱ�����ô˺������൱��Init����
	virtual void OnDettach() = 0; //��layer��layer stack�Ƴ���ʱ�����ô˺������൱��Shutdown����
	virtual void OnEvent() = 0;
	virtual void OnUpdate() = 0;

protected:
	bool isEnabled;	// ֵΪfasleʱ����Layer�ᱻ���ã�������ƻ��棬Ҳ��������¼�
	std::string m_DebugName;
};


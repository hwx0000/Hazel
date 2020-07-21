#include "Hazel.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox(){};
	~Sandbox(){};
private:
};

Hazel::Application* Hazel::CreateApplication() 
{
	Sandbox *s = new Sandbox();
	return s;
}

//int main()
//{
//	CreateApplication();
//	return 0;
//}

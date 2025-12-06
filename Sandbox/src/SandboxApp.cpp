#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		HZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hazel::Event& event) override
	{
		HZ_TRACE("{0}", event.ToString());
	}

};

class SandboxApp : public Hazel::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
	}
	~SandboxApp()
	{
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new SandboxApp();
}
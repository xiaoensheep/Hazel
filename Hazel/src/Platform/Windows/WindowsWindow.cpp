#include "hzpch.h"
#include "WindowsWindow.h"

namespace Hazel {

	static bool s_GLFWInitialzed = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("创建窗口{0}中 ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialzed)
		{
			//TODO: glfwTerminate on system shutdow
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "未能初始化GLFW!");

			s_GLFWInitialzed = true;
		}
		
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		/*作用：告诉 OpenGL 当前线程要在这个窗口的上下文中渲染
			GLFW 允许你创建多个窗口，每个窗口都有自己的 OpenGL 上下文
			必须在调用任何 OpenGL 渲染函数前，先设置当前上下文*/
		glfwMakeContextCurrent(m_Window);
	/*	作用：把 m_Data 结构体的指针绑定到 GLFW 窗口对象上
			好处：
			GLFW 回调（比如键盘、鼠标事件）会传入 GLFWwindow* window
			可以通过 glfwGetWindowUserPointer(window) 获取对应窗口的 WindowData*
			实现了 事件回调和窗口状态的关联，不用全局变量*/
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();		//处理 所有挂起的窗口事件
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		//设置 垂直同步 (VSync) 间隔
		if (enabled)
			glfwSwapInterval(1);		//每刷新一次屏幕就交换缓冲区
		else
			glfwSwapInterval(0);		//禁用 VSync（尽可能快刷新，不等待屏幕

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
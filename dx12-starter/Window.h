#pragma once
#include <GLFW/glfw3.h>
#include <iostream>


class Window
{
public:
	Window();
	bool Init();
	void Terminate();

	GLFWwindow* m_window = nullptr;
};


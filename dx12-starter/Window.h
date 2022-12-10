#pragma once
#include <GLFW/glfw3.h>
#include <iostream>


class Window
{
public:
	Window();
	bool Init();
	void Terminate();
	void Update();
	bool ShouldLoop();
	void HandleResize(GLFWwindow* window, int width, int height);
	
	int32_t m_width = 0;
	int32_t m_height = 0;
	GLFWwindow* m_window = nullptr;
};


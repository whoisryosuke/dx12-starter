#pragma once
#include "Window.h"
#include "UI.h"
#include "Renderer.h"

/// <summary>
/// The root application code. Opens a native window and runs DX12 renderer.
/// </summary>
class App
{
	public:
	App();
	void Run();
	static void HandleResizeCallback(GLFWwindow* window, int width, int height);

protected:
	bool Init();
	void Render();
	void Update();
	void Exit();
	void HandleResize(int width, int height);
	Window* m_window_container = nullptr;
	DX12Playground::UI* m_ui = nullptr;
	Renderer* m_renderer = nullptr;


};


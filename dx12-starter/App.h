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


protected:
	bool Init();
	void Render();
	void Update();
	void Exit();
	Window* m_window_container = nullptr;
	DX12Playground::UI* m_ui = nullptr;
	Renderer* m_renderer = nullptr;


};


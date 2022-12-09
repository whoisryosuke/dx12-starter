#include "App.h"

App::App()
{
    // Create any new classes
    m_window_container = new Window();
}

/// <summary>
/// Opens a native window and runs DX12 renderer.
/// </summary>
void App::Run()
{
    // Initialize anything
    if (!Init()) {
        return;
    }

    // The app loop
    while (!glfwWindowShouldClose(m_window_container->m_window))
    {
        glfwPollEvents();
        
        // Run any updates before rendering
        Update();

        // Render the 3D!
        Render();
    }
}

bool App::Init()
{
    // Initalize the window here and hydrate 
    m_window_container->Init();
	return true;
}

void App::Render()
{
}

void App::Update()
{
}

void App::Exit()
{
    m_window_container->Terminate();
}

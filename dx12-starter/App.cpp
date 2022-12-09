#include "App.h"

App::App()
{
    // Create any new classes
    m_window_container = new Window();
    m_ui = new DX12Playground::UI();
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

    // Initialize the UI (aka imgui). Requires the window context.
    // TODO: Implement DX12 first - since imgui requires device + descriptor heap
    //m_ui->Init(m_window_container->m_window);

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

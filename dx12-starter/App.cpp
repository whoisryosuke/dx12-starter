#include "App.h"

App::App()
{
    // Create any new classes
    m_window_container = new Window();
    m_ui = new DX12Playground::UI();
    m_renderer = new Renderer();
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

    // Get HWND context from window - required for DX12 and imgui
    // Get application window
    // @see: https://www.glfw.org/docs/3.3/group__native.html#gafe5079aa79038b0079fc09d5f0a8e667
    HWND hwnd = glfwGetWin32Window(m_window_container->m_window);

    m_renderer->Init(hwnd);

    // Initialize the UI (aka imgui). Requires the window context.
    // TODO: Implement DX12 first - since imgui requires device + descriptor heap
    m_ui->Init(hwnd, m_renderer->m_pd3dDevice, m_renderer->m_pd3dSrvDescHeap);

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

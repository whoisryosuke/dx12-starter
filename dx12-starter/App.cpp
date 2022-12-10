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
    while (m_window_container->ShouldLoop())
    {
        // Run any updates before rendering
        Update();

        // Render the 3D!
        Render();
    }

    Exit();
}

bool App::Init()
{
    // Initalize the window here and hydrate 
    m_window_container->Init();
    // Set a pointer to this Window class in GLFW
    // Lets us access the Window class methods in callbacks
    // @see: glfw.org/faq.html#216---how-do-i-use-c-methods-as-callbacks
    glfwSetWindowUserPointer(m_window_container->m_window, this);
    glfwSetFramebufferSizeCallback(m_window_container->m_window, HandleResizeCallback);

    // Get HWND context from window - required for DX12 and imgui
    // Get application window
    // @see: https://www.glfw.org/docs/3.3/group__native.html#gafe5079aa79038b0079fc09d5f0a8e667
    HWND hwnd = glfwGetWin32Window(m_window_container->m_window);

    // Initialize the DX12 renderer
    if (!m_renderer->Init(hwnd)) {
        m_renderer->CleanupDevice();
        return true;
    }

    // Initialize the UI (aka imgui). Requires the window context + DX12 device.
    m_ui->Init(hwnd, m_renderer->m_pd3dDevice, m_renderer->m_pd3dSrvDescHeap);

	return true;
}

void App::Render()
{
    m_ui->Render();
    m_renderer->RenderUI(m_ui);
}

void App::Update()
{
    m_window_container->Update();
}

void App::Exit()
{
    m_renderer->WaitForLastSubmittedFrame();
    m_ui->Terminate();
    m_window_container->Terminate();
}

void App::HandleResize(int width, int height)
{
    std::cout << "Resizing window" << std::endl;
    m_window_container->HandleResize(width, height);
    m_renderer->HandleResize(width, height);
}

void App::HandleResizeCallback(GLFWwindow* window, int width, int height)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    app->HandleResize(width, height);
}
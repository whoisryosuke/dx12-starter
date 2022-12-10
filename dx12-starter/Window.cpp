#include "Window.h"

Window::Window()
{
}

/// <summary>
/// Initializes and opens a native Window context using GLFW. A ref to window context is stored as class property (`m_window`).
/// </summary>
/// <returns></returns>
bool Window::Init()
{
    if (!glfwInit())
    {
        std::cout << "[GLFW]: Unable to initialize\n";
        return -1;
    }

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    const int32_t width = static_cast<int32_t>(videoMode->width * 0.9f);
    const int32_t height = static_cast<int32_t>(videoMode->height * 0.9f);

    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(
        width,
        height,
        "Ryo's DX12 Playground",
        nullptr,
        nullptr);
    if (m_window == nullptr)
    {
        std::cout << "[GLFW]: Unable to create window\n";
        glfwTerminate();

        // Exit app somehow...
        return false;
    }

    const int32_t windowLeft = videoMode->width / 2 - width / 2;
    const int32_t windowTop = videoMode->height / 2 - height / 2;
    glfwSetWindowPos(m_window, windowLeft, windowTop);


    return true;
}

void Window::Terminate()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::Update()
{
    glfwPollEvents();
}

bool Window::ShouldLoop()
{
    return !glfwWindowShouldClose(m_window);
}

void Window::HandleResize(int width, int height)
{
    m_width = width;
    m_height = height;
}

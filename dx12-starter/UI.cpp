#include "UI.h"

struct FrameContext
{
    ID3D12CommandAllocator* CommandAllocator;
    UINT64                  FenceValue;
};

// Data
static int const                    NUM_FRAMES_IN_FLIGHT = 3;
static FrameContext                 g_frameContext[NUM_FRAMES_IN_FLIGHT] = {};
static UINT                         g_frameIndex = 0;

static int const                    NUM_BACK_BUFFERS = 3;
static ID3D12Device* g_pd3dDevice = NULL;
static ID3D12DescriptorHeap* g_pd3dRtvDescHeap = NULL;
static ID3D12DescriptorHeap* g_pd3dSrvDescHeap = NULL;
static ID3D12CommandQueue* g_pd3dCommandQueue = NULL;
static ID3D12GraphicsCommandList* g_pd3dCommandList = NULL;
static ID3D12Fence* g_fence = NULL;
static HANDLE                       g_fenceEvent = NULL;
static UINT64                       g_fenceLastSignaledValue = 0;
static IDXGISwapChain3* g_pSwapChain = NULL;
static HANDLE                       g_hSwapChainWaitableObject = NULL;
static ID3D12Resource* g_mainRenderTargetResource[NUM_BACK_BUFFERS] = {};
static D3D12_CPU_DESCRIPTOR_HANDLE  g_mainRenderTargetDescriptor[NUM_BACK_BUFFERS] = {};

namespace DX12Playground {
    bool UI::Init(GLFWwindow* window)
    {

        // Get application window
        // @see: https://www.glfw.org/docs/3.3/group__native.html#gafe5079aa79038b0079fc09d5f0a8e667
        HWND hwnd = glfwGetWin32Window(window);

        // Initialize Direct3D
        //if (!CreateDeviceD3D(hwnd))
        //{
        //    CleanupDeviceD3D();
        //    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        //    return 1;
        //}

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX12_Init(g_pd3dDevice, NUM_FRAMES_IN_FLIGHT,
            DXGI_FORMAT_R8G8B8A8_UNORM, g_pd3dSrvDescHeap,
            g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
            g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart());

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != NULL);
        return true;
    }
    void UI::Update()
    {
    }
    void UI::Render()
    {
    }
}
#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wtypes.h>

#ifdef _DEBUG
#define DX12_ENABLE_DEBUG_LAYER
#endif

#ifdef DX12_ENABLE_DEBUG_LAYER
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")
#endif
#include "UI.h"

static int const                    NUM_BACK_BUFFERS = 3;
static int const                    NUM_FRAMES_IN_FLIGHT = 3;
struct FrameContext
{
	ID3D12CommandAllocator* CommandAllocator;
	UINT64                  FenceValue;
};

class Renderer
{
public:
	bool Init(HWND hWnd);
	void CreateRenderTarget();
	void CleanupDevice();
	void CleanupRenderTarget();
	void WaitForLastSubmittedFrame();
	FrameContext* WaitForNextFrameResources();
	void RenderUI(DX12Playground::UI* ui);
	void HandleResize(int width, int height);
	static void HandleResizeCallback(Renderer* renderer, int width, int height);


	FrameContext                 m_frameContext[NUM_FRAMES_IN_FLIGHT] = {};
	UINT                         m_frameIndex = 0;
	ID3D12Device* m_pd3dDevice = nullptr;
	ID3D12DescriptorHeap* m_pd3dRtvDescHeap = NULL;
	ID3D12DescriptorHeap* m_pd3dSrvDescHeap = NULL;
	ID3D12CommandQueue* m_pd3dCommandQueue = NULL;
	ID3D12GraphicsCommandList* m_pd3dCommandList = NULL;
	ID3D12Fence* m_fence = NULL;
	HANDLE                       m_fenceEvent = NULL;
	UINT64                       m_fenceLastSignaledValue = 0;
	IDXGISwapChain3* m_pSwapChain = NULL;
	HANDLE                       m_hSwapChainWaitableObject = NULL;
	ID3D12Resource* m_mainRenderTargetResource[NUM_BACK_BUFFERS] = {};
	D3D12_CPU_DESCRIPTOR_HANDLE  m_mainRenderTargetDescriptor[NUM_BACK_BUFFERS] = {};
};


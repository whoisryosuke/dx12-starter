#pragma once
// DirectX 12 APIs
#include <d3d12.h>
#include <dxgi1_4.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <wtypes.h>
#include <pix.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include "d3dx12.h"
// DirectXTK Utilities
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

// If used in DX12, prefer Microsoft ComPtr to using C++ pointers
using Microsoft::WRL::ComPtr;

#ifdef _DEBUG
#define DX12_ENABLE_DEBUG_LAYER
#endif

#ifdef DX12_ENABLE_DEBUG_LAYER
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")
#endif
#include "UI.h"

#define SUCCEEDED(hr)   (((HRESULT)(hr)) >= 0)
#define FAILED(hr)      (((HRESULT)(hr)) < 0)

static int const                    NUM_BACK_BUFFERS = 3;
static int const                    NUM_FRAMES_IN_FLIGHT = 3;
struct FrameContext
{
	ID3D12CommandAllocator* CommandAllocator;
	UINT64                  FenceValue;
};

struct Vertex
{
	DirectX::XMFLOAT3		 position;
	DirectX::XMFLOAT2		 uv;
	DirectX::XMFLOAT3		 normals;
};


inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		//throw HrException(hr);
		throw hr;
	}
}


inline void GetAssetsPath(_Out_writes_(pathSize) WCHAR* path, UINT pathSize)
{
	if (path == nullptr)
	{
		throw std::exception();
	}

	DWORD size = GetModuleFileName(nullptr, path, pathSize);
	if (size == 0 || size == pathSize)
	{
		// Method failed or path was truncated.
		throw std::exception();
	}

	WCHAR* lastSlash = wcsrchr(path, L'\\');
	if (lastSlash)
	{
		*(lastSlash + 1) = L'\0';
	}
}

class Renderer
{
public:
	// Structs
	// Constant Buffers (aka "uniforms")
	struct SceneConstantBuffer
	{
		DirectX::XMFLOAT4 offset;
		float padding[60]; // Padding so the constant buffer is 256-byte aligned.
	};
	static_assert((sizeof(SceneConstantBuffer) % 256) == 0, "Constant Buffer size must be 256-byte aligned");

	// Global uniforms (camera position / matrix / etc)
	struct GlobalsConstantBuffer
	{
		DirectX::XMMATRIX viewMatrix;
		DirectX::XMMATRIX 	projectionMatrix;
		DirectX::XMFLOAT3 	cameraPosition;
		float padding[26]; // Padding so the constant buffer is 256-byte aligned.
	};
	static_assert((sizeof(GlobalsConstantBuffer) % 256) == 0, "Constant Buffer size must be 256-byte aligned");


	Renderer(unsigned int width, unsigned int height);
	bool Init(HWND hWnd);
	void CreateRenderTarget();
	void CleanupDevice();
	void CleanupRenderTarget();
	void WaitForLastSubmittedFrame();
	FrameContext* WaitForNextFrameResources();
	std::wstring GetAssetFullPath(LPCWSTR assetName);
	void GetHardwareAdapter(IDXGIFactory1* pFactory, IDXGIAdapter1** ppAdapter, bool requestHighPerformanceAdapter);
	void RenderUI(DX12Playground::UI* ui);
	void HandleResize(int width, int height);
	static void HandleResizeCallback(Renderer* renderer, int width, int height);
	void OnUpdate();
	void UpdateCB();


	CD3DX12_VIEWPORT m_viewport;
	CD3DX12_RECT m_scissorRect;
	FrameContext                 m_frameContext[NUM_FRAMES_IN_FLIGHT] = {};
	UINT                         m_frameIndex = 0;
	ID3D12Device* m_pd3dDevice = nullptr;
	ID3D12DescriptorHeap* m_pd3dRtvDescHeap = NULL;
	ID3D12DescriptorHeap* m_pd3dSrvDescHeap = NULL;
	ComPtr<ID3D12DescriptorHeap> m_cbvHeap;
	ComPtr<ID3D12PipelineState> m_pipelineState;
	ComPtr<ID3D12RootSignature> m_rootSignature;
	ID3D12CommandQueue* m_pd3dCommandQueue = NULL;
	ComPtr<ID3D12GraphicsCommandList> m_pd3dCommandList = NULL;
	ID3D12Fence* m_fence = NULL;
	HANDLE                       m_fenceEvent = NULL;
	UINT64                       m_fenceLastSignaledValue = 0;
	IDXGISwapChain3* m_pSwapChain = NULL;
	HANDLE                       m_hSwapChainWaitableObject = NULL;
	ID3D12Resource* m_mainRenderTargetResource[NUM_BACK_BUFFERS] = {};
	D3D12_CPU_DESCRIPTOR_HANDLE  m_mainRenderTargetDescriptor[NUM_BACK_BUFFERS] = {};

	// App resources.
	ID3D12Resource* m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
	ComPtr<ID3D12Resource> m_constantBuffer;
	SceneConstantBuffer m_constantBufferData;
	ComPtr<ID3D12Resource> m_constantBufferGlobals;
	GlobalsConstantBuffer m_constantBufferGlobalsData;
	UINT8* m_pCbvDataBegin;


private:
	// Root assets path.
	std::wstring m_assetsPath;
};


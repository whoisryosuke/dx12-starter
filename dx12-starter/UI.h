#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <tchar.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace DX12Playground {

class UI
{
public:
	bool Init(HWND window, ID3D12Device* device, ID3D12DescriptorHeap* srvHeap);
	void Update();
	void Render();
	void RenderDrawData(ID3D12GraphicsCommandList* m_pd3dCommandList);
	void Terminate();

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

}
#pragma once
// ====================================================================================
// Graphics.h
//
// High-level overview for beginners:
// This header declares the `Graphics` class which is responsible for initializing
// Direct3D 11, holding the device/context/swapchain objects, and providing a few
// simple drawing utilities used by the tutorial (clearing the screen, ending the
// frame, and drawing a test object).
//
// Key concepts:
// - `ID3D11Device` creates GPU resources (buffers, shaders, views).
// - `ID3D11DeviceContext` records commands that the GPU will execute.
// - `IDXGISwapChain` holds the back buffer(s) that are presented to the screen.
// - A "render target view" (`ID3D11RenderTargetView`) is used to bind the back
//   buffer so the GPU can render into it.
//
// The nested exception classes give you helpful, human-readable error messages
// if something goes wrong when calling D3D functions.
// ====================================================================================
#include "ChiliWin.h"
#include "ChiliException.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include "DxgiInfoManager.h"

class Graphics
{
public:
	class Exception : public ChiliException
	{
		using ChiliException::ChiliException;
	};
	class HrException : public Exception
	{
	public:
		HrException( int line,const char* file,HRESULT hr,std::vector<std::string> infoMsgs = {} ) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};
	class InfoException : public Exception
	{
	public:
		InfoException( int line,const char* file,std::vector<std::string> infoMsgs ) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};
public:
	Graphics( HWND hWnd );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer( float red,float green,float blue ) noexcept;
	void DrawTestTriangle(float angle, float x, float y);
private:
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};
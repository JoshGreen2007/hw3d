#pragma once
#include "ChiliWin.h"
#include <wrl.h>
#include <vector>
#include <dxgidebug.h>
#include <string>

// ====================================================================================
// DxgiInfoManager
//
// Small utility that wraps the DXGI info queue used for retrieving debug
// messages from the Direct3D runtime. When running in debug mode this allows
// the application to collect and throw developer-friendly error messages
// containing details about D3D API errors and warnings.
//
// Usage (brief):
// - Call `Set()` before a D3D call that you want to check for debug messages.
// - After the D3D call, call `GetMessages()` which returns a vector of strings
//   containing the messages produced since the last `Set()`.
// ====================================================================================
class DxgiInfoManager
{
public:
	DxgiInfoManager();
	~DxgiInfoManager() = default;
	DxgiInfoManager( const DxgiInfoManager& ) = delete;
	DxgiInfoManager& operator=( const DxgiInfoManager& ) = delete;

	// Remember the current position in the DXGI debug message queue. Subsequent
	// calls to GetMessages() will return only messages added after this call.
	void Set() noexcept;

	// Retrieve any debug messages produced since the last Set(). Useful for
	// showing detailed error info when a D3D call fails.
	std::vector<std::string> GetMessages() const;

private:
	unsigned long long next = 0u; // index of the next message to read
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;
};

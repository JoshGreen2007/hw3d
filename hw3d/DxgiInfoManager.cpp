// DxgiInfoManager.cpp
// Wraps the DXGI debug info queue used to gather debug/error messages from
// the Direct3D runtime. When running in a debug build this utility allows the
// program to capture detailed messages that explain why D3D calls failed or
// produced warnings.

#include "DxgiInfoManager.h"
#include "Window.h"
#include "Graphics.h"
#include <dxgidebug.h>
#include <memory>

#pragma comment(lib, "dxguid.lib")

#define GFX_THROW_NOINFO(hrcall) if( FAILED( hr = (hrcall) ) ) throw Graphics::HrException( __LINE__,__FILE__,hr )

DxgiInfoManager::DxgiInfoManager()
{
	// The DXGI debug interface is provided by the system DLL dxgidebug.dll.
	// We dynamically load it so the project can still run on systems without
	// the debug DLL (release builds) while providing useful debug output on
	// developer machines.

	// define function signature of DXGIGetDebugInterface
	typedef HRESULT (WINAPI* DXGIGetDebugInterface)(REFIID,void **);

	// load the dll that contains the function DXGIGetDebugInterface
	const auto hModDxgiDebug = LoadLibraryEx( "dxgidebug.dll",nullptr,LOAD_LIBRARY_SEARCH_SYSTEM32 );
	if( hModDxgiDebug == nullptr )
	{
		throw CHWND_LAST_EXCEPT();
	}

	// get address of DXGIGetDebugInterface in dll
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress( hModDxgiDebug,"DXGIGetDebugInterface" ))
	);
	if( DxgiGetDebugInterface == nullptr )
	{
		throw CHWND_LAST_EXCEPT();
	}

	HRESULT hr;
	// Query the IDXGIInfoQueue which lets us read debug messages produced by
	// DXGI / D3D. We will throw a Graphics::HrException if this fails.
	GFX_THROW_NOINFO( DxgiGetDebugInterface( __uuidof(IDXGIInfoQueue),&pDxgiInfoQueue ) );
}

// Remember the number of messages currently in the queue so subsequent calls
// to GetMessages will only retrieve messages that were added after this.
void DxgiInfoManager::Set() noexcept
{
	next = pDxgiInfoQueue->GetNumStoredMessages( DXGI_DEBUG_ALL );
}

// Read and return all DXGI/D3D debug messages that have been added since the
// last call to Set(). Each message is returned as a std::string for easy
// logging or display.
std::vector<std::string> DxgiInfoManager::GetMessages() const
{
	std::vector<std::string> messages;
	const auto end = pDxgiInfoQueue->GetNumStoredMessages( DXGI_DEBUG_ALL );
	for( auto i = next; i < end; i++ )
	{
		HRESULT hr;
		SIZE_T messageLength;
		// get the size of message i in bytes
		GFX_THROW_NOINFO( pDxgiInfoQueue->GetMessage( DXGI_DEBUG_ALL,i,nullptr,&messageLength ) );
		// allocate memory for message
		auto bytes = std::make_unique<byte[]>( messageLength );
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		// get the message and push its description into the vector
		GFX_THROW_NOINFO( pDxgiInfoQueue->GetMessage( DXGI_DEBUG_ALL,i,pMessage,&messageLength ) );
		messages.emplace_back( pMessage->pDescription );
	}
	return messages;
}

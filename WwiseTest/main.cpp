#define AK_OPTIMIZED

#include <Windows.h>
#include <iostream>
#include <assert.h>

#include <AK/AkWwiseSDKVersion.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>                  // Memory Manager
#include <AK/SoundEngine/Common/AkModule.h>                     // Default memory and stream managers

/////////////////////////////////////////////////////////////////////////////////
// Custom alloc/free functions. These are declared as "extern" in AkMemoryMgr.h
// and MUST be defined by the game developer.
/////////////////////////////////////////////////////////////////////////////////
namespace AK
{
#ifdef WIN32
	void * AllocHook(size_t in_size)
	{
		return malloc(in_size);
	}
	void FreeHook(void * in_ptr)
	{
		free(in_ptr);
	}
	// Note: VirtualAllocHook() may be used by I/O pools of the default implementation
	// of the Stream Manager, to allow "true" unbuffered I/O (using FILE_FLAG_NO_BUFFERING
	// - refer to the Windows SDK documentation for more details). This is NOT mandatory;
	// you may implement it with a simple malloc().
	void * VirtualAllocHook(
		void * in_pMemAddress,
		size_t in_size,
		DWORD in_dwAllocationType,
		DWORD in_dwProtect
	)
	{
		return VirtualAlloc(in_pMemAddress, in_size, in_dwAllocationType, in_dwProtect);
	}
	void VirtualFreeHook(
		void * in_pMemAddress,
		size_t in_size,
		DWORD in_dwFreeType
	)
	{
		VirtualFree(in_pMemAddress, in_size, in_dwFreeType);
	}
#endif
}

using namespace std;

bool InitSoundEngine()
{
	//
	// Create and initialize an instance of the default memory manager. Note
	// that you can override the default memory manager with your own. Refer
	// to the SDK documentation for more information.
	//

	AkMemSettings memSettings;
	memSettings.uMaxNumPools = 20;

	if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
	{
		assert(!"Could not create the memory manager.");
		return false;
	}
	return true;
}

int main()
{
	cout << "Wwise Version: "<< AK_WWISESDK_VERSION_MAJOR << "." << AK_WWISESDK_VERSION_MINOR << "." << AK_WWISESDK_VERSION_SUBMINOR << "." << AK_WWISESDK_VERSION_BUILD;

	if (!InitSoundEngine())
		cout << "Failed to initialize Wwise!!!\n";

	cin.get();
}
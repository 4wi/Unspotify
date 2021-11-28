#include "detours.h"


namespace util::hooking::detour {
	bool init( ) {
		return MH_Initialize( ) == MH_OK;
	}

	bool create( void* target, void* detour, void** orig ) {
		return MH_CreateHook( target, detour, orig ) == MH_OK &&
			MH_EnableHook( target ) == MH_OK;
	}

	bool remove( void* target ) {
		return MH_DisableHook( target ) == MH_OK;
	}
}

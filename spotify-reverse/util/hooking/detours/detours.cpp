#include "detours.h"


namespace util::hooking::detour {
	void init( ) {
		MH_Initialize( );
	}

	void create( mem::addr_t& target, void* detour, void** orig ) {
		return create( target.cast<void*>( ), detour, orig );
	}

	void create( void* target, void* detour, void** orig ) {
		if ( MH_CreateHook( target, detour, orig ) != MH_OK ) __debugbreak( );
		if ( MH_EnableHook( target ) != MH_OK ) __debugbreak( );
	}

	void remove( void* target ) {
		if ( MH_DisableHook( target ) != MH_OK ) __debugbreak( );
	}
}

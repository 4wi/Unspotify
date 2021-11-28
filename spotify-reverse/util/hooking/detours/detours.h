#pragma once

#include "mh/minhook.h"
#include "../../mem/addr.h"


namespace util::hooking::detour {
	bool init( );
	bool create( void* target, void* detour, void** orig );
	bool remove( void* target = nullptr /* nullptr = MH_ALL_HOOKS */ );
}

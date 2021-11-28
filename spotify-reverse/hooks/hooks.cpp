#include "hooks.h"


#define CREATE_HOOK(n) if ( !util::hooking::detour::create(spotify::addr:: ##n, hooked:: ##n, reinterpret_cast< void** > ( &original:: ##n ) ) ) util::logger::fatal("Unable to hook %s", #n);


namespace hooks {
	void init( ) {
		if ( !util::hooking::detour::init( ) )
			util::logger::fatal( "Unable to init minhook" );
	#ifdef _DEBUG
		CREATE_HOOK( debug_msg );
	#endif
		CREATE_HOOK( get_ad );
		CREATE_HOOK( create_track );
	}

	void shutdown( ) {
		util::hooking::detour::remove( );
	}
}


#undef CREATE_HOOK

#include "hooks.h"
#include <algorithm>


namespace hooks {
	void init( ) {
		util::hooking::detour::init( );
		util::hooking::detour::create( spotify::addr::debug_msg, hooked::debug_msg, reinterpret_cast< void** >( &original::debug_msg ) );
		util::hooking::detour::create( spotify::addr::get_ad, hooked::get_ad, reinterpret_cast< void** >( &original::get_ad ) );
		util::hooking::detour::create( spotify::addr::play_track, hooked::play_track, reinterpret_cast< void** >( &original::play_track ) );
	}

	void shutdown( ) {
		util::hooking::detour::remove( );
	}
}
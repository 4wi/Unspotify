#pragma once
#include "../util/util.h"
#include "../spotify/spotify.h"


namespace hooks {
	namespace hooked {
	#ifdef _DEBUG
		std::uintptr_t __cdecl debug_msg( std::uint32_t, std::uint32_t, const char* win, const char* flag, std::uint32_t size, std::uint32_t, const char* fmt, ... );
	#endif
		std::uintptr_t __cdecl get_ad( int a1, int a2 );
		void __fastcall create_track( void* pthis, void* pedx, spotify::structs::player_meta_t* player_meta, spotify::structs::player_track_meta_t* track_meta, int a4, int a5, int a6, int a7, int a8, int a9, int a10 );
	}
	namespace original {
	#ifdef _DEBUG
		inline decltype( &hooked::debug_msg ) debug_msg;
	#endif
		inline decltype( &hooked::get_ad ) get_ad;
		inline decltype( &hooked::create_track ) create_track;
	}

	void init( );
	void shutdown( );
}
#pragma once
#include "../util/util.h"
#include "../spotify/spotify.h"


namespace hooks {
	namespace hooked {
		std::uintptr_t __cdecl debug_msg( std::uint32_t, std::uint32_t, const char* win, const char* flag, std::uint32_t size, std::uint32_t, const char* fmt, ... );
		std::uintptr_t __cdecl get_ad( int a1, int a2 );
		std::uintptr_t __fastcall play_track( std::uintptr_t pthis, std::uintptr_t pEDX, spotify::structs::player_meta_t* player_meta, spotify::structs::player_track_meta_t* track_meta, char a4, int a5, char a6, int a7, int a8, char a9, char a10, int a11, char a12, int a13 );
	}
	namespace original {
		inline decltype( &hooked::debug_msg ) debug_msg;
		inline decltype( &hooked::get_ad ) get_ad;
		inline decltype( &hooked::play_track ) play_track;
	}

	void init( );
	void shutdown( );
}
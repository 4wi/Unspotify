#include "../hooks.h"


namespace hooks {
	namespace hooked {
		/*
		@note: es3n1n:
		First of all find xref "Creating track player for track", then at the end 
		there would be a call to a function with 13 params, this is it ;)
		*/

		std::uintptr_t __fastcall play_track( 
			std::uintptr_t pthis, 
			std::uintptr_t pEDX, 
			spotify::structs::player_meta_t* player_meta, 
			spotify::structs::player_track_meta_t* track_meta, 
			char a4, int a5, char a6, int a7, int a8, char a9, char a10, int a11, char a12, int a13 
		) {
			player_meta->m_should_skip = static_cast< std::uint32_t >( static_cast< bool >( strstr( track_meta->m_track_uri, "spotify:ad:" ) ) );
			util::logger::info( "Playing %s | should_skip: %s", track_meta->m_track_uri, player_meta->m_should_skip ? "true" : "false" );
			return original::play_track( pthis, pEDX, player_meta, track_meta, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13 );
		}
	}
}

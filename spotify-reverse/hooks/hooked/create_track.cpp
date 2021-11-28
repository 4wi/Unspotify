#include "../hooks.h"


namespace hooks {
	namespace hooked {
		/*
		@xref: "    Creating track player for track (playback_id %s)"
		*/
		void __fastcall create_track( 
			void* pthis, void* pedx, 
			spotify::structs::player_meta_t* player_meta, 
			spotify::structs::player_track_meta_t* track_meta, 
			int a4, int a5, int a6, int a7, int a8, int a9, int a10 
		) {
			player_meta->m_should_skip = static_cast< std::uint32_t >( static_cast< bool >( strstr( track_meta->m_track_uri, "spotify:ad:" ) ) );
			util::logger::info( "Playing %s | should_skip: %s", track_meta->m_track_uri, player_meta->m_should_skip ? "true" : "false" );

			original::create_track( pthis, pedx, player_meta, track_meta, a4, a5, 8, a7, a8, a9, a10 );
		}
	}
}

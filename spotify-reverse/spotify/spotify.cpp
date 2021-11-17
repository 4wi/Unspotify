#include "spotify.h"


namespace spotify {
	void init( ) {
		TRACE_FN;

		modules::spotify = util::mem::module_t( nullptr );
		util::logger::debug( "module::spotify = 0x%p", modules::spotify );

		addr::debug_msg =
			modules::spotify.sig( "6A 24 B8 ? ? ? ? E8 ? ? ? ? 8B 7D 10 33 C0 8B 75 14 89 45 D8 89 45 E8 C7 45 ? ? ? ? ? 88 45 D8 89 45 FC 8D 45 24" );
		util::logger::debug( "addr::debug_msg = 0x%p", addr::debug_msg );

		addr::get_ad =
			modules::spotify.sig( "68 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 8B 5D 08 8D 8D ? ? ? ? 8B 7D 0C 53 89 9D ? ? ? ? 89 BD ? ? ? ? E8 ? ? ? ? 83 65 FC 00 8D 47 04 89 85 ? ? ? ?" );
		util::logger::debug( "addr::get_ad = 0x%p", addr::get_ad );

		addr::play_track_table_mov =
			modules::spotify.sig( "C7 03 ? ? ? ? 89 43 08 89 55 FC 89 11 89 51 04 E8 ? ? ? ? 8B 75 14 8D 7B 14 8B 45 18 8D 4B 28 FF 75 1C " );
		util::logger::debug( "addr::play_track_table_mov = 0x%p", addr::play_track_table_mov );
		addr::play_track_table = addr::play_track_table_mov.add( 2 ).self_get( );
		util::logger::debug( "addr::play_track_table = 0x%p", addr::play_track_table );
		addr::play_track_fn_addr = addr::play_track_table.add( 4 );
		util::logger::debug( "addr::play_track_fn_addr = 0x%p", addr::play_track_fn_addr );
		addr::play_track = addr::play_track_fn_addr.self_get( );
		util::logger::debug( "addr::play_track = 0x%p", addr::play_track );
	}
}
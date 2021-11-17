#pragma once

#include "../util/util.h"

namespace spotify {
	namespace structs {
		struct player_meta_t {
		private: char __pad[ 0x74 ];
		public: std::uint32_t m_should_skip;
		};

		struct player_track_meta_t {
		private: char __pad[ 0x48 ];
		public: const char* m_track_uri;
		};
	}

	namespace modules {
		inline util::mem::module_t spotify;
	}

	namespace addr {
		inline util::mem::addr_t debug_msg;
		inline util::mem::addr_t get_ad;

		inline util::mem::addr_t play_track;
		inline util::mem::addr_t play_track_table_mov;
		inline util::mem::addr_t play_track_table;
		inline util::mem::addr_t play_track_fn_addr;
	}

	void init( );
}

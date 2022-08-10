#include "../hooks.h"

namespace hooks {
    namespace hooked {
        /*
		@xref: "    Creating track player for track (playback_id %s)"
		*/
        void __fastcall create_track(void* pthis, void* pedx, spotify::structs::player_meta_t* player_meta,
            spotify::structs::player_track_meta_t* track_meta, double speed, int normalization, int urgency, int track_select_flag, int flag,
            int stream_type) {
            player_meta->m_should_skip = static_cast<std::uint32_t>(static_cast<bool>(strstr(track_meta->m_track_uri, "spotify:ad:")));
            util::logger::info("Playing %s | should_skip: %s", track_meta->m_track_uri, player_meta->m_should_skip ? "true" : "false");
            if (player_meta->m_should_skip)
                speed = 29.0;
            original::create_track(pthis, pedx, player_meta, track_meta, speed, normalization, urgency, track_select_flag, flag, stream_type);
        }
    } // namespace hooked
} // namespace hooks

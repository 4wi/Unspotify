#pragma once
#include "../spotify/spotify.h"
#include "../util/util.h"

namespace hooks {
    namespace hooked {
#ifdef _DEBUG
        std::uintptr_t __cdecl debug_msg(std::uint32_t, std::uint32_t, const char* win, const char* flag, std::uint32_t size, std::uint32_t,
            const char* fmt, ...);
#endif
        std::uintptr_t __cdecl get_ad(int a1, int a2);
        void __fastcall create_track(void* pthis, void* pedx, spotify::structs::player_meta_t* player_meta,
            spotify::structs::player_track_meta_t* track_meta, double speed, int normalization, int urgency, int track_select_flag, int flag,
            int stream_type);
    } // namespace hooked
    namespace original {
#ifdef _DEBUG
        inline decltype(&hooked::debug_msg) debug_msg;
#endif
        inline decltype(&hooked::get_ad) get_ad;
        inline decltype(&hooked::create_track) create_track;
    } // namespace original

    void init();
    void shutdown();
} // namespace hooks
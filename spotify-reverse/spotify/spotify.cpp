#include "spotify.h"

#define ASSERT_PATTERN(s)                                                                                                                                 \
    if (!addr::##s.valid())                                                                                                                               \
        util::logger::fatal("Pattern %s not found. Please update your Unspotify version", #s);
#define ASSERT_PATTERN_STEP(s)                                                                                                                            \
    if (!s)                                                                                                                                               \
    util::logger::fatal("Unable to find %s at %d", #s, __LINE__)

namespace spotify {
    void init() {
#pragma warning(disable : 5103)
        TRACE_FN;

        modules::spotify = util::mem::module_t(nullptr);
        util::logger::debug("module::spotify = 0x%p", modules::spotify);

        uint32_t str;
        util::mem::addr_t sig;
        std::vector<int> pattern = {};

#ifdef _DEBUG
        // "Could not create stream reader for file: %s"
        str = modules::spotify.sig(
            "43 6F 75 6C 64 20 6E 6F 74 20 63 72 65 61 74 65 20 73 74 72 65 61 6D 20 72 65 61 64 65 72 20 66 6F 72 20 66 69 6C 65 3A 20 25 73");
        ASSERT_PATTERN_STEP(str);
        pattern.clear();
        pattern.emplace_back(0x68 /* push offset */);
        for (int i = 0; i < 4; i++)
            pattern.emplace_back((int)(((uint8_t*)(&str))[i]));
        sig = modules::spotify.sig(pattern);
        ASSERT_PATTERN_STEP(sig);
        addr::debug_msg = sig.walk_until(0x6A /* push 02 */).walk_until(0xE8 /* call */).rel(1);
        util::logger::debug("addr::debug_msg = 0x%p", addr::debug_msg);
        ASSERT_PATTERN(debug_msg);
#endif

        // "ad_type"
        str = modules::spotify.sig("61 64 5F 74 79 70 65 00");
        ASSERT_PATTERN_STEP(str);
        pattern.clear();
        for (int i = 0; i < 4; i++)
            pattern.emplace_back((int)(((uint8_t*)(&str))[i]));
        sig = modules::spotify.sig(pattern);
        ASSERT_PATTERN_STEP(sig);
        do {
            sig = sig.walk_back_until(0xC2 /* retn */);
        } while (sig.offset(-5).read<uint8_t>() != 0xE8 && sig.offset(-8).read<uint8_t>() != 0xE8);
        addr::get_ad = sig.add(1).read<uint8_t>() == 0x68 /* push */ ? sig.add(1) : sig.walk_until(0x68 /* push 0D4h */);
        util::logger::debug("addr::get_ad = 0x%p", addr::get_ad);
        ASSERT_PATTERN(get_ad);

        // "    Creating track player for track (playback_id %s)"
        str = modules::spotify.sig("20 20 20 20 43 72 65 61 74 69 6E 67 20 74 72 61 63 6B 20 70 6C 61 79 65 72 20 66 6F 72 20 74 72 61 63 6B 20 28 70 6C "
                                   "61 79 62 61 63 6B 5F 69 64 20 25 73 29");
        ASSERT_PATTERN_STEP(sig);
        pattern.clear();
        pattern.emplace_back(0x68 /* push offset */);
        for (int i = 0; i < 4; i++)
            pattern.emplace_back((int)(((uint8_t*)(&str))[i]));
        sig = modules::spotify.sig(pattern);
        ASSERT_PATTERN_STEP(sig);
        addr::create_track = sig.walk_back_until(0xC2 /* retn */).offset(3 /* C2 04 00 */);
        while (addr::create_track.read<uint8_t>() == 0xE8 /* call */)
            addr::create_track = addr::create_track.add(5); // E8 + 4 bytes addr
        while (addr::create_track.read<uint8_t>() == 0xCC)
            addr::create_track = addr::create_track.add(1); // skip aligns
        util::logger::debug("addr::create_track = 0x%p", addr::create_track);
        ASSERT_PATTERN(create_track);
#pragma warning(default : 5103)
    }
} // namespace spotify

#undef ASSERT_PATTERN
#undef ASSERT_PATTERN_STEP

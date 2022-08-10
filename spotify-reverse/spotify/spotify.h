#pragma once
#include "../util/util.h"

namespace spotify {
    namespace structs {
        struct player_meta_t {
        private:
            char __pad[0x74];

        public:
            std::uint32_t m_should_skip;
        };

        struct player_track_meta_t {
        private:
            char __pad[0x48];

        public:
            const char* m_track_uri;
        };
    } // namespace structs

    namespace modules {
        inline util::mem::module_t spotify;
    }

    namespace addr {
#ifdef _DEBUG
        inline util::mem::addr_t debug_msg;
#endif
        inline util::mem::addr_t get_ad;
        inline util::mem::addr_t create_track;
        inline util::mem::addr_t should_show_ad;
    } // namespace addr

    void init();
} // namespace spotify

#pragma once
#include "../defines.h"
#include "../util/networking/networking.h"
#include "shared/logger.h"

namespace updates {
    struct update_info_t {
        bool m_error = false;
        std::string m_error_desc = "Unable to connect to server";

        uint32_t m_version = UNSPOTIFY_VERSION;
        std::string m_changelog = "Failed to request update info";
        bool m_is_required = false;
        std::string m_download_url = "https://git.tcp.direct/dg/unspotify";
    };

    update_info_t poll_info();
    void do_job();
} // namespace updates

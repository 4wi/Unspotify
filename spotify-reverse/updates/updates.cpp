#include "updates.h"

namespace updates {
    update_info_t poll_info() {
        auto [data, error] = util::networking::get(AUTOUPDATER_DOMAIN, AUTOUPDATER_URL);
        if (error)
            return update_info_t { .m_error = true, .m_error_desc = "Internal server error :shrug:" };

        return update_info_t { .m_error = false,
            .m_version = data["version"].get<uint32_t>(),
            .m_changelog = data["changelog"].get<std::string>(),
            .m_is_required = data["required"].get<bool>(),
            .m_download_url = data["download_url"].get<std::string>() };
    }

    void do_job() {
        auto update_info = poll_info();
        if (update_info.m_error) {
            util::logger::error("Failed to poll newest version info: %s", update_info.m_error_desc.c_str());
            return;
        }

        if (update_info.m_version <= UNSPOTIFY_VERSION) // @note: es3n1n: if we are up2date
            return;

        if (update_info.m_is_required) {
            util::logger::fatal("New version is available!\n\nChangelog:\n%s\nDownload url: %s", update_info.m_changelog.c_str(),
                update_info.m_download_url.c_str());
            return;
        }

        util::logger::info("New version is available!");
        util::logger::info("");
        util::logger::info("");
        util::logger::info("Changelog:");
        printf("%s\n", update_info.m_changelog.c_str());
        util::logger::info("");
        util::logger::info("");
        util::logger::info("Download url: %s", update_info.m_download_url.c_str());
    }
} // namespace updates
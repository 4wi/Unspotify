#pragma once
#include "logger.h"

#define UNSPOTIFY_GIT_URL "https://git.tcp.direct/dg/Unspotify"
#define UNSPOTIFY_DISCORD_URL "https://discord.gg/U7X9kKcJzF"

namespace util {
    namespace logo {
        inline void create_console_and_draw_logo() {
            util::logger::startup();
            util::logger::info("                                                       d8,   ,d8888b          ");
            util::logger::info("                                                 d8P   `8P    88P'             ");
            util::logger::info("                                             d888888P     d888888P            ");
            util::logger::info("?88   d8P  88bd88b  .d888b,?88,.d88b, d8888b   ?88'    88b  ?88'    ?88   d8P ");
            util::logger::info("d88   88   88P' ?8b ?8b,   `?88'  ?88d8P' ?88  88P     88P  88P     d88   88  ");
            util::logger::info("?8(  d88  d88   88P   `?8b   88b  d8P88b  d88  88b    d88  d88      ?8(  d88  ");
            util::logger::info("`?88P'?8bd88'   88b`?888P'   888888P'`?8888P'  `?8b  d88' d88'      `?88P'?8b ");
            util::logger::info("                             88P'                                          )88");
            util::logger::info("                            d88                                           ,d8P");
            util::logger::info("                            ?8P                                        `?888P ");
            util::logger::info("                compiled at %s %s", __DATE__, __TIME__);
            util::logger::info("                git: %s", UNSPOTIFY_GIT_URL);
            util::logger::info("                join our discord: %s", UNSPOTIFY_DISCORD_URL);
            util::logger::info("");
            util::logger::info("");
        }
    } // namespace logo
} // namespace util
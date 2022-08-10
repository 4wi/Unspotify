#include "../hooks.h"

namespace hooks {
    namespace hooked {
#ifdef _DEBUG
        std::uintptr_t __cdecl debug_msg(std::uint32_t, std::uint32_t, const char* win, const char* flag, std::uint32_t size, std::uint32_t,
            const char* fmt, ...) { // @xref: "Path provided in --%s '%s' (resolved to '%s') does not exist."
            LOGGER_PARSE_FMT;

            for (std::size_t i = 0; i < strlen(buf); i++)
                buf[i] = buf[i] == '\n' ? ' ' : buf[i];

            printf("[spotify::debug_msg] %s\n", buf);

            return 0;
        }
#endif
    } // namespace hooked
} // namespace hooks
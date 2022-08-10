#include "bootstrap.h"
#include "../exceptions/exceptions.h"
#include "../hooks/hooks.h"
#include "../spotify/spotify.h"
#include "../updates/updates.h"
#include "../util/util.h"
#include "shared/logo.h"

#include <thread>

namespace bootstrap {
    DWORD __stdcall _initial_routine(HANDLE) {
        util::logo::create_console_and_draw_logo();

        exceptions::subscribe();

#ifdef CHECK_FOR_UPDATES
        std::thread(updates::do_job).detach();
#endif

        spotify::init();
        hooks::init();

#ifdef _DEBUG
        while (!GetAsyncKeyState(VK_DELETE)) {
#else
        util::logger::warn("press any key to close this console");
        _getwch();
        util::logger::detach();

        while (true) {
#endif
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        _shutdown();
        return 1; // unreachable but whatever
    }

    bool startup(HINSTANCE dll_handle) {
        detail::dll_handle = dll_handle;
        detail::region_size = util::mem::module_t(uintptr_t(dll_handle)).get_nt_headers()->OptionalHeader.SizeOfImage;
        CreateThread(nullptr, 0, _initial_routine, 0, 0, nullptr);
        return true;
    }

    void _shutdown() {
        hooks::shutdown();
        FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(detail::dll_handle), 0x1);
    }
} // namespace bootstrap

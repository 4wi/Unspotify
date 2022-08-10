#include <Windows.h>
#include <cstdint>
#include <cstdio>

#include "injector/injector.h"

int main() {
    util::logo::create_console_and_draw_logo();

    STARTUPINFOA si = { .cb = sizeof(si) };
    PROCESS_INFORMATION pi = {};

    constexpr const char* exe_path = "oSpotify.exe";

    // Creating process
    //
    util::logger::debug("Spawning %s", exe_path);
    if (!CreateProcessA(exe_path, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        util::logger::error("Unable to create process, error code: %d", GetLastError());
        system("pause");
        goto END;
    }

    // Injecting Unspotify
    //
    util::logger::debug("Injecting spotify-reverse.dll");
    if (!injector::inject(pi.hProcess, "spotify-reverse.dll")) {
        util::logger::error("Unable to inject module, error code: %d", GetLastError());
        TerminateProcess(pi.hProcess, 0x0);
        system("pause");
        goto END;
    }

    ResumeThread(pi.hThread);

END:
    return EXIT_SUCCESS;
}

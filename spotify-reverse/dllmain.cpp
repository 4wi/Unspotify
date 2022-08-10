#include "bootstrap/bootstrap.h"
#include <cstdint>

BOOL __stdcall DllMain(std::uintptr_t hinstDll, std::uint32_t fdwReason, std::uintptr_t) {
    if (fdwReason != DLL_PROCESS_ATTACH)
        return 1;

    return bootstrap::startup(reinterpret_cast<HINSTANCE>(hinstDll));
}

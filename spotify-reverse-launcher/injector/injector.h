#pragma once
#include "shared/logo.h"
#include <Windows.h>

namespace injector {
    namespace detail {
        void* get_process_by_name(const wchar_t* name);
    }

    bool inject(const wchar_t* proc, const char* path);
    bool inject(HANDLE proc, const char* path);
} // namespace injector

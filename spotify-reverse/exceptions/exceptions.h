#pragma once
#include <Windows.h>
#include <cstdint>

namespace exceptions {
    LONG __stdcall handler(EXCEPTION_POINTERS* info);
    void subscribe();
} // namespace exceptions

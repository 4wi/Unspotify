#include "exceptions.h"
#include "../bootstrap/bootstrap.h"
#include "shared/logger.h"
#include <iostream>
#include <sstream>
#include <string>

namespace exceptions {
    LONG __stdcall handler(EXCEPTION_POINTERS* info) {
        static bool logged { false };

        if (logged)
            return EXCEPTION_CONTINUE_SEARCH; // @note: es3n1n: log exceptions only once

        auto exc_addr = reinterpret_cast<uintptr_t>(info->ExceptionRecord->ExceptionAddress);

        if ((exc_addr < reinterpret_cast<uintptr_t>(bootstrap::detail::dll_handle)
                || exc_addr > (reinterpret_cast<uintptr_t>(bootstrap::detail::dll_handle) + bootstrap::detail::region_size))) {
            return EXCEPTION_CONTINUE_SEARCH; // @note: es3n1n: log exceptions only from our mod
        }

        std::stringstream log_msg;
        log_msg << "Module base: " << std::hex << std::showbase << bootstrap::detail::dll_handle << std::endl;
        log_msg << "Module size: " << std::hex << std::showbase << bootstrap::detail::region_size << std::endl;
        log_msg << "Exception address: " << std::hex << std::showbase << exc_addr << std::endl;
        log_msg << "Exception code: " << std::hex << std::showbase << info->ExceptionRecord->ExceptionCode << std::endl;
        log_msg << "EAX: " << std::hex << std::showbase << info->ContextRecord->Eax << " | EBX: " << info->ContextRecord->Ebx << std::endl;
        log_msg << "ECX: " << std::hex << std::showbase << info->ContextRecord->Ecx << " | EDX: " << info->ContextRecord->Edx << std::endl;
        log_msg << "EBP: " << std::hex << std::showbase << info->ContextRecord->Ebp << " | ESP: " << info->ContextRecord->Esp << std::endl;
        log_msg << "ESI: " << std::hex << std::showbase << info->ContextRecord->Esi << " | EDI: " << info->ContextRecord->Edi << std::endl;

        util::logger::fatal(log_msg.str().c_str());

        logged = true;
        return EXCEPTION_EXECUTE_HANDLER;
    }

    void subscribe() { AddVectoredExceptionHandler(1, handler); }
} // namespace exceptions

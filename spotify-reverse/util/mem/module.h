#pragma once

#include "../mem/addr.h"
#include <Windows.h>
#include <string>
#include <vector>

namespace util::mem {
    struct module_t {
    public:
        //
        // constructors, etc...
        module_t() : m_addr() {};
        module_t(uintptr_t s) : m_addr(s) {};
        module_t(const char* module_name) : m_addr(GetModuleHandleA(module_name)) {};
        ~module_t() = default;

    public:
        //
        // exports related
        mem::addr_t get_export(const char* name) { return mem::addr_t(reinterpret_cast<void*>(GetProcAddress(m_addr.cast<HMODULE>(), name))); }

        //
        // pattern scan related
    public:
        mem::addr_t sig(std::string_view pattern) { return sig(pattern_to_byte(pattern)); }

        mem::addr_t sig(std::vector<int> pattern_bytes) {
            unsigned long image_size = get_nt_headers()->OptionalHeader.SizeOfImage;
            int* pattern_data = pattern_bytes.data();
            size_t pattern_size = pattern_bytes.size();

            for (unsigned long i = 0ul; i < image_size - pattern_size; i++) {
                bool found = true;

                for (unsigned long j = 0ul; j < pattern_size; j++) {
                    if (pattern_data[j] == -1)
                        continue;
                    if (m_addr.offset(i + j).read<std::uint8_t>() == pattern_data[j])
                        continue;

                    found = false;
                    break;
                }

                if (!found)
                    continue;

                return m_addr.offset(i);
            }

            return mem::addr_t();
        }

    public:
        bool safe(std::uintptr_t ptr) { return ptr >= m_addr && ptr <= m_addr.add(get_nt_headers()->OptionalHeader.SizeOfImage); }

    public:
        IMAGE_DOS_HEADER* get_dos_headers() { return m_addr.ptr<IMAGE_DOS_HEADER>(); }

        IMAGE_NT_HEADERS* get_nt_headers() { return m_addr.offset(get_dos_headers()->e_lfanew).ptr<IMAGE_NT_HEADERS>(); }

    protected:
        std::vector<int> pattern_to_byte(std::string_view pattern) {
            auto bytes = std::vector<int> {};
            auto start = const_cast<char*>(pattern.data());
            auto end = const_cast<char*>(start) + pattern.length();

            for (auto current = start; current < end; ++current) {
                if (*current == '?') {
                    ++current;

                    if (*current == '?')
                        ++current;

                    bytes.emplace_back(-1);
                } else
                    bytes.emplace_back(strtoul(current, &current, 16));
            }
            return bytes;
        }

    private:
        mem::addr_t m_addr;
    };
} // namespace util::mem

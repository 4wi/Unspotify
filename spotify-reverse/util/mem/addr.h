#pragma once
#include <cstdint>

namespace util::mem {
    template <typename ptr_type = std::uintptr_t>
    struct memory_address_t {
    public:
        //
        // constructors etc...
        memory_address_t() : m_ptr(ptr_type(0)) {};
        memory_address_t(ptr_type v) : m_ptr(v) {};
        memory_address_t(void* v) : m_ptr(ptr_type(v)) {};
        memory_address_t(const void* v) : m_ptr(ptr_type(v)) {};
        ~memory_address_t() = default;

        //
        // operators
        inline operator ptr_type() { return m_ptr; }

        inline operator void*() { return reinterpret_cast<void*>(m_ptr); }

        inline memory_address_t& operator+=(ptr_type offset) {
            m_ptr += offset;
            return *this;
        }

        inline memory_address_t& operator-=(ptr_type offset) {
            m_ptr -= offset;
            return *this;
        }

        inline memory_address_t operator-(ptr_type offset) { return memory_address_t<ptr_type>(m_ptr - offset); }

        inline memory_address_t operator+(ptr_type offset) { return add(offset); }

        inline bool operator>(ptr_type v2) { return m_ptr > v2; }

        inline bool operator>=(ptr_type v2) { return m_ptr >= v2; }

        inline bool operator<(ptr_type v2) { return m_ptr < v2; }

        inline bool operator<=(ptr_type v2) { return m_ptr <= v2; }

        inline memory_address_t add(ptr_type offset) { return memory_address_t<ptr_type>(m_ptr + offset); }

        template <typename t = uint32_t>
        inline memory_address_t rel(ptr_type offset) {
            return this->add(this->add(offset).template read<t>()).add(offset + sizeof(t));
        }

        //
        // utils
        memory_address_t<ptr_type> offset(ptr_type off) { return memory_address_t<ptr_type>(m_ptr + off); }

        template <typename T>
        T read() {
            return *ptr<T>();
        }

        template <typename T>
        T* read_ptr() {
            return read<T*>();
        }

        template <typename T>
        void write(T value) {
            *ptr<T>() = value;
        }

        template <typename T>
        T* ptr() {
            return reinterpret_cast<T*>(m_ptr);
        }

        template <typename T>
        T cast() {
            return reinterpret_cast<T>(m_ptr);
        }

        memory_address_t<ptr_type>& self_get(ptr_type count = 1) {
            for (ptr_type i = 0; i < count; i++)
                m_ptr = *reinterpret_cast<ptr_type*>(m_ptr);
            return *this;
        }

        memory_address_t<ptr_type> walk_until(uint8_t byte) {
            constexpr int max_iterations = 1000;
            for (int i = 0; i < max_iterations; i++) {
                if (offset(i).template read<uint8_t>() != byte)
                    continue;
                return offset(i);
            }
            return memory_address_t<ptr_type>();
        }

        memory_address_t<ptr_type> walk_back_until(uint8_t byte) {
            constexpr int max_iterations = 1000;
            for (int i = 1; i < max_iterations; i++) {
                if (offset(-i).template read<uint8_t>() != byte)
                    continue;
                return offset(-i);
            }
            return memory_address_t<ptr_type>();
        }

        inline bool valid() { return static_cast<bool>(m_ptr) && m_ptr > 15; }

        ptr_type raw() { return m_ptr; }

    private:
        ptr_type m_ptr;
    };
    using addr_t = mem::memory_address_t<std::uintptr_t>;
} // namespace util::mem
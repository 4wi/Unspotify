#pragma once
#include <Windows.h>


namespace bootstrap {
	namespace detail {
		inline HINSTANCE dll_handle;
		inline DWORD region_size;
	}

	DWORD __stdcall _initial_routine( HANDLE );

	bool startup( HINSTANCE handle );
	void _shutdown( );
}


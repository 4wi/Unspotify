#pragma once
#include <condition_variable>
#include <Windows.h>


namespace bootstrap {
	namespace _ {
		inline HINSTANCE dll_handle;
	}

	DWORD __stdcall _initial_routine( HANDLE );

	bool startup( HINSTANCE handle );
	void _shutdown( );
}


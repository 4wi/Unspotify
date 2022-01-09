#pragma once
#include <cstdint>
#include <Windows.h>


namespace exceptions {
	LONG __stdcall handler( EXCEPTION_POINTERS* info );
	void subscribe( );
}

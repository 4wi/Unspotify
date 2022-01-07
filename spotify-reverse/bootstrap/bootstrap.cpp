#include "bootstrap.h"
#include "../util/util.h"
#include "../spotify/spotify.h"
#include "../hooks/hooks.h"
#include "shared/logo.h"

#include <thread>


namespace bootstrap {
	DWORD __stdcall _initial_routine( HANDLE ) {
		util::logo::create_console_and_draw_logo( );

		spotify::init( );
		hooks::init( );

	#ifdef _DEBUG
		while ( !GetAsyncKeyState( VK_DELETE ) ) {
	#else
		util::logger::warn( "press any key to close this console" );
		_getwch( );
		util::logger::detach( );

		while ( true ) {
	#endif
			std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
		}

		_shutdown( );
		return 1; // unreachable but whatever
	}

	bool startup( HINSTANCE dll_handle ) {
		_::dll_handle = dll_handle;
		CreateThread( nullptr, 0, _initial_routine, 0, 0, nullptr );
		return true;
	}

	void _shutdown( ) {
		hooks::shutdown( );
		FreeLibraryAndExitThread( reinterpret_cast< HMODULE >( _::dll_handle ), 0x1 );
	}
}

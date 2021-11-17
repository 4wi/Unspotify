#include <Windows.h>
#include <cstdint>
#include <cstdio>
#include "injector/injector.h"


int main( ) {
	util::logo::create_console_and_draw_logo( );
	STARTUPINFO si = { .cb = sizeof( STARTUPINFO ) };
	PROCESS_INFORMATION pi = {};

	util::logger::debug( "Spawning oSpotify.exe" );
	if ( !CreateProcessW( L"oSpotify.exe", NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi ) ) {
		util::logger::error( "Unable to create process, error code: %d", GetLastError( ) );
		system( "pause" );
		goto END;
	}

	util::logger::debug( "Injecting spotify-reverse.dll" );
	if ( !injector::inject( pi.hProcess, "spotify-reverse.dll" ) ) {
		util::logger::error( "Unable to inject module, error code: %d", GetLastError( ) );
		TerminateProcess( pi.hProcess, 0x0 );
		system( "pause" );
		goto END;
	}
	
	ResumeThread(pi.hThread);
END:
	return EXIT_SUCCESS;
}
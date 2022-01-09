#pragma once
#include <Windows.h>
#include <urlmon.h>
#include <WinInet.h>

#include "ext/json.hpp"

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")


namespace util {
	namespace networking {
		nlohmann::json get( const char* domain, const char* url );
	}
}

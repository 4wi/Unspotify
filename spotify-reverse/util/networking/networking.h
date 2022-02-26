#pragma once
#include <Windows.h>
#include <urlmon.h>
#include <WinInet.h>
#include <map>

#include "ext/json.hpp"

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")


namespace util {
	namespace networking {
		using errorable_json_result = std::pair<nlohmann::json, bool>;
		constexpr const char* err_json_data = "{\"error\": \"Unable to connect to server\"}";

		errorable_json_result get( const char* domain, const char* url );
	}
}

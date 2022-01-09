#include "networking.h"


namespace util {
	namespace networking {
		nlohmann::json get( const char* domain, const char* url ) {
			std::string response_data = err_json_data;

			auto internet_session = InternetOpenA( "Unspotify/1.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0 );

			if ( !internet_session ) 
				return nlohmann::json::parse( response_data );

			auto http_session = InternetConnectA( internet_session, domain, 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL );

			if ( !http_session ) 
				return nlohmann::json::parse( response_data );

			HINTERNET http_req = HttpOpenRequestA( http_session, "GET", url, 0, 0, 0, INTERNET_FLAG_RELOAD, 0 );

			if ( !http_session ) 
				return nlohmann::json::parse( response_data );

			const char* szHeaders = "Content-Type: application/json\r\nUser-Agent: Unspotify/1.0";

			if ( !HttpSendRequestA( http_req, szHeaders, strlen( szHeaders ), NULL, NULL ) ) 
				return response_data;

			response_data.clear( );

			CHAR temp_buffer[ 1024 ] = { 0 };
			DWORD read_ret = 0;

			while ( InternetReadFile( http_req, temp_buffer, sizeof( temp_buffer ) - 1, &read_ret ) && read_ret )
				response_data.append( temp_buffer, read_ret );

			InternetCloseHandle( http_req );
			InternetCloseHandle( http_session );
			InternetCloseHandle( internet_session );
			
			try {
				return nlohmann::json::parse( response_data );
			} catch ( const nlohmann::json::parse_error& er ) {
				return nlohmann::json::parse( err_json_data );
			}
		}
	}
}

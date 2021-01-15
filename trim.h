#include <string>
#include <regex>

inline std::string ltrim( std::string str ) {
    return std::regex_replace( str, std::regex("^\\s+"), std::string("") );
}

inline std::string rtrim( std::string str ) {
    return std::regex_replace( str, std::regex("\\s+$"), std::string("") );
}

inline std::string trim( std::string str ) {
    return ltrim( rtrim( str ) );
}
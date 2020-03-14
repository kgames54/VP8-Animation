#define BASE64END      0
#define BASE64BUFEND    1

#include <stdio.h>
#include <string.h>
#define EXPORT_BASE __declspec(dllexport)

__declspec(dllexport) std::string base64_encode(unsigned char const*, unsigned int len);
__declspec(dllexport) std::string base64_decode(std::string const& s);
__declspec(dllexport) std::string  base64_file(char* filename);

#include "wincpp.hpp"
#include "tostring.hpp"



std::string tostring(const std::wstring& s, std::locale loc)
{
	using namespace std;
	const wchar_t* unicodestr = s.c_str();
	int lenW = static_cast<int>(s.length());
	int lenA = ::WideCharToMultiByte(CP_ACP, 0, unicodestr, lenW, 0, 0, NULL, NULL);
	if (lenA > 0) {
		vector<char> ansistr(lenA + 1);
		::WideCharToMultiByte(CP_ACP, 0, unicodestr, lenW, &ansistr[0], lenA, NULL, NULL);
		ansistr[lenA] = 0;
		return string(&ansistr[0]);
	}
	else {
		// handle the error
	}
	return string();
}

std::wstring towstring(const std::string& s, std::locale loc)
{
	using namespace std;
	const char* ansistr = s.c_str();
	int lenA = static_cast<int>(s.length());
	int lenW = ::MultiByteToWideChar(CP_ACP, 0, ansistr, lenA, 0, 0);
	if (lenW > 0) {
		vector<wchar_t> unicodestr(lenW + 1);
		::MultiByteToWideChar(CP_ACP, 0, ansistr, lenA, &unicodestr[0], lenW);
		unicodestr[lenW] = 0;
		return wstring(&unicodestr[0]);
	}
	else {
		// handle the error
	}

	return wstring();
}

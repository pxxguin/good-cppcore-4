#include "pch.h"
#include "StringFunc.h"

#include <cstdio>
#include <cstdlib>
#include <clocale>
#include <string>

// this is defined function
void PrintString(LPCTSTR str)
{
#ifdef UNICODE
	// convert to a narrow string instead of calling wprintf()
	size_t len = wcstombs(nullptr, str, 0);
	if (len != static_cast<size_t>(-1))
	{
		std::string narrow(len, '\0');
		wcstombs(&narrow[0], str, len);
		printf("%s\n", narrow.c_str());
	}
#else
	printf("%s\n", str);
#endif
}

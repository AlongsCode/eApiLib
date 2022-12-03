#pragma once
#include"myhelp.h"
#include"eapi.h"
VECTORBYTE GetEbin(unsigned char* pEbin) {
	return { *(size_t*)(pEbin + sizeof(size_t)), pEbin + sizeof(size_t) * 2 };
}

inline std::string 宽文本到文本(std::wstring 宽文本)
{
	int asciisize = ::WideCharToMultiByte(CP_ACP, 0, 宽文本.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (asciisize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	char* resultstring = new char[asciisize];

	int convresult = ::WideCharToMultiByte(CP_ACP, 0, 宽文本.c_str(), -1, resultstring, asciisize, NULL, NULL);
	if (convresult != asciisize)
	{
		throw std::exception("La falla!");
	}
	std::string Ret(resultstring);
	delete[]resultstring;
	return Ret;
}
char* W2Estr(std::wstring wstr) {
	return eapi_CloneTextData(const_cast<char*>(宽文本到文本(wstr).c_str()));
}
char* A2Estr(std::string str) {
	return eapi_CloneTextData(const_cast<char*>(str.c_str()));
}



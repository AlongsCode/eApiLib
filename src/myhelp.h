#pragma once
#include<string>
typedef struct _VECTORBYTE
{
	size_t size;
	unsigned char* data;
	_VECTORBYTE() {
		size = 0;
		data = 0;
	}
	_VECTORBYTE(size_t _size, unsigned char* _data) {
		size = _size;
		data = _data;
	}
} VECTORBYTE, * PVECTORBYTE;
VECTORBYTE GetEbin(unsigned char* pEbin);
char* W2Estr(std::wstring wstr);
char* A2Estr(std::string str);
 void NotifyShellA(long wEventId, char* dwItem1);


#include<windows.h>
#include<string>
#include <comdef.h>
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#include"eapi.h"
#include"myhelp.h"
using namespace std;
typedef struct _dmi_header
{
	BYTE type;
	BYTE length;
	WORD handle;
}dmi_header;

typedef struct _RawSMBIOSData
{
	BYTE    Used20CallingMethod;
	BYTE    SMBIOSMajorVersion;
	BYTE    SMBIOSMinorVersion;
	BYTE    DmiRevision;
	DWORD   Length;
	BYTE    SMBIOSTableData[];
}RawSMBIOSData;

const char* dmi_string(const dmi_header* dm, BYTE s)
{
	char* bp = (char*)dm;
	size_t i, len;

	if (s == 0)
		return "Not Specified";

	bp += dm->length;
	while (s > 1 && *bp)
	{
		bp += strlen(bp);
		bp++;
		s--;
	}

	if (!*bp)
		return "BAD_INDEX";

	/* ASCII filtering */
	len = strlen(bp);
	for (i = 0; i < len; i++)
		if (bp[i] < 32 || bp[i] == 127)
			bp[i] = '.';

	return bp;
}
//我本身是比较不喜欢使用COM的，但是BIOS在启动之后转交给操作系统了有些信息只能通过微软的接口获得。
BOOL GetBiosOther(wstring* ID, wstring* EMO, wstring* NAME) {
	BOOL Ret = FALSE;
	HRESULT hr = CoInitialize(0);
	if (FAILED(hr))
	{
		return FALSE;
	}
	hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);              // Reserved
	if (FAILED(hr))
	{
		CoUninitialize();
		return Ret;
	}
	IWbemLocator* pLoc = 0;
	hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hr))
	{
		CoUninitialize();
		return Ret;
	}
	IWbemServices* pSvc = 0;
	hr = pLoc->ConnectServer(BSTR(L"root\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (FAILED(hr))
	{
		pLoc->Release();
		CoUninitialize();
		return Ret;
	}
	hr = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (FAILED(hr))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return Ret;
	}
	IEnumWbemClassObject* pEnumerator = NULL;
	hr = pSvc->ExecQuery(bstr_t("WQL"), bstr_t("Select * FROM Win32_BIOS"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
	if (FAILED(hr))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return Ret;
	}
	IWbemClassObject* pclsObj = NULL;
	while (pEnumerator)
	{
		ULONG uReturn = 0;
		hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)
			break;
		VARIANT vtProp = { 0 };
		hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		
		wchar_t* _NAME = vtProp.bstrVal;
		*NAME = _NAME;
		hr = pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
		wchar_t* _EMO = vtProp.bstrVal;
		*EMO = _EMO;
		hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
		wchar_t* _ID = vtProp.bstrVal;
		*ID = _ID;
		VariantClear(&vtProp);

	}
	if (pclsObj != NULL) {
		pclsObj->Release();
	}
	if (pEnumerator != NULL) {
		pEnumerator->Release();
	}
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();
	return TRUE;
}
void GetBiosInfo(BIOSINFO* pBIOSINFO)
{

	int ret = 0;
	RawSMBIOSData* Smbios;
	dmi_header* h = NULL;
	int flag = 1;
	ret = GetSystemFirmwareTable('RSMB', 0, 0, 0);
	if (!ret)
	{
		return;
	}
	DWORD bufsize = ret;
	char* buf = new char[bufsize];
	memset(buf, 0, bufsize);

	ret = GetSystemFirmwareTable('RSMB', 0, buf, bufsize);
	if (!ret)
	{
		return;
	}

	Smbios = (RawSMBIOSData*)buf;

	BYTE* p = Smbios->SMBIOSTableData;

	if (Smbios->Length != bufsize - 8)
	{
		delete[]buf;
		return;
	}
	for (int i = 0; i < Smbios->Length; i++) {
		h = (dmi_header*)p;
	}
	for (int i = 0; i < Smbios->Length; i++) {
		if (h->type == 0 && flag) {

			pBIOSINFO->manufacturer = A2Estr(dmi_string(h, p[0x4]));
			pBIOSINFO->version = A2Estr(dmi_string(h, p[0x5]));
			pBIOSINFO->data = A2Estr(dmi_string(h, p[0x8]));
		}
	}
	
	wstring ID, OEM, NAME;
	GetBiosOther(&ID, &OEM, &NAME);
	pBIOSINFO->name = W2Estr(NAME);
	pBIOSINFO->ID = W2Estr(ID);
	pBIOSINFO->OEM = W2Estr(OEM);
	delete[]buf;
	return;
}



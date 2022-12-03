#include"windows.h"
#include"string"
#include"shlwapi.h"
#include"shlobj_core.h"
using namespace std;
#pragma comment(lib,"shlwapi.lib")


static inline bool CreateLink(LPCSTR path, LPCSTR name) {
	bool result = false;
	IShellLinkA* piShellLink = { 0 };
	IPersistFile* piPersistFile = { 0 };
	WCHAR WideCharStr[MAX_PATH] = { 0 };
	if (!SUCCEEDED(CoInitialize(NULL))) {
		return 0;
	};
	if (CoCreateInstance(CLSID_ShellLink, 0, CLSCTX_INPROC_SERVER, IID_IShellLinkA, (void**)&piShellLink) >= 0)
	{
		piShellLink->SetPath(path);
		if (piShellLink->QueryInterface(IID_IPersistFile, (void**)&piPersistFile) >= 0)
		{
			MultiByteToWideChar(0, 0, name, -1, WideCharStr, MAX_PATH);
			piPersistFile->Save(WideCharStr, 2);
			piPersistFile->Release();
			piShellLink->Release();
			result = true;
		}
	}
	return result;
}
void NotifyShellA(LONG wEventId, CHAR* szPath)//路径
{
	SHChangeNotify(wEventId, SHCNF_FLUSH | SHCNF_PATH, szPath, 0);

	CHAR* p;
	for (p = szPath + strlen(szPath) - 1; *p != '\\'; p--);
	*p = '\0';
	SHChangeNotify(SHCNE_UPDATEDIR | SHCNE_INTERRUPT, SHCNF_FLUSH | SHCNF_PATH, szPath, 0);
};
bool SetAutoRun(string lpValueName, string path, bool toreskey) {
	HKEY phkResult;

	if (!PathFileExistsA(path.c_str()))//判断文件是否存在
	{
		return false;
	}
	if (toreskey)
	{
		if (!RegOpenKeyA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &phkResult)) {
			if (!RegSetValueExA(phkResult, lpValueName.c_str(), 0, REG_SZ, (LPBYTE)path.c_str(), (path.size() + 1) * sizeof(char)))
			{
				RegCloseKey(phkResult);
				return true;
			}
			RegCloseKey(phkResult);
		}
		return false;
	}
	char pszPath[MAX_PATH];
	::SHGetSpecialFolderPathA(NULL, pszPath, CSIDL_STARTUP, TRUE);
	wsprintfA(pszPath, "%s\\%s.lnk", &pszPath, lpValueName.c_str());
	if (CreateLink(path.c_str(), pszPath)) {
		NotifyShellA(SHCNE_CREATE | SHCNE_INTERRUPT, pszPath);
		return true;
	}
	return false;
}
bool DeleteTmpFile(string lpValueName)
{
	bool Ret = false;
	HKEY phkResult;
	CHAR pszPath[MAX_PATH];


	if (!RegOpenKeyA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &phkResult))
	{
		if (!RegDeleteValueA(phkResult, lpValueName.c_str())) {
			Ret = 1;
		}
		RegCloseKey(phkResult);
	}
	SHGetSpecialFolderPathA(0, pszPath, 7, 0);
	wsprintfA(pszPath, "%s\\%s.lnk", &pszPath, lpValueName.c_str());
	if (DeleteFileA(pszPath) == 1)
		Ret = 1;
	NotifyShellA(SHCNE_DELETE | SHCNE_INTERRUPT, pszPath);
	return Ret;
}





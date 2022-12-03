#include<windows.h>
#include"string"
#include"shlobj_core.h"
#include"shlwapi.h"
#include<wininet.h>
#pragma comment(lib,"wininet.lib")
#pragma comment(lib,"shlwapi.lib")
using namespace std;


BOOL ClearDir(const WCHAR* path)
{
    wstring  lpFileName = path;
    WIN32_FIND_DATAW FindFileData;
    if (lpFileName[lpFileName.size()] != L'\\')
    {
        lpFileName += L"\\";
    }
    lpFileName += L"*.*";
    HANDLE hFindFile = FindFirstFileW(lpFileName.c_str(), &FindFileData);
    bool result = 0;
    if (hFindFile == INVALID_HANDLE_VALUE)
    {
        result = 0;
    }
    else
    {
        BOOL IsHas = FALSE;
        do
        {
            IsHas = FindNextFileW(hFindFile, &FindFileData);
            if (wcscmp(FindFileData.cFileName, L".")
                && wcscmp(FindFileData.cFileName, L"..")) {
                ClearDir(FindFileData.cFileName);
            }
            else
            {
                DeleteFileW(lpFileName.c_str());
            }
        } while (IsHas);
        FindClose(hFindFile);
        result = 1;
    }
    return result;
}

bool WipeFile(const WCHAR* path, const WCHAR* name)
{

    DWORD NumberOfBytesWritten;
    bool result = false;
    WCHAR* Buffer = new WCHAR[0x2710u];
    wstring lpFileName = wstring(path) + L"\\" + name;
    HANDLE hFile = CreateFileW(lpFileName.c_str(), 0x40000000u, 3u, 0, 3u, 0x80u, 0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        result = 0;
    }
    else
    {
        DWORD FileSize = GetFileSize(hFile, 0) - 64;
        SetFilePointer(hFile, 64, 0, 0);
        if (FileSize)
        {
            while (FileSize > 0x2710)
            {
                WriteFile(hFile, &Buffer, 0x2710u, &NumberOfBytesWritten, 0);
                FileSize -= 10000;
                if (!FileSize) {
                    break;
                }
            }
            WriteFile(hFile, &Buffer, FileSize, &NumberOfBytesWritten, 0);
        }
        CloseHandle(hFile);
        result = 1;
    }
    return result;
}
bool EmptyDirectory(const WCHAR* Path, int type1, int type2) {
    wstring lpPathName, lpFileName = wstring(Path) + L"\\*.*";
    WIN32_FIND_DATAW FindFileData;
    HANDLE hFindFile = FindFirstFileW(lpFileName.c_str(), &FindFileData);
    bool result = 0;
    if (hFindFile == INVALID_HANDLE_VALUE)
    {
        result = 0;
    }
    else
    {
        do
        {
            if (wcscmp(FindFileData.cFileName, L".")
                && wcscmp(FindFileData.cFileName, L"..")
                && (type1 || wcscmp(FindFileData.cFileName, L"desktop.ini")))
            {
                lpPathName = wstring(Path) + L"\\" + FindFileData.cFileName;

                DWORD dwFileAttributes = GetFileAttributesW(lpPathName.c_str());
                if (GetFileAttributesW(lpPathName.c_str()) & FILE_ATTRIBUTE_READONLY)
                {
                    dwFileAttributes &= 0xFE;
                }
                if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    EmptyDirectory(lpPathName.c_str(), type1, type2);
                    RemoveDirectoryW(lpPathName.c_str());
                }
                else
                {
                    if (type2 && !wcscmp(FindFileData.cFileName, L"index.dat"))
                        WipeFile(Path, FindFileData.cFileName);
                    DeleteFileW(lpPathName.c_str());
                }
            }
        } while (FindNextFileW(hFindFile, &FindFileData));
        FindClose(hFindFile);
        result = 1;
    }
    return result;
}
bool  DeleteUrlCache(int fun)
{
    bool ret = 0;
    INTERNET_CACHE_ENTRY_INFOW* pData;

    DWORD cbCacheEntryInfo;


    cbCacheEntryInfo = 0;
    FindFirstUrlCacheEntryW(0, 0, &cbCacheEntryInfo);
    pData = (INTERNET_CACHE_ENTRY_INFOW*)malloc(cbCacheEntryInfo);
    if (!pData)
    {
        return false;
    }
    memset(pData, 0, cbCacheEntryInfo);
    HANDLE hUrl = FindFirstUrlCacheEntryW(0, pData, &cbCacheEntryInfo);
    if (hUrl)
    {
        do
        {
            if (fun)
            {
                if (fun == 1 && pData->CacheEntryType & COOKIE_CACHE_ENTRY)
                    DeleteUrlCacheEntryW(pData->lpszSourceUrlName);
            }
            else if (!(pData->CacheEntryType & COOKIE_CACHE_ENTRY))
            {
                DeleteUrlCacheEntryW(pData->lpszSourceUrlName);
            }
            cbCacheEntryInfo = 0;
            FindNextUrlCacheEntryW(hUrl, 0, &cbCacheEntryInfo);
            free(pData);
            pData = (INTERNET_CACHE_ENTRY_INFOW*)malloc(cbCacheEntryInfo);
            if (!pData)
            {
                return false;
            }
            memset(pData, 0, cbCacheEntryInfo);
        } while (FindNextUrlCacheEntryW(hUrl, pData, &cbCacheEntryInfo));
        ret = 1;
    }
    if (pData)
        free(pData);
    return ret;
}
int DeleteTempFile(int type)
{
    BOOL result = 0;
    WCHAR Buffer[MAX_PATH] = { 0 };
    switch (type)
    {
    case 0:
        if (!GetTempPathW(MAX_PATH, Buffer)) {
            result = 0;
            break;
        }
        result = EmptyDirectory(Buffer, 1, 0);
        break;
    case 1:
        result = DeleteUrlCache(0);
        if (!SHGetSpecialFolderPathW(0, Buffer, 32, 0)) {
            result = 0;
            break;
        }
        ClearDir(Buffer);
        break;
    case 2:
        result = SHEmptyRecycleBinA(0, 0, 7u) == 0;
        break;
    case 3:
        result = DeleteUrlCache(1);
        if (SHGetSpecialFolderPathW(0, Buffer, 33, 0)) {
            ClearDir(Buffer);
        }
        break;
    default:
        break;
    }
    return result;
}

/*可以被省略。临时文件类型，可以为以下常量值之一：0、#接口常量.系统临时文件；1、#接口常量.IE临时文件；2、#接口常量.回收站；3、#接口常量.存根文件。*/
bool 删除临时文件(int 临时文件类型) {
    return DeleteTempFile(临时文件类型);
}





BOOL IsWindowsNT();

BOOL IsWindows2k();

INT g_nIndex = 0;
PSID* GetUserSid(void** arg)
{
    PSID* result = 0;
    DWORD lenthtemp1, lenthtemp2;
    HANDLE hProcess;
    PSID* temp;
    DWORD sidlenth, sidlenthtrmp;
    SIZE_T sidsize;
    HANDLE hprocess;
    void* argval;
    HANDLE hdui;
    HANDLE hproceherp;
    DWORD ReturnLength = 0;
    HANDLE TokenHandle = 0;
    HANDLE hcProcess = GetCurrentProcess();
    result = (PSID*)OpenProcessToken(hcProcess, 8u, &TokenHandle);
    if (result)
    {
        GetTokenInformation(TokenHandle, TokenUser, 0, 0, &ReturnLength);
        if (GetLastError() == 122)
        {
            lenthtemp1 = ReturnLength;
            lenthtemp2 = ReturnLength;
            hProcess = GetProcessHeap();
            result = (PSID*)HeapAlloc(hProcess, 0, lenthtemp1);
            temp = result;
            if (result)
            {
                result = (PSID*)GetTokenInformation(TokenHandle, TokenUser, result, lenthtemp2, &ReturnLength);
                if (result)
                {
                    sidlenth = GetLengthSid(*temp);
                    sidlenthtrmp = sidlenth;
                    sidsize = sidlenth;
                    hprocess = GetProcessHeap();
                    result = (PSID*)HeapAlloc(hprocess, 0, sidsize);
                    *arg = result;
                    if (result)
                    {
                        if (CopySid(sidlenthtrmp, result, *temp))
                        {
                            hproceherp = GetProcessHeap();
                            HeapFree(hproceherp, 0, temp);
                            result = (PSID*)(&g_nIndex + 1);
                        }
                        else
                        {
                            argval = *arg;
                            hdui = GetProcessHeap();
                            HeapFree(hdui, 0, argval);
                            result = 0;
                        }
                    }
                }
            }
        }
        else
        {
            result = 0;
        }
    }
    return result;
}
char* GetSidString(PSID pSid, char* Dest)
{
    PSID tmpsid = pSid;
    PSID_IDENTIFIER_AUTHORITY siddata;
    char* str = Dest;
    DWORD size = 0;
    char* result;
    PDWORD lenth;
    char lenstr[10] = { 0 };
    char* Desta;

    siddata = GetSidIdentifierAuthority(pSid);
    sprintf(Dest, "S-1-%lu", siddata->Value[5]);
    result = (char*)*GetSidSubAuthorityCount(pSid);
    Desta = result;
    if ((signed int)result > 0)
    {
        while (1)
        {
            lenth = GetSidSubAuthority(tmpsid, size);
            sprintf(lenstr, "%lu", *lenth);
            strcat(str, "-");
            strcat(str, lenstr);
            result = Desta;
            if ((signed int)++size >= (signed int)Desta)
                break;
            tmpsid = pSid;
        }
    }
    return result;
}
std::wstring A2W(std::string str)
{
    int widesize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)
    {
        throw std::exception("Invalid UTF-8 sequence.");
    }
    if (widesize == 0)
    {
        throw std::exception("Error in conversion.");
    }
    wchar_t* resultstring = new wchar_t[widesize];

    int convresult = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, resultstring, widesize);
    if (convresult != widesize)
    {
        throw std::exception("La falla!");
    }
    std::wstring wstrReturn(resultstring);
    delete[] resultstring;
    return wstrReturn;
}
bool  GetOldSD(HKEY hKey, LPCWSTR lpSubKey, PSECURITY_DESCRIPTOR* size)
{
    bool ret = false;
    LSTATUS errcode;
    void* retp;
    HKEY phk;
    HKEY phkResult;
    DWORD cbSecurityDescriptor;

    phkResult = 0;
    cbSecurityDescriptor = 0;
    *size = 0;
    if (!RegOpenKeyExW(hKey, lpSubKey, 0, 0x20000u, &phkResult))
    {
        errcode = RegGetKeySecurity(phkResult, 4u, *(PSECURITY_DESCRIPTOR*)size, &cbSecurityDescriptor);
        if (errcode == 122)
        {
            retp = malloc(cbSecurityDescriptor);
            phk = phkResult;
            *size = (PSECURITY_DESCRIPTOR)retp;
            if (RegGetKeySecurity(phk, 4u, retp, &cbSecurityDescriptor))
            {
                free(size);
                *size = 0;
                goto over;
            }
        }
        else if (errcode)
        {
            goto over;
        }
        ret = 1;
    }
over:
    if (phkResult)
        RegCloseKey(phkResult);
    return ret;
}
BOOL CreateNewSD(PSID a1, PSECURITY_DESCRIPTOR pSecurityDescriptor, PACL* arg)
{
    DWORD fsize;
    SIZE_T faclsize;
    HANDLE hproc;
    ACL* pAcl1;
    DWORD ssize;
    DWORD saclsize;
    SIZE_T tempaclsize;
    HANDLE hprocess;
    PACL pAcl2;
    HANDLE hProc;
    DWORD taclsize;
    DWORD tsize_;
    SIZE_T tsize_trmp;
    HANDLE hPRoc;
    DWORD sizepSid;
    HANDLE hdui;
    PSID pSid;
    BOOL ret;
    SID_IDENTIFIER_AUTHORITY pIdentifierAuthority;

    ret = 0;
    pSid = 0;
    pIdentifierAuthority.Value[0] = 0;
    pIdentifierAuthority.Value[1] = 0;
    pIdentifierAuthority.Value[2] = 0;
    pIdentifierAuthority.Value[3] = 0;
    pIdentifierAuthority.Value[4] = 0;
    pIdentifierAuthority.Value[5] = 5;
    if (AllocateAndInitializeSid(&pIdentifierAuthority, 1u, 0x12u, 0, 0, 0, 0, 0, 0, 0, &pSid))
    {
        fsize = GetLengthSid(pSid);
        faclsize = fsize + GetLengthSid(a1) + 24;
        hproc = GetProcessHeap();
        pAcl1 = (ACL*)HeapAlloc(hproc, 0, faclsize);
        *arg = pAcl1;
        if (pAcl1)
        {
            if (InitializeAcl(pAcl1, faclsize, 2u))
            {
                ssize = GetLengthSid(a1);
                saclsize = ssize + sizeof(ACL);
                tempaclsize = ssize + sizeof(ACL);
                hprocess = GetProcessHeap();
                pAcl2 = (PACL)HeapAlloc(hprocess, HEAP_ZERO_MEMORY, tempaclsize);
                pAcl2->AclRevision = ACL_REVISION3;
                pAcl2->AceCount = 983103;
                pAcl2->AclSize = saclsize;
                memcpy((char*)(&pAcl2[1]), a1, GetLengthSid(a1));
                if (AddAce(*(PACL*)arg, 2u, 0xFFFFFFFF, pAcl2, saclsize))
                {
                    hProc = GetProcessHeap();
                    HeapFree(hProc, 0, pAcl2);
                    taclsize = GetLengthSid(pSid);
                    tsize_ = taclsize + sizeof(ACL);
                    tsize_trmp = taclsize + sizeof(ACL);
                    hPRoc = GetProcessHeap();
                    pAcl2 = (PACL)HeapAlloc(hPRoc, HEAP_ZERO_MEMORY, tsize_trmp);
                    pAcl2->AclRevision = ACL_REVISION3;
                    pAcl2->AceCount = 983103;
                    pAcl2->AclSize = tsize_;
                    sizepSid = GetLengthSid(pSid);
                    memcpy((char*)(&pAcl2[1]), pSid, sizepSid);
                    if (AddAce(*(PACL*)arg, 2u, 0xFFFFFFFF, pAcl2, tsize_))
                    {
                        if (InitializeSecurityDescriptor(pSecurityDescriptor, 1u)
                            && SetSecurityDescriptorDacl(pSecurityDescriptor, 1, *(PACL*)arg, 0))
                        {
                            ret = 1;
                        }
                    }
                }
                if (pAcl2)
                {
                    hdui = GetProcessHeap();
                    HeapFree(hdui, 0, pAcl2);
                }
            }
        }
    }
    if (pSid)
        FreeSid(pSid);
    return ret;
}
bool RegSetPrivilege(HKEY hKey, LPCWSTR lpSubKey, PSECURITY_DESCRIPTOR pSecurityDescriptor, int a5)
{
    const WCHAR* psudke;
    bool ret;
    HKEY pkey;
    WCHAR* temp;
    DWORD size;
    LSTATUS errcode;
    HKEY phkResult;
    DWORD cbMaxValueNameLen;
    DWORD cValues;
    DWORD cbMaxSubKeyLen;
    psudke = lpSubKey;
    ret = 0;
    phkResult = 0;
    if (!lpSubKey)
        return ret;
    pkey = hKey;
    if (!RegOpenKeyExW(hKey, lpSubKey, 0, 0x40000u, &phkResult) && !RegSetKeySecurity(phkResult, 4u, pSecurityDescriptor))
    {
        if (!a5)
        {
        begin:
            ret = 1;
            goto over;
        }
        RegCloseKey(phkResult);
        phkResult = 0;
        if (!RegOpenKeyExW(pkey, psudke, 0, 0x20019u, &phkResult)
            && !RegQueryInfoKeyW(
                phkResult,
                0,
                0,
                0,
                (LPDWORD)&lpSubKey,
                &cbMaxSubKeyLen,
                0,
                &cValues,
                &cbMaxValueNameLen,
                (LPDWORD)&hKey,
                0,
                0))
        {
            temp = new wchar_t[MAX_PATH + 1];
            size = 0;
            if (lpSubKey)
            {
                do
                {
                    errcode = RegEnumKeyW(phkResult, size, temp, 0x105u);
                    if (errcode)
                    {
                        if (errcode == 259)
                            break;
                    }
                    else
                    {
                        RegSetPrivilege(phkResult, temp, pSecurityDescriptor, 1);
                    }
                    ++size;
                } while (size < (unsigned int)lpSubKey);
            }
            delete[]temp;
            goto begin;
        }
    }
over:
    if (phkResult)
        RegCloseKey(phkResult);
    return ret;
}
BOOL ClearHistory(int arg)
{
    PSECURITY_DESCRIPTOR pcbBuffer;
    SECURITY_DESCRIPTOR pSecurityDescriptor = { 0 };
    LSTATUS errky = 0;
    LPSTR pszValue;
    wstring lpSubKey, szSubKey;
    string  pszSubKey;
    PACL lpMem = 0;
    CHAR Buffer[20] = { 0 };
    intptr_t erro;
    BOOL ret = FALSE;
    WCHAR pszPath[MAX_PATH] = { 0 };
    string comminw;
    DWORD index;
    INT type = 0;
    WCHAR* wstrw;
    switch (arg)
    {
    case 0:
        errky = SHDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Internet Explorer\\TypedURLs");
        goto over;
    case 1:
        if (IsWindows2k() || IsWindowsNT())
        {
            if (GetUserSid((void**)&pszValue))
            {
                GetSidString((PSID)pszValue, Buffer);

                lpSubKey = A2W(pszSubKey);
                szSubKey = lpSubKey;
                GetOldSD(HKEY_CURRENT_USER, lpSubKey.c_str(), &pcbBuffer);
                if (CreateNewSD((PSID)pszValue, &pSecurityDescriptor, &lpMem))
                {
                    RegSetPrivilege(HKEY_CURRENT_USER, szSubKey.c_str(), &pSecurityDescriptor, 0);
                    szSubKey += L"\\Data";
                    RegSetPrivilege(HKEY_CURRENT_USER, szSubKey.c_str(), &pSecurityDescriptor, 0);
                    szSubKey += L"\\e161255a-37c3-11d2-bcaa-00c04fd929db";
                    RegSetPrivilege(HKEY_CURRENT_USER, szSubKey.c_str(), &pSecurityDescriptor, 1);
                    erro = SHDeleteKeyW(HKEY_CURRENT_USER, szSubKey.c_str());
                }
                else
                {
                    erro = (intptr_t)pcbBuffer;
                }
                if (lpMem)
                {
                    HeapFree(GetProcessHeap(), 0, lpMem);
                }
                if (pcbBuffer)
                {
                    RegSetPrivilege(HKEY_CURRENT_USER, lpSubKey.c_str(), (PSECURITY_DESCRIPTOR)pcbBuffer, 0);
                    free(pcbBuffer);
                }
            }
            else
            {
                erro = (intptr_t)pcbBuffer;
            }
            if (pszValue)
            {

                HeapFree(GetProcessHeap(), 0, pszValue);
            }
        }
        else
        {
            DWORD size = MAX_PATH;
            WCHAR wstr[MAX_PATH + 1] = { 0 };
            GetUserNameW(wstr, &size);
            wstring comline = L"Software\\Microsoft\\Protected Storage System Provider\\" + wstring(wstr) + L"\\Data\\e161255a-37c3-11d2-bcaa-00c04fd929db";

            erro = SHDeleteKeyW(HKEY_LOCAL_MACHINE, comline.c_str());
        }
        ret = erro == 0;

        break;
    case 2:
        errky = SHDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Internet Explorer\\IntelliForms");
        goto over;
    case 3:
        if (!SHGetSpecialFolderPathW(0, pszPath, 6, 0))
            break;
        type = 0;
        wstrw = pszPath;
        goto begin;
    case 4:
        errky = SHDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Microsoft\\RAS Autodial\\Addresses");
        goto over;
    case 5:
        errky = SHDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU");
        goto over;
    case 6:
        if (SHGetSpecialFolderPathW(0, pszPath, 8, 0) && EmptyDirectory(pszPath, 0, 0))
        {
            errky = SHDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RecentDocs");
        over:
            ret = errky == 0;
        }
        break;
    case 7:
        if (!SHGetSpecialFolderPathW(0, pszPath, 19, 0))
            break;
        type = 0;
        wstrw = pszPath;
        goto begin;
    case 8:

        index = 1;
        do
        {
            comminw = "Machine" + to_string(index);
            SHDeleteValueA(HKEY_CURRENT_USER, "Software\\Microsoft\\Telnet", pszValue);
            comminw = "Service" + to_string(index);

            SHDeleteValueA(HKEY_CURRENT_USER, "Software\\Microsoft\\Telnet", pszValue);
            comminw = "TermType" + to_string(index);

            SHDeleteValueA(HKEY_CURRENT_USER, "Software\\Microsoft\\Telnet", pszValue);
            ++index;
        } while (index <= 8);
        SHDeleteValueA(
            HKEY_CURRENT_USER,
            "Software\\Microsoft\\Telnet",
            "LastMachine");
        SHDeleteValueA(
            HKEY_CURRENT_USER,
            "Software\\Microsoft\\Telnet",
            "LastService");
        SHDeleteValueA(
            HKEY_CURRENT_USER,
            "Software\\Microsoft\\Telnet",
            "LastTermType");
        ret = 1;
        break;
    case 9:
        GetWindowsDirectoryW(pszPath, MAX_PATH);
        wcscat(pszPath, L"\History");
        EmptyDirectory(pszPath, 0, 1);
        if (SHGetSpecialFolderPathW(0, pszPath, 34, 0))
        {
            type = 1;
            wstrw = pszPath;
        begin:
            ret = EmptyDirectory(wstrw, 0, type);
        }
        break;
    default:
        break;
    }
    BOOL result = ret;
    return result;
}



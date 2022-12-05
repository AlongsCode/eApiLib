#include"windows.h"
#include"eapi.h"
#include"syse.h"
#include<shlobj_core.h>
#include<shlwapi.h>
#include"myhelp.h"
#include"tlhelp32.h"
#include"gdiplus.h"
#include <direct.h>
#include<iphlpapi.h>
#include<wininet.h>
#include<lmcons.h>
#include<lmmsg.h>
#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment(lib, "Version.lib")
#pragma comment(lib,"Iphlpapi.lib")
#pragma comment(lib,"Netapi32.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib, "mpr.lib")
using namespace std;

//大部分命令都写在这了，几千行说实话静态编译都链接进去太傻逼，但是再写一页cpp我又嫌麻烦，想优化的自己优化一下把


using namespace Gdiplus;//GDI+对象
using namespace DllExports;//GDI+接口
/*************************取键盘呢指示灯状态****************************/
BOOL  GetKeyboardLockState(int Type)
{
    BOOL result = FALSE; BYTE KeyState[256] = { 0 };
    if (GetKeyboardState(KeyState))
    {
        if (Type == 1)
        {
            result = KeyState[VK_CAPITAL] & 1;
        }
        else if (Type == 2)
        {
            result = KeyState[VK_SCROLL] & 1;
        }
        else
        {
            result = KeyState[VK_NUMLOCK] & 1;
        }
    }
    return result;
}
/*************************模拟按键****************************/
//取键值
BYTE MyVkKeyScanExA(MDATA_INF pArgInf) {
    HKL hKl = GetKeyboardLayout(0);
    BYTE ret = 0;
    //文本型
    if (pArgInf.m_dtDataType == SDT_TEXT) {
        if (strlen(pArgInf.m_pText) > 0)
        {
            ret = VkKeyScanExA(*(char*)pArgInf.m_pText, hKl);
        }
    }//宽字符
    if (pArgInf.m_dtDataType == SDT_BIN) {
        VECTORBYTE Ebin = GetEbin(pArgInf.m_pBin);
        if (Ebin.size >= 2) {
            ret = VkKeyScanExW(*(wchar_t*)Ebin.data, hKl);
        }
    }
    else {//字节、整数、短整数
            ret = pArgInf.m_byte;
    }
    return ret;
}
void  SimulateKey(BYTE bVk, BYTE bVk2, BYTE bVk3)
{
    //按下
    keybd_event(bVk, 0, 0, 0);
    if (bVk2) {
        keybd_event(bVk2, 0, 0, 0);
    }
    if (bVk3) {
        keybd_event(bVk3, 0, 0, 0);
    }
     //松开
    keybd_event(bVk, 0, KEYEVENTF_KEYUP, 0);
    if (bVk2) {
        keybd_event(bVk2, 0, KEYEVENTF_KEYUP, 0);
    }
    if (bVk3) {
        keybd_event(bVk3, 0, KEYEVENTF_KEYUP, 0);
    } 
}
/*************************模拟鼠标点击****************************/
void SimulateMouse(int X, int Y, int Type)
{
    SetCursorPos(X, Y);
    switch (Type)
    {
    case 1:
        mouse_event(2u, X, Y, 0, 0);
        mouse_event(4u, X, Y, 0, 0);
        mouse_event(2u, X, Y, 0, 0);
        mouse_event(4u, X, Y, 0, 0);
        break;
    case 2:
        mouse_event(8u, X, Y, 0, 0);
        mouse_event(0x10u, X, Y, 0, 0);
        break;
    case 3:
        mouse_event(8u, X, Y, 0, 0);
        mouse_event(0x10u, X, Y, 0, 0);
        mouse_event(8u, X, Y, 0, 0);
        mouse_event(0x10u, X, Y, 0, 0);
        break;
    default:
        mouse_event(2u, X, Y, 0, 0);
        mouse_event(4u, X, Y, 0, 0);
        break;
    }
}


/*************************取驱动器数量****************************/
INT GetDrivesNum(INT type)
{
    int af = 26, ret = 0;
    unsigned char hd = 65;
    do
    {
        char lpRootPathName[3] = { hd,58,0 };
        if (type)
        {
            if (GetDriveTypeA(lpRootPathName) == type)
                jmp:
            ++ret;
        }
        else
        {
            switch (GetDriveTypeA(lpRootPathName))
            {
            case 2u:
            case 3u:
            case 4u:
            case 5u:
                goto jmp;
            default:
                break;
            }
        }
        ++hd;
        --af;
    } while (af);

    return ret;
}


/*************************取驱动器列表****************************/
inline vector<string> GetDrivesListA(int Type)
{
    bool IsnOver = 0;
    int AHl = 26;
    unsigned char DIs = 65;
    vector<string> ret;
    do
    {
        char lpRootPathName[3] = { DIs,58,0 };
        if (Type)
        {
            if (GetDriveTypeA(lpRootPathName) == Type)
            {
            jmp:
                ret.push_back(lpRootPathName);
            }
        }
        else
        {
            switch (GetDriveTypeA(lpRootPathName))
            {
            case 2u:
            case 3u:
            case 4u:
            case 5u:
                goto jmp;
            default:
                break;
            }
        }
        IsnOver = AHl == 1;
        ++DIs;
        --AHl;
    } while (!IsnOver);


    return ret;
}
vector<string> GetDrivesList(int type)
{
    vector<string> ret;
    switch (type)
    {
    case 0:
        ret = GetDrivesListA(0);
        break;
    case 1:
        ret = GetDrivesListA(3);
        break;
    case 2:
        ret = GetDrivesListA(5);
        break;
    case 3:
        ret = GetDrivesListA(2);
        break;
    case 4:
        ret = GetDrivesListA(4);
        break;
    default:
        break;
    }
    return ret;
}

/*************************弹出关闭光驱****************************/
MCIERROR ControlCdrom(bool pop)
{
    MCIERROR result;

    if (pop)
        result = mciSendStringW(L"Set cdaudio door open wait", 0, 0, 0);
    else
        result = mciSendStringW(L"Set cdaudio door closed wait", 0, 0, 0);
    return result;
}

/*************************取光驱盘符****************************/
char* GetCdrom()
{
    char ahl = 'A';
    char str[3] = { ahl ,':','\0' };
    while (1)
    {
        str[0] = ahl;

        if (GetDriveTypeA(str) == 5)
            break;
        if (++ahl >= 90)
        {
            return 0;
        }
    }
    char* ret = (char*)eapi_MMalloc(sizeof(str));
    strcpy(ret, str);
    return ret;
}
/*************************光驱中是否有盘****************************/
BOOL IsDiskInside() {

    wchar_t ahl = L'A';
    wchar_t str[3] = { ahl ,L':',L'\0' };
    while (1)
    {
        str[0] = ahl;

        if (GetDriveTypeW(str) == 5)
            break;
        if (++ahl >= 90)
        {
            return 0;
        }
    }
    return GetVolumeInformationW(str, 0, 0, 0, 0, 0, 0, 0);

}

/*************************取进程信息列表****************************/
vector<PROCINF> GetProcessList()
{
    vector<PROCINF> ret;
    PROCINF temp;
    HANDLE hSnap;
    PROCESSENTRY32 pe;
    hSnap = CreateToolhelp32Snapshot(2u, 0);
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnap, &pe))
    {
        do
        {
            temp.identifier = pe.th32ProcessID;
            temp.name = (char*)eapi_MMalloc(MAX_PATH);
            memset(temp.name, 0, MAX_PATH);
            strcpy(temp.name, pe.szExeFile);
            temp.modidentifier = pe.th32ModuleID;
            temp.pidentifier = pe.th32ParentProcessID;
            temp.priority = pe.pcPriClassBase;
            temp.size = pe.cntThreads;
            ret.push_back(temp);
        } while (Process32Next(hSnap, &pe));
    }
    CloseHandle(hSnap);

    return ret;
}

/*************************终止进程****************************/

BOOL KillProcess(int ID)
{
    DWORD dwProcessId = 0;
    BOOL result = false;
    if (ID)
    {
        dwProcessId = ID;
    }
    if (dwProcessId)
    {
        HANDLE hPros = OpenProcess(1u, 0, dwProcessId);
        result = TerminateProcess(hPros, 0);
    }
    else
    {
        result = 0;
    }
    return result;
}
BOOL KillProcess(char* TEXT)
{
    DWORD dwProcessId = 0;
    bool result = false;
    HWND 窗口句柄 = FindWindowA(0, TEXT);
    if (窗口句柄)
    {
        GetWindowThreadProcessId(窗口句柄, &dwProcessId);
    }
    HANDLE hSnap = CreateToolhelp32Snapshot(2u, 0);
    PROCESSENTRY32 pe = { 0 };
    pe.dwSize = sizeof(pe);
    if (Process32First(hSnap, &pe))
    {
        bool isfind = true;
        while (TEXT != pe.szExeFile)
        {
            if (!Process32Next(hSnap, &pe)) {
                isfind = false;
                break;
            }
        }
        if (isfind)
        {
            dwProcessId = pe.th32ProcessID;
        }
    }
    if (dwProcessId)
    {
        HANDLE hPros = OpenProcess(1u, 0, dwProcessId);
        result = TerminateProcess(hPros, 0) ;
    }
    else
    {
        result = 0;
    }
    return result;
}



/*************************取DLL列表****************************/
vector<string> GetDllList(int ID)
{

    HANDLE g_hNaoshot = 0;
    HANDLE hSnapshot = 0;
    MODULEENTRY32 me = {0};
    PROCESSENTRY32 pe = {0};
    vector<string> ret;
    me.dwSize = sizeof(me);
    if (ID == -1)
    {
        g_hNaoshot = CreateToolhelp32Snapshot(2u, 0);
        pe.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(g_hNaoshot, &pe))
        {
            do
            {
                hSnapshot = CreateToolhelp32Snapshot(8u, pe.th32ProcessID);

                if (Module32First(hSnapshot, &me))
                {
                    do
                    {
                        if (ret.size() == 0)
                        {
                            ret.push_back(me.szExePath);;
                        }
                        else
                        {
                            size_t i = 0;
                            string Path = string(me.szExePath);
                            while (ret[i] != Path)
                            {
                                ++i;
                                if (i >= ret.size()) {
                                    ret.push_back(Path);;
                                }
                            }
                        }


                    } while (Module32Next(hSnapshot, &me));
                }
                CloseHandle(hSnapshot);
            } while (Process32Next(g_hNaoshot, &pe));
        }
    }
    else
    {
        g_hNaoshot = CreateToolhelp32Snapshot(8u, ID);
        if (Module32First(g_hNaoshot, &me))
        {
            do
            {
                ret.push_back(me.szExePath);
            } while (Module32Next(g_hNaoshot, &me));
        }
    }
    CloseHandle(g_hNaoshot);
    return ret;
}

/*************************取没有响应程序列表****************************/
BOOL IsWindowsNT()
{

    BOOL result = false;;
    OSVERSIONINFOA VersionInformation = {}; 

    VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    if (GetVersionExA(&VersionInformation)
        || (VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA), (result = GetVersionExA(&VersionInformation)) != 0))
    {
        if (VersionInformation.dwPlatformId == 2 && VersionInformation.dwMajorVersion <= 4) {
            result = true;
        }
    }
    return result;
}
BOOL IsWindows2k()
{
    signed int ret = 0;
    BOOL result = 0;
    OSVERSIONINFOA VersionInformation = {};
    VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    if (GetVersionExA(&VersionInformation)
        || (VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA), (result = GetVersionExA(&VersionInformation)) != 0))
    {
        if (VersionInformation.dwPlatformId == 2 && VersionInformation.dwMajorVersion >= 5)
            ret = 1;
        result = ret;
    }
    return result;
}
typedef BOOL(WINAPI* HUNG_FUN9X)(DWORD);
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lparam) {
    vector<HWND>* pHwnd = (vector<HWND>*)lparam;
    if (GetWindowLongPtrA(hWnd, GWL_STYLE) & WS_VISIBLE)//如果窗口可见
    {
        pHwnd->push_back(hWnd);
    }
    return 1;
}
vector<string> GetHungProgramList() {
    vector<string> RET;
    vector<HWND> hWnd;
    HMODULE m_hUser32 = NULL;
    HUNG_FUN9X IsHungThread = NULL;;
    bool oldwin = false;
    if (m_hUser32 == NULL)
    {
        m_hUser32 = GetModuleHandleW(L"USER32.DLL");
    }
    if (m_hUser32)
    {
        IsHungThread = (HUNG_FUN9X)GetProcAddress(m_hUser32, "IsHungThread");
    }
    EnumWindows(&EnumWindowsProc, (LPARAM)&hWnd);
    if (IsWindowsNT() || IsWindows2k()) {
        oldwin = 1;
    }
    for (size_t i = 0; i < hWnd.size(); i++)
    {
        if (IsWindow(hWnd[i]))
        {
            BOOL SUCC = FALSE;
            if (oldwin)
            {
                SUCC = IsHungAppWindow(hWnd[i]);
            }
            else
            {
                if (IsHungThread)
                {
                    SUCC = IsHungThread(GetWindowThreadProcessId(hWnd[i], 0));
                }
            }
            if (SUCC)
            {
                char str[256] = {};
                GetWindowTextA(hWnd[i], str, 256);
                RET.push_back(str);
            }

        }

    }
    return RET;
}

/*************************取没有响应程序列表****************************/

bool MyGetFileVersionInfo(char* FlieNmae, EFileINfo* pInfo) {


    DWORD Infosize = GetFileVersionInfoSizeA(FlieNmae, 0);
    bool retb = false;
    if (Infosize)
    {
        wchar_t* pInfobuff = new wchar_t[(size_t)Infosize + 1];
        if (!pInfobuff) {
            return false;
        }
        if (!GetFileVersionInfoA(FlieNmae, 0, Infosize, pInfobuff)) {
            delete[] pInfobuff;
            return false;
        };
        unsigned char* pbuff = 0;
        unsigned int BuffLenth = 0;
        if (!VerQueryValueW(pInfobuff, L"\\VarFileInfo\\Translation", (LPVOID*)&pbuff, &BuffLenth)) {
            delete[] pInfobuff;
            return false;
        };
        wstring languge = L"080404b0";
        wstring languagedata;

        if (BuffLenth <= 0)
        {
            languge = L"040904E4";
        }
        else
        {
            size_t loopnum = BuffLenth >> 2;
            size_t i = 0;
            if ((signed int)(BuffLenth >> 2) > 0)
            {
                DWORD* temp = (DWORD*)pbuff;
                wchar_t pTempbuff[256] = {};
                do
                {
                    VerLanguageNameW(*temp, pTempbuff, 256);//语言信息
                    languagedata += pTempbuff;
                    if (i != loopnum - 1)
                        languagedata += L",";
                    ++i;
                    ++temp;
                } while (i < loopnum);
            }
            pInfo->language = W2Estr(languagedata);
            wchar_t* retbuff = 0;
            unsigned int retlenth = 0;
            VerQueryValueW(pInfobuff, (L"\\StringFileInfo\\" + languge + L"\\Comments").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->Remarks = retbuff == 0 ? 0 : W2Estr(retbuff);
            VerQueryValueW(pInfobuff, (L"\\StringFileInfo\\" + languge + L"\\CompanyName").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->companyname = retbuff == 0 ? 0 : W2Estr(retbuff);
            VerQueryValueW(pInfobuff, (L"\\StringFileInfo\\" + languge + L"\\FileDescription").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->description = retbuff == 0 ? 0 : W2Estr(retbuff);
            VerQueryValueW(pInfobuff, (L"\\StringFileInfo\\" + languge + L"\\FileVersion").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->vision = retbuff == 0 ? 0 : W2Estr(retbuff);
            VerQueryValueW(pInfobuff, (L"\\StringFileInfo\\" + languge + L"\\InternalName").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->inname = retbuff == 0 ? 0 : W2Estr(retbuff);
            VerQueryValueW(pInfobuff, (L"\\StringFileInfo\\" + languge + L"\\LegalCopyright").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->copyright = retbuff == 0 ? 0 : W2Estr(retbuff);
            VerQueryValueW(pInfobuff, (L"\\StringFileInfo\\" + languge + L"\\LegalTrademarks").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->trademark = retbuff == 0 ? 0 : W2Estr(retbuff);
            VerQueryValueW(pInfobuff, (L"\\StringFileInfo\\" + languge + L"\\OriginalFilename").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->name = retbuff == 0 ? 0 : W2Estr(retbuff);
            VerQueryValueW(pInfobuff, (L"\\StringFileInfo\\" + languge + L"\\PrivateBuild").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->privatebuild = retbuff == 0 ? 0 : W2Estr(retbuff);
            VerQueryValueW(pInfobuff, (L"\\StringFileInfo\\" + languge + L"\\ProductName").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->Productname = retbuff == 0 ? 0 : W2Estr(retbuff);
            VerQueryValueW(pInfobuff, (L"\\StringFileInfo\\" + languge + L"\\ProductVersion").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->productversion = retbuff == 0 ? 0 : W2Estr(retbuff);
            VerQueryValueW(pInfobuff, (L"\\SpecialBuild\\" + languge + L"\\ProductVersion").c_str(), (LPVOID*)&retbuff, &retlenth);
            pInfo->Specialbuild = retbuff == 0 ? 0 : W2Estr(retbuff);
            retb = true;
        }
        delete[] pInfobuff;
    }

    return retb;



}


/*************************取内存容量信息****************************/

size_t GetMemoryInfo(unsigned short val)
{
    unsigned long long result = 0;
    bool is_old_windows = false;
    MEMORYSTATUS Buffer;
    MEMORYSTATUSEX BufferEx;
    OSVERSIONINFOA VersionInformation;
    VersionInformation.dwOSVersionInfoSize = sizeof(VersionInformation);
    if (GetVersionExA(&VersionInformation))
    {

        is_old_windows = VersionInformation.dwMajorVersion <= 4;
    }
    else
    {
        is_old_windows = 0;
    }
    if (is_old_windows)
    {
        Buffer.dwLength = sizeof(MEMORYSTATUS);
        GlobalMemoryStatus(&Buffer);
        switch (val)
        {
        case 1:
            result = (unsigned __int64)Buffer.dwAvailPhys >> 20;
            break;
        case 2:
            result = (unsigned __int64)Buffer.dwTotalVirtual >> 20;
            break;
        case 3:
            result = (unsigned __int64)Buffer.dwAvailVirtual >> 20;
            break;
        case 4:
            result = (unsigned __int64)Buffer.dwTotalPageFile >> 20;
            break;
        case 5:
            result = (unsigned __int64)Buffer.dwAvailPageFile >> 20;
            break;
        default:
            result = (unsigned __int64)Buffer.dwTotalPhys >> 20;
            break;
        }
    }
    else
    {
        BufferEx.dwLength = sizeof(BufferEx);
        GlobalMemoryStatusEx(&BufferEx);
        switch (val)
        {
        case 1:
            result = BufferEx.ullAvailPhys >> 20;
            break;
        case 2:
            result = BufferEx.ullTotalVirtual >> 20;
            break;
        case 3:
            result = BufferEx.ullAvailVirtual >> 20;
            break;
        case 4:
            result = BufferEx.ullTotalPageFile >> 20;
            break;
        case 5:
            result = BufferEx.ullAvailPageFile >> 20;
            break;
        default:
            result = BufferEx.ullTotalPhys >> 20;
        }
    }
    return result;
}

/*************************取声卡名称A****************************/

char* GetAudioCard()
{
    char* result = 0;
    tagWAVEOUTCAPSA pwoc = { 0 };
    if (waveOutGetNumDevs())
    {
        if (!waveOutGetDevCapsA(0, &pwoc, sizeof(tagWAVEOUTCAPSA))) {
            if (pwoc.szPname)
            {
                result = eapi_CloneTextData(pwoc.szPname);
            }
        }
    }
    return result;
}
/*************************取字体列表A****************************/

INT CALLBACK NEnumFontNameProcA(LOGFONTA* lpelfe, TEXTMETRIC* lpntme, INT FontType, LPARAM lParam) {
    std::vector<string>* aryFaceName = (std::vector<string>*)lParam;;
    bool Hased = false;
    for (auto it = aryFaceName->begin(); it != aryFaceName->end(); it++)
    {
        if (*it == string(lpelfe->lfFaceName)) {
            Hased = true;
            return 1;
        }
    }
    aryFaceName->push_back(lpelfe->lfFaceName);
    return 1;
}
/*****************取字体列表**********/
vector<string>  GetFontListA()//枚举系统中的所有字体名称
{
    vector<string> FontName;
    HDC hdc = GetDC(NULL);;
    LOGFONTA lpLogfont = { 0 };
    lpLogfont.lfCharSet = DEFAULT_CHARSET;
    EnumFontFamiliesExA(hdc, &lpLogfont, (FONTENUMPROCA)NEnumFontNameProcA, (LPARAM)&FontName, 0);
    ReleaseDC(NULL, hdc);
    return FontName;
}


/*****************添加字体**********/
bool  AddFont(string FontPath)
{
    char pszPath[MAX_PATH] = { 0 };
    bool result = false;
    if (SHGetSpecialFolderPathA(0, pszPath, 20, 0))
    {
        if (PathFileExistsA(FontPath.c_str()))
        {
            string::size_type iPos = FontPath.find_last_of('\\');
            string filename = FontPath.substr(iPos, FontPath.length() - iPos);
            filename = pszPath + filename;
            if (CopyFileA(FontPath.c_str(), filename.c_str(), TRUE))
            {
                BOOL Ret = AddFontResourceA(FontPath.c_str());
                result = (bool)Ret;
                if (Ret) {
                    SendMessageA(HWND_BROADCAST, 0x1Du, 0, 0);
                }
            }
        }
    }
    return result;
}

HANDLE  AddFont(LPBYTE FontPath)
{
    DWORD dwFonts = 0;
    VECTORBYTE FontData = GetEbin(FontPath);
    
    return  AddFontMemResourceEx(FontData.data, FontData.size, 0, &dwFonts);
}

/*****************卸载字体**********/
bool RemoveFont(HANDLE hF)
{

    return RemoveFontMemResourceEx(hF);
}
bool RemoveFont(string lpFileName)
{
    bool Ret = false;
    Ret = RemoveFontResourceA(lpFileName.c_str());
    if (Ret)
        SendMessageA(HWND_BROADCAST, 0x1Du, 0, 0);
    return Ret;
}


/*****************取图片尺寸*********************/

SIZE  GetImageSize(LPBYTE _data)//快速读取图片高度，失败返回零。
{
    VECTORBYTE data = GetEbin(_data);
    SIZE Ret = {};
    GdiplusStartupInput GpInput;
    ULONG_PTR gdip_Token;
    GpInput.GdiplusVersion = 1;
    if (GdiplusStartup(&gdip_Token, &GpInput, 0) == 0) {

        size_t dwFileSize;
        dwFileSize = data.size;
        HGLOBAL hImageMemory = GlobalAlloc(GMEM_MOVEABLE, dwFileSize); // ; //给图片分配全局内存;
        if (!hImageMemory)
        {
            return Ret;
        }
        void*  pImageMemory = GlobalLock(hImageMemory); // ; //锁定内存;
        if (!pImageMemory)
        {
            GlobalFree(hImageMemory);
            GdiplusShutdown(gdip_Token); // GDI关闭 +;
            return {};
        }
        GpImage* gdip_Image = NULL;
        RtlMoveMemory(pImageMemory, data.data, dwFileSize);
        LPSTREAM pIStream;
        CreateStreamOnHGlobal(hImageMemory, false, &pIStream); // //用全局内存初使化IStream接口指针;
        GdipLoadImageFromStream(pIStream, &gdip_Image);
        GlobalUnlock(pImageMemory); // ; //解锁内存;
        GlobalFree(hImageMemory);
        UINT Wid, Hgt;
        GdipGetImageHeight(gdip_Image, &Hgt);
        GdipGetImageWidth(gdip_Image, &Wid);
        GdipDisposeImage(gdip_Image);
        GdiplusShutdown(gdip_Token); // GDI关闭 +;
        Ret.cx = Hgt;
        Ret.cy = Wid;
    }
    return Ret;
}
SIZE   GetImageSize(string ImagePat)//快速读取图片高度，失败返回零。
{
    SIZE Ret = {};
    UINT Wid;
    UINT Hgt;
    GdiplusStartupInput GpInput;
    ULONG_PTR gdip_Token;
    std::string FileName;
    size_t dwFileSize;
    HGLOBAL hImageMemory;
    void* pImageMemory;
    LPSTREAM pIStream;
    GpImage* gdip_Image = NULL;
    FileName = ImagePat;
    bool FileExists = PathFileExistsA(FileName.c_str());
    GpInput.GdiplusVersion = 1;
    if (GdiplusStartup(&gdip_Token, &GpInput, 0) == 0) {
        if (FileExists) {
            GdipLoadImageFromFile(A2W(FileName).c_str(), &gdip_Image);
            GdipGetImageHeight(gdip_Image, &Hgt);
            GdipGetImageWidth(gdip_Image, &Wid);
            GdipDisposeImage(gdip_Image);
            GdiplusShutdown(gdip_Token); // GDI关闭 +;
            Ret.cx = Hgt;
            Ret.cy = Wid;
        }
    }
    return Ret;
}


/*****************取IE版本号A*********************/

char* GetIEVersion()
{
    const char szFilename[] = "mshtml.dll";
    DWORD dwMajorVersion = 0, dwMinorVersion = 0;
    DWORD dwBuildNumber = 0, dwRevisionNumber = 0;
    DWORD dwHandle = 0;
    DWORD dwVerInfoSize = GetFileVersionInfoSizeA(szFilename, &dwHandle);
    if (dwVerInfoSize) {
        LPVOID lpBuffer = LocalAlloc(LPTR, dwVerInfoSize);
        if (lpBuffer) {
            if (GetFileVersionInfoA(szFilename, dwHandle, dwVerInfoSize, lpBuffer)) {
                VS_FIXEDFILEINFO* lpFixedFileInfo = NULL;
                UINT nFixedFileInfoSize = 0;
                if (VerQueryValueA(lpBuffer, "\\", (LPVOID*)&lpFixedFileInfo, &nFixedFileInfoSize) && (nFixedFileInfoSize)) {
                    dwMajorVersion = HIWORD(lpFixedFileInfo->dwFileVersionMS);
                    dwMinorVersion = LOWORD(lpFixedFileInfo->dwFileVersionMS);
                    dwBuildNumber = HIWORD(lpFixedFileInfo->dwFileVersionLS);
                    dwRevisionNumber = LOWORD(lpFixedFileInfo->dwFileVersionLS);
                }
            }LocalFree(lpBuffer);
        }
    }
    else {
        return 0;
    }
    char buf[512] = { 0 };
    wsprintfA(buf, "%d.%d.%d.%d", dwMajorVersion, dwMinorVersion, dwBuildNumber, dwRevisionNumber);
    return eapi_CloneTextData(buf);

}

/*****************添加IE工具条按钮*********************/
BOOL  AddButtonToIE(string ButtTitle, string Icon, string Comline, string HotIcon, BOOL IsVisible)
{
    BOOL result = FALSE;
    GUID pguid;
    DWORD dwDisposition;
    if (CoCreateGuid(&pguid))
    {
        HKEY phkResult = 0;
        char lpSubKey[260] = { 0 };
        wsprintfA(lpSubKey,
            "Software\\Microsoft\\Internet Explorer\\Extensions\\{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
            pguid.Data1,
            pguid.Data2,
            pguid.Data3,
            pguid.Data4[0],
            pguid.Data4[1],
            pguid.Data4[2],
            pguid.Data4[3],
            pguid.Data4[4],
            pguid.Data4[5],
            pguid.Data4[6],
            pguid.Data4[7]);
        if (RegCreateKeyExA(HKEY_LOCAL_MACHINE, lpSubKey, 0, 0, 0, KEY_ALL_ACCESS, 0, &phkResult, &dwDisposition))
        {
            RegSetValueExA(phkResult, "CLSID", 0, REG_SZ, (const BYTE*)"{1FBA04EE-3024-11D2-8F1F-0000F87ABD16}", sizeof("{1FBA04EE-3024-11D2-8F1F-0000F87ABD16}"));
            const char* BtutonVisible = IsVisible ? "Yes" : "No";
            size_t VisibleSize = IsVisible ? sizeof("Yes") : sizeof("No");

            RegSetValueExA(phkResult, "Default Visible", 0, REG_SZ, (const BYTE*)BtutonVisible, VisibleSize);//默认显示
            RegSetValueExA(phkResult, "ButtonText", 0, REG_SZ, (const BYTE*)ButtTitle.c_str(), ButtTitle.size());
            RegSetValueExA(phkResult, "Icon", 0, REG_SZ, (const BYTE*)Icon.c_str(), Icon.size());
            RegSetValueExA(phkResult, "HotIcon", 0, REG_SZ, (const BYTE*)HotIcon.c_str(), HotIcon.size());
            RegSetValueExA(phkResult, "Exec", 0, REG_SZ, (const BYTE*)Comline.c_str(), Comline.size());
            if (phkResult)
                RegCloseKey(phkResult);
            result = TRUE;
        }

    }
    return result;
}


/*****************删除IE工具条按钮*********************/

BOOL  DeleteButtonFromIE(const char* Button)
{

    BOOL result = FALSE;
    HKEY phkResult, hKey;;
    CHAR Name[260] = { 0 }, lpSubKey[260] = { 0 }, ValueName[260] = { 0 };
    DWORD cbData = 260;


    strcpy(ValueName, "ButtonText");
    strcpy(lpSubKey, "Software\\Microsoft\\Internet Explorer\\Extensions");

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_EXECUTE, &phkResult))
    {
        DWORD Type = 1;
        for (DWORD i = 0; !RegEnumKeyA(phkResult, i, Name, cbData); ++i)//找到一次也不跳出，枚举全部，是否会有重名？？
        {
            wsprintfA(lpSubKey, "Software\\Microsoft\\Internet Explorer\\Extensions\\%s", Name);//要不是后面没有格式化和申请堆内存，看到这又想换string，不用cat不用sprintf，
            if (!RegOpenKeyExA(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_ALL_ACCESS, &hKey))
            {
                if (!RegQueryValueExA(hKey, ValueName, 0, &Type, (LPBYTE)Name, &cbData) && !strcmp(Button, Name))//找到
                {
                    result = TRUE;
                    if (RegDeleteKeyA(phkResult, Name))
                    {
                        RegCloseKey(phkResult);
                        RegCloseKey(hKey);
                        return 0;
                    }
                }
                RegCloseKey(hKey);
            }
        }
        RegCloseKey(phkResult);
    }
    return result;
}


/*****************创建程序组*********************/

BOOL CreateProgramGroup(const char* path, int position)
{
    BOOL result=FALSE;
    char pszPath[260] = { 0 };

    SHGetSpecialFolderPathA(0, pszPath, position, 0);
    int lrnth = lstrlenA(path);
    wsprintfA(&pszPath[lrnth], "\\s%", path);
    result = CreateDirectoryA(pszPath, 0);
    if (result)
    {
        NotifyShellA(SHCNE_MKDIR | SHCNE_INTERRUPT, pszPath);
        result = TRUE;
    }
    return result;
}


/*****************删除程序组*********************/

BOOL DeleteProgramGroup(const char* path, int position)
{
    BOOL result=FALSE; 
    CHAR pszPath[260] = {0};
    SHGetSpecialFolderPathA(HWND_DESKTOP, pszPath, position, FALSE);
    int lenth = lstrlenA(pszPath);
    wsprintfA(&pszPath[lenth],"s%", path);
    result = EmptyDirectory(A2W(pszPath).c_str(), 0, 0);
    if (result)
    {
        if (!_rmdir(pszPath))
        {
            NotifyShellA(SHCNE_RMDIR | SHCNE_INTERRUPT, pszPath);
            result = TRUE;
        }
    }
    return result;
}



/**************************************************************/
BOOL GetShortCutTarget(const wstring& lpszLinkFilePath, wstring* FilePath, wstring* LinkArg, wstring* BeginPosition, wstring* IconPath, int* RunMod, wstring* shortkey, wstring* remarks)
{

    BOOL bReturn = FALSE;
    IShellLinkW* pShellLink = 0;
    CoInitialize(NULL);
    
    if (S_OK == CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void**)&pShellLink))
    {
        IPersistFile* pPersistFile = 0;
        if (S_OK == pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile))
        {
            if (S_OK == pPersistFile->Load(lpszLinkFilePath.c_str(), STGM_READ))
            {
                WCHAR Temp[MAX_PATH] = { 0 };	int Icon = 0;
                if (FilePath)
                {
                    *FilePath = {};
                    if (S_OK == pShellLink->GetPath(Temp, MAX_PATH, 0, SLGP_UNCPRIORITY))//文件路径
                    {
                        *FilePath = Temp;
                    }
                    memset(Temp, 0, sizeof(Temp));
                }
                if (LinkArg)
                {
                    *LinkArg = {};
                    if (S_OK == pShellLink->GetArguments(Temp, MAX_PATH))//获取参数
                    {
                        *LinkArg = Temp;
                    }
                    memset(Temp, 0, sizeof(Temp));
                }
                if (BeginPosition)
                {
                    *BeginPosition = {};
                    if (S_OK == pShellLink->GetWorkingDirectory(Temp, MAX_PATH))//工作文件夹
                    {
                        *BeginPosition = Temp;
                    }
                    memset(Temp, 0, sizeof(Temp));
                }
                if (IconPath)
                {
                    *IconPath = {};
                    if (S_OK == pShellLink->GetIconLocation(Temp, MAX_PATH, &Icon))//图标信息
                    {
                        *IconPath = Temp + to_wstring(Icon);
                    }
                    memset(Temp, 0, sizeof(Temp));
                }
                if (RunMod)
                {
                    *RunMod = 0;
                    pShellLink->GetShowCmd(RunMod);
                }
                if (shortkey)
                {
                    *shortkey = {};
                    WORD OutShortKey = 0;
                    if (S_OK == pShellLink->GetHotkey(&OutShortKey) && OutShortKey)//图标信息
                    {
                        const WCHAR* KeycStr[] = { L"" ,L"Shift", L"Ctrl" ,L"Shift+Ctrl",L"Alt", L"Shift+Alt",L"Ctrl+Alt",L"Shift+Ctrl+Alt" };
                        BYTE Skey[4] = { LOBYTE(OutShortKey) ,0,0,0 };
                        int Index = (int)HIBYTE(OutShortKey);
                        if (Index == 0)
                        {
                            *shortkey = wstring((wchar_t*)Skey);
                        }
                        else if (Index <= 7 && Index > 0);
                        {
                            *shortkey = KeycStr[Index] + wstring(L"+") + wstring((wchar_t*)Skey);
                        }
                    }
                }
                if (remarks)
                {
                    *remarks = {};
                    if (S_OK == pShellLink->GetDescription(Temp, MAX_PATH))//图标信息
                    {
                        *remarks = Temp;
                    }
                }

            }
            pPersistFile->Release();
        }
        pShellLink->Release();
    }
    CoUninitialize();
    return bReturn;
}

BOOL GetShortCutTarget(const wstring& lpszLinkFilePath, wstring* FilePath, wstring* LinkArg, wstring* BeginPosition, wstring* IconPath, int* RunMod, int* shortkey, wstring* remarks)
{

    BOOL bReturn = FALSE;
    IShellLinkW* pShellLink = 0;
    CoInitialize(NULL);

    if (S_OK == CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void**)&pShellLink))
    {
  
        IPersistFile* pPersistFile = 0;
        if (S_OK == pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile))
        {
           
            if (S_OK == pPersistFile->Load(lpszLinkFilePath.c_str(), STGM_READ))
            {
             
                WCHAR Temp[MAX_PATH] = { 0 };	int Icon = 0;
    
                if (FilePath)
                {
                    
                    *FilePath = {};
      
                    if (S_OK == pShellLink->GetPath(Temp, MAX_PATH, 0, SLGP_UNCPRIORITY))//文件路径
                    {
                        *FilePath = Temp;

                    }
                    memset(Temp, 0, sizeof(Temp));
                }
                if (LinkArg)
                {
                    *LinkArg = {};
                    if (S_OK == pShellLink->GetArguments(Temp, MAX_PATH))//获取参数
                    {
                        *LinkArg = Temp;
                    }
                    memset(Temp, 0, sizeof(Temp));
                }
                if (BeginPosition)
                {
                    *BeginPosition = {};
                    if (S_OK == pShellLink->GetWorkingDirectory(Temp, MAX_PATH))//工作文件夹
                    {
                        *BeginPosition = Temp;
                    }
                    memset(Temp, 0, sizeof(Temp));
                }
                if (IconPath)
                {
                    *IconPath = {};
                    if (S_OK == pShellLink->GetIconLocation(Temp, MAX_PATH, &Icon))//图标信息
                    {
                        *IconPath = Temp + to_wstring(Icon);
                    }
                    memset(Temp, 0, sizeof(Temp));
                }
                if (RunMod)
                {
                    *RunMod = 0;
                    pShellLink->GetShowCmd(RunMod);
                }
                if (shortkey)
                {
                    *shortkey = 0;
                    WORD OutShortKey = 0;
                    if (S_OK == pShellLink->GetHotkey(&OutShortKey) && OutShortKey)//图标信息
                    {
                        *shortkey = OutShortKey;
                    }
                }
                if (remarks)
                {
                    *remarks = {};
                    if (S_OK == pShellLink->GetDescription(Temp, MAX_PATH))//图标信息
                    {
                        *remarks = Temp;
                    }
                }

            }
            pPersistFile->Release();
        }
        pShellLink->Release();
    }
    CoUninitialize();
    return bReturn;
}



/************************创建快捷方式*********************************/
BOOL CreateLink(string LinkName, string FilePath, string remark, WORD wHotkey,string comline, string workdir)
{
    BOOL blSucceeded = FALSE;
    IShellLinkA* piShellLink;
    if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&piShellLink)))
    {
        IPersistFile* piPersistFile;
        if (SUCCEEDED(piShellLink->QueryInterface(IID_IPersistFile, (void**)&piPersistFile)))
        {
            piShellLink->SetPath(FilePath.c_str());
            piShellLink->SetShowCmd(SW_SHOW);
            if (remark.empty() == FALSE)  piShellLink->SetDescription(remark.c_str());
            if (comline.empty() == FALSE)  piShellLink->SetArguments(comline.c_str());
            if (wHotkey != 0)  piShellLink->SetHotkey(wHotkey);
            if (workdir.empty() == FALSE)  piShellLink->SetWorkingDirectory(workdir.c_str());
            const char* FileNmae = (strchr(LinkName.c_str(), '.') != NULL ? LinkName.c_str() : (LinkName + ".lnk").c_str());
            WCHAR WideCharStr[MAX_PATH] = { 0 };
            MultiByteToWideChar(0, 0, FileNmae, -1, WideCharStr, MAX_PATH);
            blSucceeded = SUCCEEDED(piPersistFile->Save(WideCharStr, TRUE));
            piPersistFile->Release();
        }
        piShellLink->Release();
    }
    return blSucceeded;
}


/************************创建程序项***************************/
BOOL CreateProgramItem(const char* GroupName, const char* ItemName, const char* ItemPath, int position)
{

    BOOL result = FALSE;
    if (PathFileExistsA(ItemPath))
    {
        char pszPath[MAX_PATH] = { 0 };
        SHGetSpecialFolderPathA(0, pszPath, position, 0);
        wsprintfA(pszPath, "%s\\%s\\%s.lnk", pszPath, GroupName, ItemName);
        if (CreateLink(pszPath, ItemPath, "", 0,"", ""));
        {
            NotifyShellA(SHCNE_CREATE | SHCNE_INTERRUPT, pszPath);
            result = TRUE;
        }
    }
    return result;
}

/************************删除程序项***************************/
BOOL DeleteProgramItem(const char* GroupName, const char* ItemName,  int position)
{

    BOOL result = FALSE;
    char pszPath[MAX_PATH] = { 0 };
    SHGetSpecialFolderPathA(0, pszPath, position, 0);
    wsprintfA(pszPath, "%s\\%s\\%s.lnk", pszPath, GroupName, ItemName);
    result = DeleteFileA(pszPath);
    if (result)
    {
        NotifyShellA(SHCNE_DELETE | SHCNE_INTERRUPT, pszPath);
    }
    return result;
}

/*设置自动运行*/

bool CancelAutoRun(char* lpValueName)
{
    bool Ret = false;
    HKEY hKeyAutoStart;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKeyAutoStart) == ERROR_SUCCESS)
    {
        if (RegDeleteValueA(hKeyAutoStart, lpValueName) == ERROR_SUCCESS) {
            Ret = true;//为或关系
        };
        RegFlushKey(HKEY_CURRENT_USER);
    }
    //注册表中处理结束，开始处理启动文件夹
    CHAR pszPath[MAX_PATH];
    SHGetSpecialFolderPathA(0, pszPath, 7, 0);
    wsprintfA(pszPath, "%s\\%s.lnk", pszPath, lpValueName);
    if (DeleteFileA(pszPath)) {
        Ret = true;//为或关系，是否改为两个全部清空？但是注册表找不到注册项也会返回false
    }
    NotifyShellA(SHCNE_DELETE | SHCNE_INTERRUPT, pszPath);
    return Ret;

}

/************取网卡信息列表************/
vector<_NETWORKINFO> GetApapterList()
{
    DWORD Index;
    ULONG SizePointer = 0;
    GetAdaptersInfo(0, &SizePointer);
    vector<_NETWORKINFO> Ret;
    if (SizePointer)
    {
        PIP_ADAPTER_INFO PipInfo = (PIP_ADAPTER_INFO)malloc(SizePointer);
        GetAdaptersInfo(PipInfo, &SizePointer);
        PIP_ADAPTER_INFO Temp = PipInfo;
        if (PipInfo)
        {

            Index = 1;
            do
            {
                _NETWORKINFO TempNet;
                char lpadd[40] = { 0 };
                sprintf(lpadd, "%02X-%02X-%02X-%02X-%02X-%02X", Temp->Address[0], Temp->Address[1], Temp->Address[2], Temp->Address[3], Temp->Address[4], Temp->Address[5]);
                TempNet.index = Index + 1;
                TempNet.Address = eapi_CloneTextData(lpadd);
                TempNet.name = eapi_CloneTextData(Temp->Description);
                TempNet.IpAddress = eapi_CloneTextData( Temp->IpAddressList.IpAddress.String);
                TempNet.IpMask = eapi_CloneTextData(Temp->IpAddressList.IpMask.String);
                TempNet.DefaultGateway = eapi_CloneTextData(Temp->GatewayList.IpAddress.String);
                string WinsAddr;
                if (Temp->HaveWins) {
                    WinsAddr = Temp->PrimaryWinsServer.IpAddress.String;
                }
                TempNet.WinsAddress = A2Estr(WinsAddr.c_str());
                string DhcpServer;
                if (Temp->DhcpEnabled) {
                    DhcpServer = Temp->DhcpServer.IpAddress.String;
                }
                TempNet.DHCPAdress = A2Estr(DhcpServer.c_str());
                Ret.push_back(TempNet);
                Temp = Temp->Next;
                ++Index;
            } while (Temp);
        }
        free(PipInfo);
    }

    return Ret;
}

/************取本机网卡名************/
char* GetLocalAdapterName(int NetIndex)
{
    char* Ret = 0;
    ULONG SizePointer;
    int Index;
    SizePointer = 0;
    IP_ADAPTER_INFO* IPINF;
    IP_ADAPTER_INFO* temp;
    GetAdaptersInfo(0, &SizePointer);
    if (SizePointer)
    {

        IPINF = new IP_ADAPTER_INFO[SizePointer];
        temp = IPINF;
        GetAdaptersInfo((PIP_ADAPTER_INFO)IPINF, &SizePointer);
        Index = 0;
        while (temp)
        {
            if (Index == NetIndex - 1)
            {
                Ret = eapi_CloneTextData(temp->Description);
                break;
            }
            temp = temp->Next;
            if (++Index >= 5)
            {
                delete[]temp;
                return  Ret;
            }
        }
        delete[]temp;
    }
    return  Ret;
}


/************取本机网卡物理地址************/
typedef struct _INFO {
    struct _IP_ADAPTER_INFO* Next;
    DWORD ComboIndex;
    char AdapterName[MAX_ADAPTER_NAME_LENGTH + 4];
    char Description[MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
    UINT AddressLength;
    BYTE Address[MAX_ADAPTER_ADDRESS_LENGTH];
};
char* GetLocalMac(int NetIndex)
{

    char Dest[40] = { 0 };
    PIP_ADAPTER_INFO IPINFO; // esi@2
    signed int Index; // eax@2
    ULONG SizePointer; // [sp+0h] [bp-4h]@1

    SizePointer = 0;
    GetAdaptersInfo(0, &SizePointer);
    if (SizePointer)
    {
        IPINFO = new IP_ADAPTER_INFO[SizePointer];
        GetAdaptersInfo(IPINFO, &SizePointer);
        Index = 1;
        if (IPINFO)
        {
            while (Index != NetIndex)
            {
                IPINFO = IPINFO->Next;
                ++Index;
                if (!IPINFO)
                {
                    return 0;
                }
            }
            sprintf(Dest, "%02X-%02X-%02X-%02X-%02X-%02X", IPINFO->Address[0], IPINFO->Address[1], IPINFO->Address[2], IPINFO->Address[3], IPINFO->Address[4], IPINFO->Address[5]);
        }
        delete[]IPINFO;
    }
    return  eapi_CloneTextData(Dest);
}

/************取远程网卡物理地址************/
char* GetRemoteMac(char* ip)
{

    ULONG PhyAddrLen = 6;
    WSAData wsaData;
    ULONG pMacAddr[2] = { 0 };
    char Ret[40] = { 0 };

    if (!WSAStartup(MAKEWORD(2, 2), &wsaData))
    {
        IPAddr  addr = inet_addr(ip);
        if (gethostbyaddr((const char*)&addr, sizeof(addr), AF_INET) && !SendARP(addr, 0, &pMacAddr, &PhyAddrLen))
        {
            BYTE* bPhysAddr = (BYTE*)&pMacAddr;
            sprintf(Ret, "%02X-%02X-%02X-%02X-%02X-%02X", bPhysAddr[0], bPhysAddr[1], bPhysAddr[2], bPhysAddr[3], bPhysAddr[4], bPhysAddr[5]);
        }
        WSACleanup();
    }
    return eapi_CloneTextData(Ret);
}
/************取远程机器名************/
char* GetRemoteName(char* ip)
{
    WSAData wsaData = { 0 };
    char Ret[256] = { 0 };
    IPAddr  addr = inet_addr(ip);
    if (addr != -1)
    {
        if (!WSAStartup(MAKEWORD(2, 2), &wsaData))
        {
            hostent* DATA = gethostbyaddr((const char*)&addr, sizeof(addr), AF_INET);
            if (DATA)
            {
                strcpy(Ret, DATA->h_name);
                WSACleanup();
            }
        }
    }
    return eapi_CloneTextData(Ret);
}



/************取IP地址************/
char* GetIpFromHostName(char* MachineName)
{
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(wVersionRequested, &wsaData) != 0)
        return 0;
    char local[255] = { 0 };
    gethostname(local, sizeof(local));
    if (MachineName) {
        memset(local, 0, 255);
        strcpy(local, MachineName);
    }
    hostent* ph = gethostbyname(local);
    if (ph == NULL)
        return 0;
    in_addr addr;
    memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr));
    char*  localIP;
    localIP = eapi_CloneTextData(inet_ntoa(addr));
    WSACleanup();
    return localIP;
}

/************取网络类型列表A************/

vector<string> GetNetList()
{
    vector<string>  result;
    DWORD dwResultEnum, cbBuffer = 16384, cEntries = 0xFFFFFFFF;
    HANDLE hEnum;
    LPNETRESOURCEA lpnrLocal;
    if (!WNetOpenEnumA(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, 0, &hEnum))
    {
        lpnrLocal = (LPNETRESOURCEA)GlobalAlloc(GPTR, cbBuffer);
        if (lpnrLocal != NULL) {
            do {
                ZeroMemory(lpnrLocal, cbBuffer);
                dwResultEnum = WNetEnumResourceA(hEnum, &cEntries, lpnrLocal, &cbBuffer);
                if (dwResultEnum == NO_ERROR) {
                    for (DWORD i = 0; i < cEntries; i++) {
                        if (lpnrLocal[i].lpRemoteName)
                        {
                            result.push_back(lpnrLocal[i].lpRemoteName);
                        }
                        else if (lpnrLocal[i].lpProvider)
                        {
                            result.push_back(lpnrLocal[i].lpProvider);
                        }
                    }
                }
                else if (dwResultEnum != ERROR_NO_MORE_ITEMS) {
                    break;
                }
            } while (dwResultEnum != ERROR_NO_MORE_ITEMS);
            GlobalFree((HGLOBAL)lpnrLocal);
        }
        WNetCloseEnum(hEnum);
    }
    return result;
}


/***************取网络工作组列表***********/
vector<string> GetGroupList(string NetType) {

    vector<string> pNetWork;
    vector<string> result;
    HANDLE hEnum;
    if (!NetType.empty())
    {
        pNetWork.push_back(NetType.c_str());
    }
    else
    {
        pNetWork = GetNetList();
    }
    size_t ncount = pNetWork.size();
    if (ncount > 0)
    {
        NETRESOURCEA NetResource;
        for (size_t i = 0; i < ncount; i++)
        {
            memset(&NetResource, 0, sizeof(NETRESOURCEA));
            NetResource.lpProvider = const_cast<char*>(pNetWork[i].c_str());
            NetResource.dwDisplayType = RESOURCEDISPLAYTYPE_SERVER;
            NetResource.dwUsage = RESOURCEUSAGE_CONTAINER;
            NetResource.dwScope = RESOURCE_CONNECTED;
            if (!WNetOpenEnumA(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, RESOURCEUSAGE_CONTAINER, &NetResource, &hEnum))
            {
                while (1)
                {
                    DWORD cCount = 0xFFFFFFFF;
                    DWORD BufferSize = sizeof(NETRESOURCEA) * 256;
                    NETRESOURCEA* pBuff = new NETRESOURCEA[256];

                    if (WNetEnumResourceA(hEnum, &cCount, pBuff, &BufferSize) == ERROR_NO_MORE_ITEMS)//如果没有更多就跳出
                    {
                        delete[]pBuff;
                        break;
                    }
                    if (cCount)
                    {
                        for (size_t p = 0; p < cCount; p++)
                        {
                            CHAR TEMP[260] = { 0 };
                            strcpy(TEMP, pBuff[p].lpRemoteName);
                            result.push_back(TEMP);
                        }
                    }
                    delete[]pBuff;
                }
                WNetCloseEnum(hEnum);

            }
        }

    }
    return result;
}
/***************取网络计算机列表***********/
vector<string>GetComputerList(string group) {

    vector<string> result;
    vector<string> AllGroup;
    HANDLE hEnum;
    if (!group.empty())
    {
        AllGroup.push_back(group);
    }
    else
    {
        AllGroup = GetGroupList(string());
    }
    if (AllGroup.size() > 0)
    {
        NETRESOURCEA NetResource;
        for (size_t i = 0; i < AllGroup.size(); i++)
        {
            memset(&NetResource, 0, sizeof(NetResource));
            NetResource.lpRemoteName = const_cast<char*>(AllGroup[i].c_str());
            NetResource.dwDisplayType = RESOURCEDISPLAYTYPE_SERVER;
            NetResource.dwUsage = RESOURCEUSAGE_CONTAINER;
            NetResource.dwScope = RESOURCE_CONNECTED;
            if (!WNetOpenEnumA(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, RESOURCEUSAGE_CONTAINER, &NetResource, &hEnum))
            {

                while (1) {
                    DWORD cCount = 0xFFFFFFFF;
                    DWORD BufferSize = sizeof(NETRESOURCEA) * 256;
                    NETRESOURCEA* pBuff = new NETRESOURCEA[256];
                    if (WNetEnumResourceA(hEnum, &cCount, pBuff, &BufferSize) == ERROR_NO_MORE_ITEMS)
                    {
                        delete[]pBuff;
                        break;
                    }
                    if (cCount)
                    {
                        for (size_t d = 0; d < cCount; d++)
                        {
                            CHAR TEMP[260] = { 0 };
                            strcpy(TEMP, pBuff[d].lpRemoteName);
                            result.push_back(TEMP);
                        }


                    }
                    delete[]pBuff;
                }
                WNetCloseEnum(hEnum);
            }
        }
    }

    return result;
}

/***************取网络计算机列表***********/
bool   IsConnectToInternet()
{
    DWORD flag;
    return InternetGetConnectedState(&flag, 0);
}
/***************端口检测***********/
bool CheckPort(u_short port, char* ipadress)
{

    bool result=false;
    WSAData WsaData;
    sockaddr skadress;
    char* cp = ipadress;
    in_addr in;
    char* itar;
    char name[100] = { 0 };
    if (!WSAStartup(MAKEWORD(2,2), &WsaData))
    {
        if (!cp)
        {
            gethostname(name, 100);
            hostent* hHost = gethostbyname(name);
            if (!hHost)
            {
                WSACleanup();
                result = 0;
                return result;
            }
            memcpy(&in, hHost->h_addr_list, hHost->h_length);
            itar = inet_ntoa(in);
            cp = itar;
        }
        SOCKET socker = socket(2, 1, 0);
        if (socker == -1)
        {

            result = 0;
        }
        else
        {
            skadress.sa_family = 2;
            *(u_short*)&skadress.sa_data[0] = htons(port);
            *(DWORD*)&skadress.sa_data[2] = inet_addr(cp);
            if (connect(socker, &skadress, 16) == -1)
                result = 0;
            closesocket(socker);
            WSACleanup();
        }
    }


    return result;
}


/***************发送局域网消息***********/
BOOL NetMsgSend(char* target, char* message) {
    OSVERSIONINFOW verinfo;
    verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
    GetVersionExW(&verinfo);
    if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
        if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) return FALSE;
    }
    else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) return FALSE;
    else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) return FALSE;
    wchar_t* server = new wchar_t[strlen(target) + 1], *msg = new wchar_t[strlen(message) + 1];
    mbstowcs(server, target, strlen(target));
    mbstowcs(msg, message, strlen(message));
    BOOL ret = FALSE;
    if (NetMessageBufferSend(NULL, server, NULL, (BYTE*)&msg[0], wcslen(msg) * sizeof(wchar_t)))
    {
        ret=TRUE;
    }
    delete[]server;
    delete[]msg;
    return  ret;
}
/**************************打开特殊系统窗口************************/

void OpenSysInfoDlg()
{
    HKEY hKey;
    LSTATUS hLsta;
    char pBuff[MAX_PATH] = { 0 };
    DWORD pBuffSize = MAX_PATH;
    if (!RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Shared Tools\\MSInfo", 0, 0x20019u, &hKey)) {
        DWORD type = REG_NONE;

        hLsta = RegQueryValueExA(hKey, "Path", 0, &type, (BYTE*)pBuff, &pBuffSize);
        if (hKey)
        {
            RegCloseKey(hKey);
        }
        PathFileExistsA(pBuff);
        ShellExecuteA(0, "open", pBuff, 0, 0, 1);
    }
    else if (!RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Shared Tools Location", 0, 0x20019u, &hKey))
    {
        DWORD type = REG_NONE;
        RegQueryValueExA(hKey, "MSInfo", 0, &type, (BYTE*)pBuff, &pBuffSize);//可能会找不到文件
        PathAppendA(pBuff, "MSInfo32.exe");
        if (hKey)
        {
            RegCloseKey(hKey);
        }
        PathFileExistsA(pBuff);
        ShellExecuteA(0, "open", pBuff, 0, 0, 1);
    }
}
void  OpenSysWindow(int Type, int PageIndex) {
    string TempCom;
    char ComLine[100] = { 0 };
    switch (Type)
    {

    case 0:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL";
        break;
    case 1:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL sysdm.cpl,," + to_string(PageIndex);
        break;
    case 2:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL desk.cpl,," + to_string(PageIndex);
        break;
    case 3:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL access.cpl,," + to_string(PageIndex);
        break;
    case 4:
        TempCom = "rundll32.exe shell32.dll,SHHelpShortcuts_RunDLL AddPrinter";
        break;
    case 5:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL appwiz.cpl,," + to_string(PageIndex);;
        break;
    case 6:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL timedate.cpl,," + to_string(PageIndex);;
        break;
    case 7:
        TempCom = "rundll32.exe shell32.dll,SHHelpShortcuts_RunDLL FontsFolder";
        break;
    case 8:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL joy.cpl,," + to_string(PageIndex);;
        break;
    case 9:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL main.cpl @0," + to_string(PageIndex);;
        break;
    case 10:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL main.cpl @1," + to_string(PageIndex);;
        break;
    case 11:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL mmsys.cpl,," + to_string(PageIndex);;
        break;
    case 12:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL odbccp32.cpl";
        break;
    case 13:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL powercfg.cpl";
        break;
    case 14:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL intl.cpl,," + to_string(PageIndex);;
        break;
    case 15:
        TempCom = "rundll32.exe shell32.dll,Control_RunDLL Inetcpl.cpl,," + to_string(PageIndex);;
        break;
    case 16:
        TempCom = "Rundll32 netplwiz.dll,UsersRunDll";
        break;
    case 17:
        OpenSysInfoDlg();
        break;
    default:
        break;
    }
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi;
    si.cb = sizeof(si);
    strcpy(ComLine, TempCom.c_str());
    //WinExec(TempCom.c_str(), ERROR_ACCESS_DENIED);
    CreateProcessA(NULL, ComLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

/**************************打开网址************************/

bool OpenURL(char* Url) {

    return ShellExecuteA(FindWindowExA(0, 0, 0, "Microsoft Internet Explorer"), "open", Url, 0, 0, 1) != 0;
}
/**************************设置桌面墙纸************************/
bool  SetDeskWallPaper(string FileNmae, int stytle)
{

    bool result = false;
    HKEY phkResult;
    if (SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, const_cast<char*>(FileNmae.c_str()), 0))
    {

        if (!RegOpenKeyExA(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_READ | KEY_WRITE, &phkResult))
        {
            if (RegSetValueExA(phkResult, "Wallpaper", 0, 1u, (const BYTE*)FileNmae.c_str(), FileNmae.size()))
            {
                RegCloseKey(phkResult);
            }
            else
            {
                string Style = to_string(stytle);
                if (!RegSetValueExA(phkResult, "WallpaperStyle", 0, REG_SZ, (const BYTE*)Style.c_str(), Style.size())
                    && !RegSetValueExA(phkResult, "TileWallpaper", 0, REG_SZ, (const BYTE*)FileNmae.c_str(), FileNmae.size()))
                {
                    RegCloseKey(phkResult);
                    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, const_cast<char*>(FileNmae.c_str()), 1u);
                    return true;
                }
                result = RegCloseKey(phkResult);
            }
        }
    }
    return result;
}

/**************************设置窗口透明度************************/
//#include<optional>
bool SetDiaphaneity(HWND hWnd, unsigned char alpha, COLORREF key, bool through)
{
    DWORD dwFlag=2;
    if (through) {
        LONG TempStyle = GetWindowLongA(hWnd, GWL_EXSTYLE);
        SetWindowLongA(hWnd, GWL_EXSTYLE, TempStyle | WS_EX_TRANSPARENT | WS_EX_LAYERED); // 设置鼠标穿透;
    }
    else {
        SetWindowLongA(hWnd, GWL_EXSTYLE, WS_EX_LAYERED);
    }
    if (!key) {
        if (alpha == 0) {
            dwFlag = 1;
        }
        else {
            dwFlag = 3;
        }
    }
    return SetLayeredWindowAttributes(hWnd, key, alpha, dwFlag);
}


/**************************取显示模式列表************************/


vector<VIDEOMODE> GetVideoList()
{
    vector<VIDEOMODE> modes;
    DWORD i = 0;
    DEVMODEW dm = {0};
    while (EnumDisplaySettingsW(NULL, i, &dm))
    {
        VIDEOMODE thismode(dm.dmBitsPerPel, dm.dmPelsWidth,
            dm.dmPelsHeight, dm.dmDisplayFrequency);
        modes.push_back(thismode);
        ++i;
    }
    return modes;
}

/**************************取当前显示模式************************/
VIDEOMODE GetCurVideo()
{
    HDC hdc = ::GetDC(NULL);
    if (hdc == NULL) {
        return {};
    }
    VIDEOMODE m(GetDeviceCaps(hdc, BITSPIXEL), GetDeviceCaps(hdc, HORZRES), GetDeviceCaps(hdc, VERTRES), GetDeviceCaps(hdc, VREFRESH));
    ::ReleaseDC(NULL, hdc);
    return m;
}

/**************************设置屏幕分辨率************************/
void CreateCompatibleDEVMODE(DEVMODE* pdm, DWORD BitsPerPixel, DWORD Width, DWORD Height, DWORD Frequency)
{
    ZeroMemory(pdm, sizeof(DEVMODE));
    pdm->dmSize = sizeof(DEVMODE);

    if (BitsPerPixel)
    {
        pdm->dmBitsPerPel = BitsPerPixel;
        pdm->dmFields |= DM_BITSPERPEL;
    }

    if (Width)
    {
        pdm->dmPelsWidth = Width;
        pdm->dmFields |= DM_PELSWIDTH;
    }

    if (Height)
    {
        pdm->dmPelsHeight = Height;
        pdm->dmFields |= DM_PELSHEIGHT;
    }

    if (Frequency)
    {
        pdm->dmDisplayFrequency = Frequency;
        pdm->dmFields |= DM_DISPLAYFREQUENCY;
    }
}

LONG ChangeVideoModeTemporarily(VIDEOMODE mode)
{
    DEVMODE dm;
    CreateCompatibleDEVMODE(&dm, mode.m_dwBitsPerPixel, mode.m_dwWidth, mode.m_dwHeight, mode.m_dwFrequency);
    LONG rVal = ChangeDisplaySettings(&dm, 0);
    return rVal;
}
BOOL SetResolveRatio(DWORD w, DWORD h, DWORD bit, DWORD Fre)
{
    VIDEOMODE DC(bit, w, h, Fre);

    return ChangeVideoModeTemporarily(DC) == 0;
}

/**************************屏幕单位转换************************/

double ChangeUnit(double srval, int src, int target)
{
    double result; 
    if (src == target)
    {
        result = srval;
    }
    else
    {
        result = 0.0;
        switch (src)
        {
        case 2:
            if (target)
            {
                if (target == 1)
                {
                    result = srval * 0.0394;
                }
                else if (target == 3)
                {
                    result = srval * 0.1;
                }
            }
            else
            {
                result = srval * 2.8368;
            }
            break;
        case 3:
            if (target)
            {
                if (target == 1)
                {
                    result = srval * 0.394;
                }
                else if (target == 2)
                {
                    result = srval * 10.0;
                }
            }
            else
            {
                result = srval * 28.368;
            }
            break;
        case 1:
            if (target)
            {
                if (target == 2)
                {
                    result = srval * 25.38071065989848;
                }
                else if (target == 3)
                {
                    result = srval * 2.538071065989848;
                }
            }
            else
            {
                result = srval * 72.0;
            }
            break;
        case 0:
            switch (target)
            {
            case 1:
                result = srval * 0.01388888888888889;
                break;
            case 2:
                result = srval * 0.3525098702763678;
                break;
            case 3:
                result = srval * 0.03525098702763678;
                break;
            }
            break;
        default:
            return result;
        }
    }
    return result;
}

/**************************取当前鼠标处颜色值************************/
bool GetPointRGB(BYTE* r, BYTE* g, BYTE* b)
{
    POINT Point;
    HDC hdc = GetDC(0);
    GetCursorPos(&Point);
    COLORREF pClor = GetPixel(hdc, Point.x, Point.y);
    *r = GetRValue(pClor);
    *g = GetGValue(pClor);
    *b = GetBValue(pClor);
    return ReleaseDC(0, hdc);
}

/**************************取所有窗口列表************************/

static BOOL WinEnumWindowsProc(HWND hWnd, LPARAM lParm)
{
    vector<HWND>* ret = (vector<HWND>*)lParm;
    if (GetWindowLongA(hWnd, -16) & 0x10000000)
    {
        ret->push_back(hWnd);
    }
    return 1;
}
vector<HWND> GetAllWindowsList()
{
    vector<HWND> ret;
    EnumWindows((WNDENUMPROC)WinEnumWindowsProc, (LPARAM)&ret);
    return ret;
}


/**************************取鼠标所在窗口句柄************************/


HWND GetSmallestWindowFromPoint(POINT Point) {
    tagRECT Rect; RECT rc; HWND ret = NULL;
    HWND hPrWnd, hWnd = WindowFromPoint(Point);
    if (hWnd && (GetWindowRect(hWnd, &Rect), (hPrWnd = GetParent(hWnd)) != 0)) {
        HWND temp = hWnd;
        do
        {
            temp = GetWindow(temp, 2u);
            GetWindowRect(temp, &rc);
            if (PtInRect(&rc, Point)
                && GetParent(temp) == hPrWnd
                && IsWindowVisible(temp)
                && (rc.right - rc.left) * (rc.bottom - rc.top) < (Rect.right - Rect.left) * (Rect.bottom - Rect.top))
            {
                ret = temp;
                GetWindowRect(temp, &Rect);
            }
        } while (temp);
    }
    else
    {
        ret = hWnd;
    }
    return  ret;
}


/**************************映射网络驱动器************************/
bool NetAddConnection(string path, string dev) {

    if (dev.size() > 1)
    {
        if (dev.substr(dev.size() - 1) != ":")
        {
            dev += ":";
        }
    }
    if (path.size() > 2)
    {
        if (path.substr(0, 2) != "\\\\")
        {
            path = "\\\\" + path;
        }
    }

    NETRESOURCEA NetResource = { 0 };
    NetResource.dwType = RESOURCETYPE_ANY;
    NetResource.dwScope = RESOURCE_GLOBALNET;
    NetResource.dwUsage = RESOURCEUSAGE_CONNECTABLE;
    NetResource.lpLocalName = const_cast<char*>(dev.c_str());
    NetResource.lpRemoteName = const_cast<char*>(path.c_str());
    NetResource.lpProvider = NULL;
    if (::WNetAddConnection2A(&NetResource, 0, 0, 0) != NO_ERROR) {

        return false;

    };
    return true;

}

/**************************发送局域网消息************************/
BOOL  NetSendMessage(string Target, string _msg) {
    OSVERSIONINFOW verinfo;
    verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
    GetVersionExW(&verinfo);
    if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
        if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) return FALSE;
    }
    else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) return FALSE;
    else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) return FALSE;
    BOOL ret = FALSE;
    if (Target.empty())
    {
        vector<string> List = GetComputerList("");
        for (size_t i = 0; i < List.size(); i++)
        {
            wchar_t* server = new wchar_t[List[i].size() + 1], * msg = new wchar_t[_msg.size() + 1];
            mbstowcs(server, List[i].c_str(), List[i].size());
            mbstowcs(msg, _msg.c_str(), _msg.size());
            if (NetMessageBufferSend(NULL, server, NULL, (BYTE*)&msg[0], wcslen(msg) * sizeof(wchar_t)))
            {
                ret = TRUE;
            }
            delete[]server;
            delete[]msg;
        }
    }
    else
    {
        wchar_t* server = new wchar_t[Target.size() + 1], * msg = new wchar_t[_msg.size() + 1];
        mbstowcs(server, Target.c_str(), Target.size());
        mbstowcs(msg, _msg.c_str(), _msg.size());
        if (NetMessageBufferSend(NULL, server, NULL, (BYTE*)&msg[0], wcslen(msg) * sizeof(wchar_t)))
        {
            ret = TRUE;
        }
        delete[]server;
        delete[]msg;
    }

    return  ret;
}


/**************************取网络共享资源列表************************/
vector<string>GetShareResourceList(string computer, int type) {
    vector<string> 所有网络工作组;
    vector<string> result;
    if (!computer.empty())
    {
        所有网络工作组.push_back(computer);
    }
    else
    {
        所有网络工作组 = GetComputerList(string());
    }
    if (所有网络工作组.size() > 0)
    {
        NETRESOURCEA NetResource;    HANDLE hEnum;
        for (size_t i = 0; i < 所有网络工作组.size(); i++)
        {
            NetResource.lpRemoteName = (LPSTR)computer.c_str();
            if (!WNetOpenEnumA(RESOURCE_GLOBALNET, type, RESOURCEUSAGE_CONTAINER, &NetResource, &hEnum))
            {
                DWORD cCount = 0xFFFFFFFF;
                DWORD BufferSize = sizeof(NETRESOURCEA) * 256;
                NETRESOURCEA* pBuff = new NETRESOURCEA[256];
                DWORD Errcode = WNetEnumResourceA(hEnum, &cCount, pBuff, &BufferSize);
                if (Errcode == ERROR_NO_MORE_ITEMS || Errcode) {
                    delete[]pBuff;
                    break;
                }
                if (cCount)
                {
                    for (size_t d = 0; d < cCount; d++)
                    {
                        CHAR TEMP[260] = { 0 };
                        strcpy(TEMP, pBuff[d].lpRemoteName);
                        result.push_back(TEMP);
                    }

                }
                delete[]pBuff;
            }
            WNetCloseEnum(hEnum);
        }


    }
    return result;

}

/**************************取消网络驱动器映射************************/
bool CancelNetConnection(string Dev) {
    if (Dev.size() > 1)
    {
        if (Dev.substr(Dev.size() - 1) != ":")
        {
            Dev += ":";
        }
    }
    if (::WNetCancelConnection2A(Dev.c_str(), 0, FALSE) != NO_ERROR) {
        return false;
    };
    return true;

}
/**************************取消自动运行************************/

bool CancelAutoRun(string lpValueName)
{
    bool Ret = false;
    HKEY hKeyAutoStart;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKeyAutoStart) == ERROR_SUCCESS)
    {
        if (RegDeleteValueA(hKeyAutoStart, lpValueName.c_str()) == ERROR_SUCCESS) {
            Ret = true;
        };
        RegFlushKey(HKEY_CURRENT_USER);
    }
    //注册表中处理结束，开始处理启动恩简介
    CHAR pszPath[MAX_PATH];
    SHGetSpecialFolderPathA(0, pszPath, 7, 0);
    wsprintfA(pszPath, "%s\\%s.lnk", &pszPath, lpValueName.c_str());
    if (DeleteFileA(pszPath)) {
        Ret = true;

    }
    NotifyShellA(SHCNE_DELETE | SHCNE_INTERRUPT, pszPath);
    return Ret;

}

/**************************取打印机列表A************************/

vector<string> GetPrinterList()
{
    DWORD needed = 0;
    DWORD returned = 0;
    vector<string> ret;
    if (!EnumPrintersA(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 1, 0, 0, &needed, &returned)) {
        LPBYTE buffer = new BYTE[needed];
        if (EnumPrintersA(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 1, buffer, needed, &needed, &returned)) {
            PPRINTER_INFO_1A infoList = reinterpret_cast<PPRINTER_INFO_1A>(buffer);

            for (DWORD i = 0; i < returned; ++i) {
                ret.push_back(infoList[i].pName);
            }
        }
        delete[] buffer;
    }
    return ret;
}


/**************************默认打印机************************/
string MyGetDefaultPrinter() {
    
    OSVERSIONINFOA VersionInformation = { 0 };
    DWORD pcbNeeded = 0;
    DWORD pcReturned = 0;
    VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    GetVersionExA(&VersionInformation);
    DWORD NameSize = 512;
    char Ret[512] = { 0 };
    if (VersionInformation.dwPlatformId == 1)
    {
        SetLastError(0);
        EnumPrintersA(1u, 0, 2u, 0, 0, &pcbNeeded, &pcReturned);
        if (GetLastError() == 122 && pcbNeeded)
        {
            LPBYTE buffer = new BYTE[pcbNeeded];
            if (!buffer) {
                return 0;
            }
            if (!EnumPrintersA(1u, 0, 2u, buffer, pcbNeeded, &pcbNeeded, &pcReturned))
            {
                delete[]buffer;
                return 0;
            }
            PPRINTER_INFO_2A PriterInfo = (PPRINTER_INFO_2A)buffer;
            if (strlen(PriterInfo->pPrinterName) >= NameSize)
            {
                delete[]buffer;;
                return 0;
            }
            strcpy(Ret, PriterInfo->pPrinterName);
            delete[]buffer;;
            return Ret;
        }
        return string();
    }
    if (VersionInformation.dwPlatformId != 2) {
        return string();
    }
    if (VersionInformation.dwMajorVersion >= 5)
    {

        if (!GetDefaultPrinterA(Ret, &NameSize)) {
            return string();
        }
        return Ret;
    }
    if (!GetProfileStringA("windows", "device", ",,,", Ret, NameSize)) {
        return string();
    }
    strtok(Ret, ",");
    if (strlen(Ret) >= NameSize)
    {
        return string();
    }
    return Ret;
}


BOOL MySetDefaultPrinter(string pPrinterName) {
    OSVERSIONINFOA VersionInformation = {0};
    HANDLE phPrinter=0;
    DWORD pcbNeeded=0;
    LPBYTE pBuffer=0;
    VersionInformation.dwOSVersionInfoSize = sizeof(VersionInformation);
    if (pPrinterName.empty()) {
        return 0;
    }
    if (VersionInformation.dwPlatformId == 1)
    {
        if (OpenPrinterA(const_cast<char*>(pPrinterName.c_str()), &phPrinter, 0) && phPrinter)
        {
            SetLastError(0);
            if (!GetPrinterA(phPrinter, 2u, 0, 0, &pcbNeeded) && (GetLastError() != ERROR_INSUFFICIENT_BUFFER || !pcbNeeded))
            {
                ClosePrinter(phPrinter);
                return 0;
            }
            pBuffer = new BYTE[pcbNeeded];
            if (!pBuffer)
            {
                ClosePrinter(phPrinter);
                return 0;
            }
            if (!GetPrinterA(phPrinter, 2u, pBuffer, pcbNeeded, &pcbNeeded))
            {
                ClosePrinter(phPrinter);
                delete[]pBuffer;
                return 0;
            }
            PRINTER_INFO_2A* pi2 = (PRINTER_INFO_2A*)pBuffer;
            if (!SetPrinterA(phPrinter, 2u, pBuffer, 0)) {
                ClosePrinter(phPrinter);
                delete[]pBuffer;
                return 0;
            }
            if (phPrinter) {
                ClosePrinter(phPrinter);
            }
            if (pBuffer) {
                delete[]pBuffer;
            }
            return true;
        }
        return false;
    }
    if (VersionInformation.dwPlatformId == 2)
    {
        if (VersionInformation.dwMajorVersion < 5)
        {
            if (!OpenPrinterA(const_cast<char*>(pPrinterName.c_str()), &phPrinter, 0) || !phPrinter)
            {
                return 0;
            }
            SetLastError(0);
            if (!GetPrinterA(phPrinter, 2u, 0, 0, &pcbNeeded) && (GetLastError() != ERROR_INSUFFICIENT_BUFFER || !pcbNeeded))
            {
                ClosePrinter(phPrinter);
                return 0;
            }
            pBuffer = new BYTE[pcbNeeded];
            PRINTER_INFO_2A* pi2 = (PRINTER_INFO_2A*)pBuffer;
            if (!pBuffer)
            {
                ClosePrinter(phPrinter);
                return 0;
            }
            pi2->Attributes |= 4u;
            if (!GetPrinterA(phPrinter, 2u, (LPBYTE)pBuffer, pcbNeeded, &pcbNeeded)
                || !pi2->pPortName
                || !pi2->pDriverName)
            {
                ClosePrinter(phPrinter);
                delete[]pBuffer;
                return 0;
            }

            string instructions = pPrinterName.c_str();

            instructions = instructions + "," + pi2->pDriverName + "," + pi2->pPortName;

            if (!WriteProfileStringA("windows", "device", instructions.c_str()))
            {
                ClosePrinter(phPrinter);
                delete[]pBuffer;
                return 0;
            }
        }
        else
        {
            if (!SetDefaultPrinterA(pPrinterName.c_str())) {
                return 0;
            }

        }
    }
    if (phPrinter) {
        ClosePrinter(phPrinter);
    }
    if (pBuffer) {
        delete[]pBuffer;
    }
    return true;
}



/***********************取屏幕DPI********************/
DOUBLE GetMoniterDPI(HWND hWnd)
{
  
    if (hWnd == NULL)
        hWnd = GetDesktopWindow();

    INT nDPI = 0;

    const HINSTANCE hInstWinSta = LoadLibraryW(L"SHCore.dll");
    if (hInstWinSta != NULL)
    {
        typedef HRESULT(WINAPI* PFN_GDFM) (HMONITOR, INT, UINT*, UINT*);
        typedef HRESULT(WINAPI* FN_SET_PROCESS_DPI_AWARENESS)(INT nValue);

        FN_SET_PROCESS_DPI_AWARENESS fnSetProcessDpiAwareness = (FN_SET_PROCESS_DPI_AWARENESS)GetProcAddress(hInstWinSta, "SetProcessDpiAwareness");
        if (fnSetProcessDpiAwareness != NULL)
            fnSetProcessDpiAwareness(2);
        PFN_GDFM fnGetDpiForMonitor = (PFN_GDFM)GetProcAddress(hInstWinSta, "GetDpiForMonitor");
        if (fnGetDpiForMonitor != NULL)
        {
            UINT dpiX;
            fnGetDpiForMonitor(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), 0, &dpiX, (UINT*)&nDPI);
        }

        FreeLibrary(hInstWinSta);
    }

    if (nDPI == 0)
    {
        const HDC hDC = ::GetDC(hWnd);
        nDPI = GetDeviceCaps(hDC, LOGPIXELSY);
        ::ReleaseDC(hWnd, hDC);
    }

    const DOUBLE dbDpi = (DOUBLE)nDPI / 96.0;
    return 1.0 > dbDpi ? 1.0 : dbDpi;
}

/***********************取图片格式********************/
inline static bool islike(string arg1, string arg2)
{

    size_t i;
    char isnend;
    bool result;
    register  const char* str1 = arg1.c_str();
    register  const char* str2 = arg2.c_str();

    if (str1 && str2 && *str1 && *str2)
    {
        i = str1 - str2;
        do
        {
            if (!*str2)
                break;
            if (str2[i] != *str2)
                break;
            isnend = (str2++)[i + 1];
        } while (isnend);
        result = *str2 == 0;
    }
    else
    {
        result = 0;
    }

    return result;
}
inline static std::string  byte2hex(vector<unsigned char> pBuffer)//将字节集用16进制表示.可以将字节集用系统标准16进制表示
{
    string Ret;
    size_t dwBufLen;
    dwBufLen = pBuffer.size();
    for (size_t i = 0; i < dwBufLen; i++) {
        char temp[255] = {0};
        sprintf(temp, "%02X", pBuffer[i]);
        Ret.append(temp);
    }
    return Ret;
}
std::string  GetPictureFormat(string path)//根据文件头部判断文件格式，成功返回格式名称，失败返回空。
{
    HANDLE hFile;
    std::string Hex;
    DWORD readSize;
    hFile = CreateFileA(path.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return "";
    }
    unsigned char* data = new unsigned char[16];//取前16位
    if (ReadFile(hFile, data, 16, &readSize, NULL) == FALSE) {
        return {};
    };
    CloseHandle(hFile);
    if (readSize == 16) {
        Hex = byte2hex(vector<unsigned char>(data, data + 16));
        if (islike(Hex, "FFD8FF")) {
            return "JPEG";
        }
        else if (islike(Hex, "89504E470D0A1A0A0000000D49484452")) {
            return "PNG";
        }
        else if (islike(Hex, "47494638") || islike(Hex, "474946383761") || islike(Hex, "474946383961")) {
            return "GIF";
        }
        else if (islike(Hex, "49492A00") || islike(Hex, "4D4D002A") || islike(Hex, "49492A00")) {
            return "TIFF";
        }
        else if (islike(Hex, "424D")) {
            return "BMP";
        }
        else if (islike(Hex, "0A")) {
            return "PCX";
        }
        else if (islike(Hex, "3C")) {
            return "SVG";
        }
        else if (islike(Hex, "38425053000100000000000000")) {
            return "PSD";
        }
        else if (islike(Hex, "465753")) {
            return "SWF";
        }
        else if (islike(Hex, "D7CDC69A0000")) {
            return "WMF";
        }
        else if (islike(Hex, "01000000")) {
            return "EMF";
        }
        else if (islike(Hex, "C5D0D3C6")) {
            return "EPS";
        }
        else if (islike(Hex, "0000020000") || islike(Hex, "0000100000")) {
            return "TGA";
        }
        else if (islike(Hex, "00000100")) {
            return "ICO";
        }
        else if (islike(Hex, "00000200")) {
            return "CUR";
        }
        else if (islike(Hex, "52494646")) {
            return "ANI";
        }
        else if (islike(Hex, "464F524D")) {
            return "IFF";
        }
        else {
        }
    }
    return "";
}

std::string  GetPictureFormat(vector<unsigned char> _data)//根据文件头部判断文件格式，成功返回格式名称，失败返回空。
{
    vector<unsigned char> data;
    std::string Hex;
    size_t readSize = data.size();

    if (data.empty() || readSize < 16) {
        return "";
    }
    data = vector<unsigned char>(_data.data(), _data.data() + 16);
    if (data.size() == 16) {
        Hex = byte2hex(data);
        if (islike(Hex, "FFD8FF")) {
            return "JPEG";
        }
        else if (islike(Hex, "89504E470D0A1A0A0000000D49484452")) {
            return "PNG";
        }
        else if (islike(Hex, "47494638") || islike(Hex, "474946383761") || islike(Hex, "474946383961")) {
            return "GIF";
        }
        else if (islike(Hex, "49492A00") || islike(Hex, "4D4D002A") || islike(Hex, "49492A00")) {
            return "TIFF";
        }
        else if (islike(Hex, "424D")) {
            return "BMP";
        }
        else if (islike(Hex, "0A")) {
            return "PCX";
        }
        else if (islike(Hex, "3C")) {
            return "SVG";
        }
        else if (islike(Hex, "38425053000100000000000000")) {
            return "PSD";
        }
        else if (islike(Hex, "465753")) {
            return "SWF";
        }
        else if (islike(Hex, "D7CDC69A0000")) {
            return "WMF";
        }
        else if (islike(Hex, "01000000")) {
            return "EMF";
        }
        else if (islike(Hex, "C5D0D3C6")) {
            return "EPS";
        }
        else if (islike(Hex, "0000020000") || islike(Hex, "0000100000")) {
            return "TGA";
        }
        else if (islike(Hex, "00000100")) {
            return "ICO";
        }
        else if (islike(Hex, "00000200")) {
            return "CUR";
        }
        else if (islike(Hex, "52494646")) {
            return "ANI";
        }
        else if (islike(Hex, "464F524D")) {
            return "IFF";
        }
        else {
        }
    }
    return "";
}




/*********************************取硬盘编号*****************************/

static inline BOOL GetDiskByCmd(string& ider)
{
    //diskdrive
    const long MAX_COMMAND_SIZE = 10000; // 命令行输出缓冲大小     
    CHAR szFetCmd[] = "wmic diskdrive get serialnumber"; // 获取DiskDrive命令行    
    const string strEnSearch = "SerialNumber"; // DiskDrive序列号的前导信息  


    BOOL   bret = FALSE;
    HANDLE hReadPipe = NULL; //读取管道  
    HANDLE hWritePipe = NULL; //写入管道      
    PROCESS_INFORMATION pi;   //进程信息      
    STARTUPINFO         si;   //控制命令行窗口信息  
    SECURITY_ATTRIBUTES sa;   //安全属性  

    char            szBuffer[MAX_COMMAND_SIZE + 1] = { 0 }; // 放置命令行结果的输出缓冲区  
    string          strBuffer;
    unsigned long   count = 0;
    long            ipos = 0;

    memset(&pi, 0, sizeof(pi));
    memset(&si, 0, sizeof(si));
    memset(&sa, 0, sizeof(sa));

    pi.hProcess = NULL;
    pi.hThread = NULL;
    si.cb = sizeof(STARTUPINFO);
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    //1.0 创建管道  
    bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
    if (!bret)
    {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return(bret);
    }

    //2.0 设置命令行窗口的信息为指定的读写管道  
    GetStartupInfo(&si);
    si.hStdError = hWritePipe;
    si.hStdOutput = hWritePipe;
    si.wShowWindow = SW_HIDE; //隐藏命令行窗口  
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

    //3.0 创建获取命令行的进程  
    bret = CreateProcessA(NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    if (!bret)
    {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return(bret);
    }



    //4.0 读取返回的数据  
    WaitForSingleObject(pi.hProcess, 500/*INFINITE*/);
    bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
    if (!bret)
    {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return(bret);
    }

    //5.0 查找CPU序列号  
    bret = FALSE;
    strBuffer = szBuffer;
    ipos = strBuffer.find(strEnSearch);

    if (ipos < 0) // 没有找到  
    {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return(bret);
    }
    else
    {
        strBuffer = strBuffer.substr(ipos + strEnSearch.length());
    }

    memset(szBuffer, 0x00, sizeof(szBuffer));
    strcpy_s(szBuffer, strBuffer.c_str());

    //modify here
    //去掉中间的空格 \r \n     
    char temp[512];
    memset(temp, 0, sizeof(temp));

    int index = 0;
    for (size_t i = 0; i < strBuffer.size(); i++)
    {
        if (strBuffer[i] != ' ' && strBuffer[i] != '\n' && strBuffer[i] != '\r')
        {
            temp[index] = strBuffer[i];
            index++;
        }
    }
    ider = temp;

    bret = TRUE;


    //关闭所有的句柄  
    CloseHandle(hWritePipe);
    CloseHandle(hReadPipe);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return(bret);
}

string GetDiskNumber() {
    string Ret;
    GetDiskByCmd(Ret);
    return Ret;
}

/*********************************程序提权*****************************/
bool UpPrivilegeValue()
{
    //OpenProcessToken()函数用来打开与进程相关联的访问令牌
    HANDLE hToken = nullptr;
    if (FALSE == OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
    {
        return false;
    }
    //LookupPrivilegeValue()函数查看系统权限的特权值
    LUID luid;
    if (FALSE == LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
    {
        CloseHandle(hToken);
        return false;
    }
    //调整权限设置
    TOKEN_PRIVILEGES Tok;
    Tok.PrivilegeCount = 1;
    Tok.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    Tok.Privileges[0].Luid = luid;
    if (FALSE == AdjustTokenPrivileges(hToken, FALSE, &Tok, sizeof(Tok), nullptr, nullptr))
    {
        CloseHandle(hToken);
        return false;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
    {
        CloseHandle(hToken);
        return false;
    }

    CloseHandle(hToken);
    return true;
}

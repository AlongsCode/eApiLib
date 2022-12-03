#pragma once
#include<vector>
#include<string>
//#include<optional>
using namespace std;
typedef struct MYPRINTINFO
{
	char* DeviceName;
	int Orientation;
	int PaperSize;
	int PaperWidth;
	int PaperLength;
	int Copies;
	MYPRINTINFO()
	{
		DeviceName = 0;
		Orientation = 0;
		PaperSize = 9;
		PaperWidth = 0;
		PaperLength = 0;
		Copies = 1;
	}
}*PMYPRINTINFO;
typedef struct HDInfo
{
	char* model;
	char* Version;
	char* serial;
	//单位:MB
	size_t capacity ;
	//单位:MB
	size_t cachesize ;
	size_t sectorspertrack;
	size_t heads ;
	size_t cylinders;
	HDInfo() {//VC6只能这样初始化
		memset(this, 0, sizeof(*this));
	}
}* PHDINFO;
typedef struct PROCINF
{
	DWORD identifier;
	CHAR* name;
	DWORD    modidentifier ;
	DWORD    pidentifier;
	LONG    priority;
	DWORD   size;
	PROCINF() {
		memset(this, 0, sizeof(*this));
	}
}*LPPROCINF;;
typedef struct  _NETWORKINFO
{
	CHAR* name;
	int     index;
	CHAR* Address;
	CHAR* IpAddress;
	CHAR* IpMask;
	CHAR* DefaultGateway;
	CHAR* WinsAddress;
	CHAR* DHCPAdress;
	_NETWORKINFO() {
		memset(this, 0, sizeof(*this));
	}

}*PNETWORKINFO;

typedef struct _ESYSINFO
{
	char* winsys;
	char* vsion;
	int buildvsion;
	char* lastpack;
	char* user;
	char* windir;
	char* sysdir;
	//语言代码
	int code;
	char* locallanguage;
	//非标准国家代码,为电话代码
	int countyrcode;
	//官方名称
	char* countryname;
	char* money;
	char* dataformat;
	char* timeformat;
	char* timezone;
	char* iso;
	bool isx64;
	_ESYSINFO() {
		memset(this, 0, sizeof(*this));
	}
}*PESYSINFO;
typedef struct BIOSINFO {
	char* name;
	char* manufacturer;
	char* version;
	char* data;
	char* ID;
	char* OEM;
	BIOSINFO() {
		memset(this, 0, sizeof(*this));
	}
}*PEBIOSINFO;
typedef struct EFileINfo
{
	char* vision;
	char* description;
	char* inname;
	char* companyname;
	char* copyright;
	char* trademark;
	char* name;
	char* Productname;
	char* productversion;
	char* language;
	char* Remarks;
	//个人编译版本说明
	char* privatebuild;
	//特殊编译版说明
	char* Specialbuild;
	EFileINfo() {
		memset(this, 0, sizeof(*this));
	}
}*PEFileINfo;
typedef struct CPUINFO
{
	char* Vendor;
	char* name;
	//单位：MHz。
	int  hz ;
	char* Description;
	int  L1;
	int  L2;
	char* ID;
	//CPU位宽单位：位。
	int Bit;
	int L3;
	int cores;
	int threadcount;
	CPUINFO() {
		memset(this, 0, sizeof(*this));
	}
}*PCPUINFO;
typedef  struct VIDEOMODE
{
	
	DWORD m_dwWidth;
	DWORD m_dwHeight;
	DWORD m_dwFrequency;
	DWORD m_dwBitsPerPixel;
	VIDEOMODE() {
		memset(this, sizeof(this), 0);
	}
	VIDEOMODE(DWORD BitsPerPixel, DWORD Width, DWORD Height, DWORD Frequency) {
		m_dwBitsPerPixel = BitsPerPixel;
		m_dwWidth = Width;
		m_dwHeight = Height;
		m_dwFrequency = Frequency;
	}
}*PVIDEOMODE;
vector<VIDEOMODE> GetVideoList();
char* GetRemoteMac(char* ip);
char* GetIpFromHostName(char* MachineName);
char* GetRemoteName(char* ip);
char* GetLocalMac(int NetIndex);
char* GetLocalAdapterName(int NetIndex);
vector<_NETWORKINFO> GetApapterList();
double GetCpuUsges();
char* GetAudioCard(); 
DOUBLE GetMoniterDPI(HWND hWnd);
std::string  GetPictureFormat(string path);
bool UpPrivilegeValue();
string GetDiskNumber();
std::string  GetPictureFormat(vector<unsigned char> data);
INT OpenPrintSetDlg(INT Type, MYPRINTINFO* pPrintInfo);
std::wstring A2W(std::string str);
VIDEOMODE GetCurVideo();
BOOL ClearHistory(int  type);
BOOL DeleteTempFile(int type);
bool SetAutoRun(string lpValueName, string path, bool toreskey);
bool DeleteTmpFile(string lpValueName);
bool AddRightMenu(string Rangeorextensiontobeused, string Title, string comline, string shortkey, string icon, bool shiftdisplay);
bool DeleteRightMenu(string Rangeorextensiontobeused, string Title);
size_t GetMemoryInfo(unsigned short val);
BOOL GetCpuInfo(CPUINFO* pCpuinfo);
bool MyGetFileVersionInfo(char* FlieNmae, EFileINfo* pInfo);
void GetBiosInfo(BIOSINFO* pBIOSINFO);
BOOL  GetKeyboardLockState(int Type);
BYTE MyVkKeyScanExA(MDATA_INF pArgInf);
void  SimulateKey(BYTE bVk, BYTE bVk2, BYTE bVk3);
void SimulateMouse(int X, int Y, int Type);
INT GetDrivesNum(INT type);
bool GetHDInfo(HDInfo* pHDInfo, int HDIndex);
vector<string> GetDrivesList(int type);
MCIERROR ControlCdrom(bool pop);
char* GetCdrom();
BOOL IsDiskInside();
vector<PROCINF> GetProcessList();
BOOL KillProcess(int ID);
BOOL KillProcess(char* TEXT);
vector<string> GetDllList( int ID);
vector<string> GetHungProgramList();
BOOL SetResolveRatio(DWORD w, DWORD h, DWORD bit, DWORD Fre);
double ChangeUnit(double srval, int src, int target);
bool GetPointRGB(BYTE* r, BYTE* g, BYTE* b);
void GetSysInfo(_ESYSINFO* pSysInfo);
vector<string> GetFontListA();
HANDLE  AddFont(LPBYTE FontPath);
bool  AddFont(string FontPath);
bool   IsConnectToInternet();
vector<HWND> GetAllWindowsList();
HWND GetSmallestWindowFromPoint(POINT Point);
bool NetAddConnection(string path, string dev);
BOOL  NetSendMessage(string Target, string _msg);
vector<string>GetShareResourceList(string computer, int type);
bool OpenURL(char* Url);
bool  SetDeskWallPaper(string FileNmae, int stytle);
bool CheckPort(u_short port, char* ipadress);
bool RemoveFont(HANDLE hF);
char* GetIEVersion();
bool CancelNetConnection(string Dev);
bool CancelAutoRun(string lpValueName);
vector<string> GetPrinterList();
string MyGetDefaultPrinter();

BOOL MySetDefaultPrinter(string pPrinterName);
bool RemoveFont(string lpFileName);
SIZE  GetImageSize(LPBYTE _data);//快速读取图片高度，失败返回零。
SIZE   GetImageSize(string ImagePat);
int GetIconFromResource(string PathName, bool Extract2ClipBoard, string SaveName, int _Index);
BOOL  AddButtonToIE(string ButtTitle, string Icon, string Comline, string HotIcon, BOOL IsVisible);
BOOL  DeleteButtonFromIE(const char* Button);
BOOL CreateProgramGroup(const char* path, int position);
bool EmptyDirectory(const WCHAR* Path, int type1, int type2);
BOOL GetShortCutTarget(const wstring& lpszLinkFilePath, wstring* FilePath, wstring* LinkArg, wstring* BeginPosition, wstring* IconPath, int* RunMod, int* shortkey, wstring* remarks);
BOOL GetShortCutTarget(const wstring& lpszLinkFilePath, wstring* FilePath, wstring* LinkArg, wstring* BeginPosition, wstring* IconPath, int* RunMod, wstring* shortkey, wstring* remarks);
BOOL CreateLink(string LinkName, string FilePath, string remark, WORD wHotkey, string comline, string workdir);
BOOL DeleteProgramItem(const char* GroupName, const char* ItemName, int position);
BOOL CreateProgramItem(const char* GroupName, const char* ItemName, const char* ItemPath, int position);
bool CancelAutoRun(char* lpValueName);
vector<string> GetNetList();
vector<string> GetGroupList(string NetType);
vector<string>GetComputerList(string group);
void  OpenSysWindow(int Type, int PageIndex);
bool SetDiaphaneity(HWND hWnd, unsigned char alpha, COLORREF key, bool through);
int  CopyScreenToBitmap(RECT* lprc, int Type, LPSTR lpFileName);
HBITMAP  CopyScreenToBitmap(RECT* lprc);
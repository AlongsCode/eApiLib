
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma pack( push )
#pragma pack( 2 )
typedef struct
{
	BYTE	bWidth;
	BYTE	bHeight;
	BYTE	bColorCount;
	BYTE	bReserved;
	WORD	wPlanes;
	WORD	wBitCount;
	DWORD	dwBytesInRes;
	WORD	nID;
} MEMICONDIRENTRY, * LPMEMICONDIRENTRY;
typedef struct
{
	WORD			idReserved;
	WORD			idType;
	WORD			idCount;
	MEMICONDIRENTRY	idEntries[1];
} MEMICONDIR, * LPMEMICONDIR;
#pragma pack( pop )

typedef struct
{
	BYTE	bWidth;
	BYTE	bHeight;
	BYTE	bColorCount;
	BYTE	bReserved;
	WORD	wPlanes;
	WORD	wBitCount;
	DWORD	dwBytesInRes;
	DWORD	dwImageOffset;
} ICONDIRENTRY, * LPICONDIRENTRY;
typedef struct
{
	WORD			idReserved;
	WORD			idType;
	WORD			idCount;
	ICONDIRENTRY	idEntries[1];
} ICONDIR, * LPICONDIR;



typedef struct
{
	UINT			Width, Height, Colors;
	LPBYTE			lpBits;
	DWORD			dwNumBytes;
	LPBITMAPINFO	lpbi;
	LPBYTE			lpXOR;
	LPBYTE			lpAND;
} ICONIMAGE, * LPICONIMAGE;
typedef struct
{
	BOOL		bHasChanged;
	CHAR		szOriginalICOFileName[MAX_PATH];
	CHAR		szOriginalDLLFileName[MAX_PATH];
	UINT		nNumImages;
	ICONIMAGE	IconImages[1];
} ICONRESOURCE, * LPICONRESOURCE;

typedef struct
{
	DWORD	dwBytes;
	DWORD	dwOffset;
} RESOURCEPOSINFO, * LPRESOURCEPOSINFO;

typedef struct
{
	LPCSTR    	szFileName;
	HINSTANCE	hInstance;
	LPSTR    	lpID;
} EXEDLLICONINFO, * LPEXEDLLICONINFO;


#define MAX_ICON_WIDTH	128           
#define MIN_ICON_WIDTH	16              
#define MAX_ICON_HEIGHT	MAX_ICON_WIDTH   
#define MIN_ICON_HEIGHT	MIN_ICON_WIDTH  

class MyIcon
{
public:
	MyIcon();
	virtual ~MyIcon();

public:
	LPICONRESOURCE ReadIconFromICOFile(LPCSTR szFileName);
	BOOL WriteIconToICOFile(LPICONRESOURCE lpIR, LPCSTR szFileName);
	HICON MakeIconFromResource(LPICONIMAGE lpIcon);
	LPICONRESOURCE ReadIconFromEXEFile(LPCSTR szFileName, LPCSTR lpID);
	BOOL IconImageToClipBoard(LPICONIMAGE lpii);
	BOOL IconImageFromBMPFile(LPCSTR szFileName, LPICONIMAGE lpii, BOOL bStretchToFit);
	BOOL IconImageToBMPFile(LPCSTR szFileName, LPICONIMAGE lpii);

private:
	UINT ReadICOHeader(HANDLE hFile);
	BOOL AdjustIconImagePointers(LPICONIMAGE lpImage);
	BOOL WriteICOHeader(HANDLE hFile, UINT nNumEntries);
	DWORD CalculateImageOffset(LPICONRESOURCE lpIR, UINT nIndex);
	BOOL DIBToIconImage(LPICONIMAGE lpii, LPBYTE lpDIB, BOOL bStretch);

};



#include <windows.h>
#include "IconHelp.h"




#if _MSC_VER > 1000
#pragma once
#endif 

#define WIDTHBYTES(bits)      ((((bits) + 31)>>5)<<2)

class MyDib
{
public:
	MyDib();
	virtual ~MyDib();

public:
	LPSTR FindDIBBits(LPSTR lpbi);
	WORD DIBNumColors(LPSTR lpbi);
	WORD PaletteSize(LPSTR lpbi);
	DWORD BytesPerLine(LPBITMAPINFOHEADER lpBMIH);
	LPBYTE ConvertDIBFormat(LPBITMAPINFO lpSrcDIB, UINT nWidth, UINT nHeight, UINT nColors, BOOL bStretch);
	void SetMonoDIBPixel(LPBYTE pANDBits, DWORD dwWidth, DWORD dwHeight, DWORD x, DWORD y, BOOL bWhite);
	LPBYTE ReadBMPFile(LPCSTR szFileName);
	BOOL WriteBMPFile(LPCSTR szFileName, LPBYTE lpDIB);

private:
	BOOL CopyColorTable(LPBITMAPINFO lpTarget, LPBITMAPINFO lpSource);

};
MyDib::MyDib()
{

}

MyDib::~MyDib()
{

}

LPSTR MyDib::FindDIBBits(LPSTR lpbi)
{
    return (lpbi + *(LPDWORD)lpbi + PaletteSize(lpbi));
}

WORD MyDib::DIBNumColors(LPSTR lpbi)
{
    WORD wBitCount;
    DWORD dwClrUsed;

    dwClrUsed = ((LPBITMAPINFOHEADER)lpbi)->biClrUsed;

    if (dwClrUsed)
        return (WORD)dwClrUsed;

    wBitCount = ((LPBITMAPINFOHEADER)lpbi)->biBitCount;

    switch (wBitCount)
    {
    case 1: return 2;
    case 4: return 16;
    case 8:	return 256;
    default:return 0;
    }
    return 0;
}

WORD MyDib::PaletteSize(LPSTR lpbi)
{
    return (DIBNumColors(lpbi) * sizeof(RGBQUAD));
}

DWORD MyDib::BytesPerLine(LPBITMAPINFOHEADER lpBMIH)
{
    return WIDTHBYTES(lpBMIH->biWidth * lpBMIH->biPlanes * lpBMIH->biBitCount);
}

LPBYTE MyDib::ConvertDIBFormat(LPBITMAPINFO lpSrcDIB, UINT nWidth, UINT nHeight, UINT nbpp, BOOL bStretch)
{
    LPBITMAPINFO    lpbmi = NULL;
    LPBYTE        	lpSourceBits, lpTargetBits, lpResult;
    HDC            	hDC = NULL, hSourceDC, hTargetDC;
    HBITMAP        	hSourceBitmap, hTargetBitmap, hOldTargetBitmap, hOldSourceBitmap;
    DWORD        	dwSourceBitsSize, dwTargetBitsSize, dwTargetHeaderSize;

    // Allocate and fill out a BITMAPINFO struct for the new DIB
    // Allow enough room for a 256-entry color table, just in case
    dwTargetHeaderSize = sizeof(BITMAPINFO) + (256 * sizeof(RGBQUAD));
    lpbmi = (LPBITMAPINFO)malloc(dwTargetHeaderSize);
    lpbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    lpbmi->bmiHeader.biWidth = nWidth;
    lpbmi->bmiHeader.biHeight = nHeight;
    lpbmi->bmiHeader.biPlanes = 1;
    lpbmi->bmiHeader.biBitCount = nbpp;
    lpbmi->bmiHeader.biCompression = BI_RGB;
    lpbmi->bmiHeader.biSizeImage = 0;
    lpbmi->bmiHeader.biXPelsPerMeter = 0;
    lpbmi->bmiHeader.biYPelsPerMeter = 0;
    lpbmi->bmiHeader.biClrUsed = 0;
    lpbmi->bmiHeader.biClrImportant = 0;
    // Fill in the color table
    if (!CopyColorTable(lpbmi, (LPBITMAPINFO)lpSrcDIB))
    {
        free(lpbmi);
        return NULL;
    }

    // Gonna use DIBSections and BitBlt() to do the conversion, so make 'em
    hDC = GetDC(NULL);
    hTargetBitmap = CreateDIBSection(hDC, lpbmi, DIB_RGB_COLORS, (void**)&lpTargetBits, NULL, 0);
    hSourceBitmap = CreateDIBSection(hDC, lpSrcDIB, DIB_RGB_COLORS, (void**)&lpSourceBits, NULL, 0);
    hSourceDC = CreateCompatibleDC(hDC);
    hTargetDC = CreateCompatibleDC(hDC);

    // Flip the bits on the source DIBSection to match the source DIB
    dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine(&(lpSrcDIB->bmiHeader));
    dwTargetBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine(&(lpbmi->bmiHeader));
    memcpy(lpSourceBits, FindDIBBits((LPSTR)lpSrcDIB), dwSourceBitsSize);

    // Select DIBSections into DCs
    hOldSourceBitmap = (HBITMAP)SelectObject(hSourceDC, hSourceBitmap);
    hOldTargetBitmap = (HBITMAP)SelectObject(hTargetDC, hTargetBitmap);

    // Set the color tables for the DIBSections
    if (lpSrcDIB->bmiHeader.biBitCount <= 8)
        SetDIBColorTable(hSourceDC, 0, 1 << lpSrcDIB->bmiHeader.biBitCount, lpSrcDIB->bmiColors);
    if (lpbmi->bmiHeader.biBitCount <= 8)
        SetDIBColorTable(hTargetDC, 0, 1 << lpbmi->bmiHeader.biBitCount, lpbmi->bmiColors);

    // If we are asking for a straight copy, do it
    if ((lpSrcDIB->bmiHeader.biWidth == lpbmi->bmiHeader.biWidth) && (lpSrcDIB->bmiHeader.biHeight == lpbmi->bmiHeader.biHeight))
    {
        BitBlt(hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, SRCCOPY);
    }
    else
    {
        // else, should we stretch it?
        if (bStretch)
        {
            SetStretchBltMode(hTargetDC, COLORONCOLOR);
            StretchBlt(hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, lpSrcDIB->bmiHeader.biWidth, lpSrcDIB->bmiHeader.biHeight, SRCCOPY);
        }
        else
        {
            // or just take the upper left corner of the source
            BitBlt(hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, SRCCOPY);
        }
    }

    // Clean up and delete the DCs
    SelectObject(hSourceDC, hOldSourceBitmap);
    SelectObject(hSourceDC, hOldTargetBitmap);
    DeleteDC(hSourceDC);
    DeleteDC(hTargetDC);
    ReleaseDC(NULL, hDC);

    // Flush the GDI batch, so we can play with the bits
    GdiFlush();

    // Allocate enough memory for the new CF_DIB, and copy bits
    lpResult = (LPBYTE)malloc(dwTargetHeaderSize + dwTargetBitsSize);
    memcpy(lpResult, lpbmi, dwTargetHeaderSize);
    memcpy(FindDIBBits((LPSTR)lpResult), lpTargetBits, dwTargetBitsSize);

    // final cleanup
    DeleteObject(hTargetBitmap);
    DeleteObject(hSourceBitmap);
    free(lpbmi);

    return lpResult;
}

BOOL MyDib::CopyColorTable(LPBITMAPINFO lpTarget, LPBITMAPINFO lpSource)
{
    // What we do depends on the target's color depth
    switch (lpTarget->bmiHeader.biBitCount)
    {
        // 8bpp - need 256 entry color table
    case 8:
        if (lpSource->bmiHeader.biBitCount == 8)
        { // Source is 8bpp too, copy color table
            memcpy(lpTarget->bmiColors, lpSource->bmiColors, 256 * sizeof(RGBQUAD));
            return TRUE;
        }
        else
        { // Source is != 8bpp, use halftone palette                
            HPALETTE        hPal;
            HDC            	hDC = GetDC(NULL);
            PALETTEENTRY    pe[256];
            UINT            i;

            hPal = CreateHalftonePalette(hDC);
            ReleaseDC(NULL, hDC);
            GetPaletteEntries(hPal, 0, 256, pe);
            DeleteObject(hPal);
            for (i = 0; i < 256; i++)
            {
                lpTarget->bmiColors[i].rgbRed = pe[i].peRed;
                lpTarget->bmiColors[i].rgbGreen = pe[i].peGreen;
                lpTarget->bmiColors[i].rgbBlue = pe[i].peBlue;
                lpTarget->bmiColors[i].rgbReserved = pe[i].peFlags;
            }
            return TRUE;
        }
        break; // end 8bpp

        // 4bpp - need 16 entry color table
    case 4:
        if (lpSource->bmiHeader.biBitCount == 4)
        { // Source is 4bpp too, copy color table
            memcpy(lpTarget->bmiColors, lpSource->bmiColors, 16 * sizeof(RGBQUAD));
            return TRUE;
        }
        else
        { // Source is != 4bpp, use system palette
            HPALETTE        hPal;
            PALETTEENTRY    pe[256];
            UINT            i;

            hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);
            GetPaletteEntries(hPal, 0, 16, pe);
            for (i = 0; i < 16; i++)
            {
                lpTarget->bmiColors[i].rgbRed = pe[i].peRed;
                lpTarget->bmiColors[i].rgbGreen = pe[i].peGreen;
                lpTarget->bmiColors[i].rgbBlue = pe[i].peBlue;
                lpTarget->bmiColors[i].rgbReserved = pe[i].peFlags;
            }
            return TRUE;
        }
        break; // end 4bpp

        // 1bpp - need 2 entry mono color table
    case 1:
        lpTarget->bmiColors[0].rgbRed = 0;
        lpTarget->bmiColors[0].rgbGreen = 0;
        lpTarget->bmiColors[0].rgbBlue = 0;
        lpTarget->bmiColors[0].rgbReserved = 0;
        lpTarget->bmiColors[1].rgbRed = 255;
        lpTarget->bmiColors[1].rgbGreen = 255;
        lpTarget->bmiColors[1].rgbBlue = 255;
        lpTarget->bmiColors[1].rgbReserved = 0;
        break; // end 1bpp

        // no color table for the > 8bpp modes
    case 32:
    case 24:
    case 16:
    default:
        return TRUE;
        break;
    }
    return TRUE;
}

void MyDib::SetMonoDIBPixel(LPBYTE pANDBits, DWORD dwWidth, DWORD dwHeight, DWORD x, DWORD y, BOOL bWhite)
{
    DWORD	ByteIndex;
    BYTE    BitNumber;

    // Find the byte on which this scanline begins
    ByteIndex = (dwHeight - y - 1) * WIDTHBYTES(dwWidth);
    // Find the byte containing this pixel
    ByteIndex += (x >> 3);
    // Which bit is it?
    BitNumber = (BYTE)(7 - (x % 8));

    if (bWhite)
        // Turn it on
        pANDBits[ByteIndex] |= (1 << BitNumber);
    else
        // Turn it off
        pANDBits[ByteIndex] &= ~(1 << BitNumber);
}

LPBYTE MyDib::ReadBMPFile(LPCSTR szFileName)
{
    HANDLE            	hFile;
    BITMAPFILEHEADER    bfh;
    DWORD            	dwBytes;
    LPBYTE            	lpDIB = NULL, lpTemp = NULL;
    WORD                wPaletteSize = 0;
    DWORD            	dwBitsSize = 0;

    // Open the file
    if ((hFile = CreateFileA(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        return NULL;
    }
    // Read the header
    if ((!ReadFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwBytes, NULL)) || (dwBytes != sizeof(BITMAPFILEHEADER)))
    {
        CloseHandle(hFile);
        return NULL;
    }
    // Does it look like a BMP file?
    if ((bfh.bfType != 0x4d42) || (bfh.bfReserved1 != 0) || (bfh.bfReserved2 != 0))
    {
        CloseHandle(hFile);
        return NULL;
    }
    // Allocate some memory
    if ((lpDIB = (LPBYTE)malloc(sizeof(BITMAPINFO))) == NULL)
    {
        CloseHandle(hFile);
        return NULL;
    }
    // Read in the BITMAPINFOHEADER
    if ((!ReadFile(hFile, lpDIB, sizeof(BITMAPINFOHEADER), &dwBytes, NULL)) || (dwBytes != sizeof(BITMAPINFOHEADER)))
    {
        CloseHandle(hFile);
        free(lpDIB);
        return NULL;
    }
    if (((LPBITMAPINFOHEADER)lpDIB)->biSize != sizeof(BITMAPINFOHEADER))
    {
        CloseHandle(hFile);
        free(lpDIB);
        return NULL;
    }
    // How big are the elements?
    wPaletteSize = PaletteSize((LPSTR)lpDIB);
    dwBitsSize = ((LPBITMAPINFOHEADER)lpDIB)->biHeight * BytesPerLine((LPBITMAPINFOHEADER)lpDIB);
    // realloc to account for the total size of the DIB
    if ((lpTemp = (LPBYTE)realloc(lpDIB, sizeof(BITMAPINFOHEADER) + wPaletteSize + dwBitsSize)) == NULL)
    {
        CloseHandle(hFile);
        free(lpDIB);
        return NULL;
    }
    lpDIB = lpTemp;
    // If there is a color table, read it
    if (wPaletteSize != 0)
    {
        if ((!ReadFile(hFile, ((LPBITMAPINFO)lpDIB)->bmiColors, wPaletteSize, &dwBytes, NULL)) || (dwBytes != wPaletteSize))
        {
            CloseHandle(hFile);
            free(lpDIB);
            return NULL;
        }
    }
    // Seek to the bits
    // checking against 0 in case some bogus app didn't set this element
    if (bfh.bfOffBits != 0)
    {
        if (SetFilePointer(hFile, bfh.bfOffBits, NULL, FILE_BEGIN) == 0xffffffff)
        {
            CloseHandle(hFile);
            free(lpDIB);
            return NULL;
        }
    }
    // Read the image bits
    if ((!ReadFile(hFile, FindDIBBits((LPSTR)lpDIB), dwBitsSize, &dwBytes, NULL)) || (dwBytes != dwBitsSize))
    {
        CloseHandle(hFile);
        free(lpDIB);
        return NULL;
    }
    // clean up
    CloseHandle(hFile);
    return lpDIB;
}

BOOL MyDib::WriteBMPFile(LPCSTR szFileName, LPBYTE lpDIB)
{
    HANDLE            	hFile;
    BITMAPFILEHEADER    bfh;
    DWORD            	dwBytes, dwBytesToWrite;
    LPBITMAPINFOHEADER	lpbmih;

    // Open the file
    if ((hFile = CreateFileA(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }
    bfh.bfType = 0x4d42;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + PaletteSize((LPSTR)lpDIB);
    bfh.bfSize = (bfh.bfOffBits + ((LPBITMAPINFOHEADER)lpDIB)->biHeight * BytesPerLine((LPBITMAPINFOHEADER)lpDIB)) / 4;
    // Write the header
    if ((!WriteFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwBytes, NULL)) || (dwBytes != sizeof(BITMAPFILEHEADER)))
    {
        CloseHandle(hFile);
        return FALSE;
    }
    lpbmih = (LPBITMAPINFOHEADER)lpDIB;
    //    lpbmih->biHeight /= 2;
    dwBytesToWrite = bfh.bfOffBits + (lpbmih->biHeight * BytesPerLine(lpbmih));
    if ((!WriteFile(hFile, lpDIB, dwBytesToWrite, &dwBytes, NULL)) || (dwBytes != dwBytesToWrite))
    {
        CloseHandle(hFile);
        return FALSE;
    }
    lpbmih->biHeight *= 2;
    CloseHandle(hFile);
    return TRUE;
}





MyDib* pDib;


MyIcon::MyIcon()
{

}

MyIcon::~MyIcon()
{

}


HICON MyIcon::MakeIconFromResource(LPICONIMAGE lpIcon)
{
    HICON        	hIcon = NULL;

    // Sanity Check
    if (lpIcon == NULL)
        return NULL;
    if (lpIcon->lpBits == NULL)
        return NULL;
    // Let the OS do the real work :)
    hIcon = CreateIconFromResourceEx(lpIcon->lpBits, lpIcon->dwNumBytes, TRUE, 0x00030000,
        (*(LPBITMAPINFOHEADER)(lpIcon->lpBits)).biWidth, (*(LPBITMAPINFOHEADER)(lpIcon->lpBits)).biHeight / 2, 0);

    // It failed, odds are good we're on NT so try the non-Ex way
    if (hIcon == NULL)
    {
        // We would break on NT if we try with a 16bpp image
        if (lpIcon->lpbi->bmiHeader.biBitCount != 16)
        {
            hIcon = CreateIconFromResource(lpIcon->lpBits, lpIcon->dwNumBytes, TRUE, 0x00030000);
        }
    }
    return hIcon;
}
/* End MakeIconFromResource() **********************************************/

/****************************************************************************
*
*     FUNCTION: ReadIconFromICOFile
*
*     PURPOSE:  Reads an Icon Resource from an ICO file
*
*     PARAMS:   LPCSTR szFileName - Name of the ICO file
*
*     RETURNS:  LPICONRESOURCE - pointer to the resource, NULL for failure
*
*
\****************************************************************************/
LPICONRESOURCE MyIcon::ReadIconFromICOFile(LPCSTR szFileName)
{
    LPICONRESOURCE    	lpIR = NULL, lpNew = NULL;
    HANDLE            	hFile = NULL;
    LPRESOURCEPOSINFO	lpRPI = NULL;
    UINT                i;
    DWORD            	dwBytesRead;
    LPICONDIRENTRY    	lpIDE = NULL;


    // Open the file
    if ((hFile = CreateFileA(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        //MessageBox(AfxGetMainWnd()->m_hWnd, "ͼ���ļ���ʱ����!", szFileName, MB_OK);
        return NULL;
    }
    // Allocate memory for the resource structure
    if ((lpIR = (LPICONRESOURCE)malloc(sizeof(ICONRESOURCE))) == NULL)
    {
        //MessageBox(AfxGetMainWnd()->m_hWnd, "ͼ������ڴ�ʱ����!", szFileName, MB_OK);
        CloseHandle(hFile);
        return NULL;
    }
    // Read in the header
    if ((lpIR->nNumImages = ReadICOHeader(hFile)) == (UINT)-1)
    {
        //MessageBox(AfxGetMainWnd()->m_hWnd, "��ͼ���ļ�ͷʱ����!", szFileName, MB_OK);
        CloseHandle(hFile);
        free(lpIR);
        return NULL;
    }
    // Adjust the size of the struct to account for the images
    if ((lpNew = (LPICONRESOURCE)realloc(lpIR, sizeof(ICONRESOURCE) + ((lpIR->nNumImages - 1) * sizeof(ICONIMAGE)))) == NULL)
    {
        //MessageBox(AfxGetMainWnd()->m_hWnd, "ͼ���ڴ����·������!", szFileName, MB_OK);
        CloseHandle(hFile);
        free(lpIR);
        return NULL;
    }
    lpIR = lpNew;
    // Store the original name
    lstrcpyA(lpIR->szOriginalICOFileName, szFileName);
    lstrcpyA(lpIR->szOriginalDLLFileName, "");
    // Allocate enough memory for the icon directory entries
    if ((lpIDE = (LPICONDIRENTRY)malloc(lpIR->nNumImages * sizeof(ICONDIRENTRY))) == NULL)
    {
        //MessageBox(AfxGetMainWnd()->m_hWnd, "ͼ���ļ��ڴ����·������!", szFileName, MB_OK);
        CloseHandle(hFile);
        free(lpIR);
        return NULL;
    }
    // Read in the icon directory entries
    if (!ReadFile(hFile, lpIDE, lpIR->nNumImages * sizeof(ICONDIRENTRY), &dwBytesRead, NULL))
    {
        //MessageBox(AfxGetMainWnd()->m_hWnd, "��ͼ���ļ�ʱ����!", szFileName, MB_OK);
        CloseHandle(hFile);
        free(lpIR);
        return NULL;
    }
    if (dwBytesRead != lpIR->nNumImages * sizeof(ICONDIRENTRY))
    {
        //MessageBox(AfxGetMainWnd()->m_hWnd, "��ͼ���ļ�ʱ����!", szFileName, MB_OK);
        CloseHandle(hFile);
        free(lpIR);
        return NULL;
    }
    // Loop through and read in each image
    for (i = 0; i < lpIR->nNumImages; i++)
    {
        // Allocate memory for the resource
        if ((lpIR->IconImages[i].lpBits = (LPBYTE)malloc(lpIDE[i].dwBytesInRes)) == NULL)
        {
            //MessageBox(AfxGetMainWnd()->m_hWnd, "ͼ���ڴ����·������!", szFileName, MB_OK);
            CloseHandle(hFile);
            free(lpIR);
            free(lpIDE);
            return NULL;
        }
        lpIR->IconImages[i].dwNumBytes = lpIDE[i].dwBytesInRes;
        // Seek to beginning of this image
        if (SetFilePointer(hFile, lpIDE[i].dwImageOffset, NULL, FILE_BEGIN) == 0xFFFFFFFF)
        {
            //MessageBox(AfxGetMainWnd()->m_hWnd, "ͼ�����ݶ�λʱ����!", szFileName, MB_OK);
            CloseHandle(hFile);
            free(lpIR);
            free(lpIDE);
            return NULL;
        }
        // Read it in
        if (!ReadFile(hFile, lpIR->IconImages[i].lpBits, lpIDE[i].dwBytesInRes, &dwBytesRead, NULL))
        {
            //MessageBox(AfxGetMainWnd()->m_hWnd, "��ͼ�����ݳ���!", szFileName, MB_OK);
            CloseHandle(hFile);
            free(lpIR);
            free(lpIDE);
            return NULL;
        }
        if (dwBytesRead != lpIDE[i].dwBytesInRes)
        {
            //MessageBox(AfxGetMainWnd()->m_hWnd, "��ͼ�����ݳ���!", szFileName, MB_OK);
            CloseHandle(hFile);
            free(lpIDE);
            free(lpIR);
            return NULL;
        }
        // Set the internal pointers appropriately
        if (!AdjustIconImagePointers(&(lpIR->IconImages[i])))
        {
            //MessageBox(AfxGetMainWnd()->m_hWnd, "ͼ���ڲ���ʽת������!", szFileName, MB_OK);
            CloseHandle(hFile);
            free(lpIDE);
            free(lpIR);
            return NULL;
        }
    }
    // Clean up	
    free(lpIDE);
    free(lpRPI);
    CloseHandle(hFile);
    return lpIR;
}
/* End ReadIconFromICOFile() **********************************************/

/****************************************************************************
*
*     FUNCTION: AdjustIconImagePointers
*
*     PURPOSE:  Adjusts internal pointers in icon resource struct
*
*     PARAMS:   LPICONIMAGE lpImage - the resource to handle
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
*
\****************************************************************************/
BOOL MyIcon::AdjustIconImagePointers(LPICONIMAGE lpImage)
{
    // Sanity check
    if (lpImage == NULL)
        return FALSE;
    // BITMAPINFO is at beginning of bits
    lpImage->lpbi = (LPBITMAPINFO)lpImage->lpBits;
    // Width - simple enough
    lpImage->Width = lpImage->lpbi->bmiHeader.biWidth;
    // Icons are stored in funky format where height is doubled - account for it
    lpImage->Height = (lpImage->lpbi->bmiHeader.biHeight) / 2;
    // How many colors?
    lpImage->Colors = lpImage->lpbi->bmiHeader.biPlanes * lpImage->lpbi->bmiHeader.biBitCount;
    // XOR bits follow the header and color table
    lpImage->lpXOR = (LPBYTE)pDib->FindDIBBits((LPSTR)lpImage->lpbi);
    // AND bits follow the XOR bits
    lpImage->lpAND = lpImage->lpXOR + (lpImage->Height * pDib->BytesPerLine((LPBITMAPINFOHEADER)(lpImage->lpbi)));
    return TRUE;
}
/* End AdjustIconImagePointers() *******************************************/

/****************************************************************************
*
*     FUNCTION: ReadICOHeader
*
*     PURPOSE:  Reads the header from an ICO file
*
*     PARAMS:   HANDLE hFile - handle to the file
*
*     RETURNS:  UINT - Number of images in file, -1 for failure
*
*
\****************************************************************************/
UINT MyIcon::ReadICOHeader(HANDLE hFile)
{
    WORD    Input;
    DWORD	dwBytesRead;

    // Read the 'reserved' WORD
    if (!ReadFile(hFile, &Input, sizeof(WORD), &dwBytesRead, NULL))
        return (UINT)-1;
    // Did we get a WORD?
    if (dwBytesRead != sizeof(WORD))
        return (UINT)-1;
    // Was it 'reserved' ?   (ie 0)
    if (Input != 0)
        return (UINT)-1;
    // Read the type WORD
    if (!ReadFile(hFile, &Input, sizeof(WORD), &dwBytesRead, NULL))
        return (UINT)-1;
    // Did we get a WORD?
    if (dwBytesRead != sizeof(WORD))
        return (UINT)-1;
    // Was it type 1?
    if (Input != 1)
        return (UINT)-1;
    // Get the count of images
    if (!ReadFile(hFile, &Input, sizeof(WORD), &dwBytesRead, NULL))
        return (UINT)-1;
    // Did we get a WORD?
    if (dwBytesRead != sizeof(WORD))
        return (UINT)-1;
    // Return the count
    return Input;
}
/* End ReadICOHeader() ****************************************************/

/****************************************************************************
*
*     FUNCTION: GetIconFromInstance
*
*     PURPOSE:  Callback for enumerating resources in a DLL/EXE
*
*     PARAMS:   HINSTANCE hInstance - Instance handle for this module
*               LPSTR    nIndex    - Resource index
*
*     RETURNS:  HICON - Handle to the icon, NULL for failure
*
*
\****************************************************************************/

/* End GetIconFromInstance() ***********************************************/

/****************************************************************************
*
*     FUNCTION: ReadIconFromEXEFile
*
*     PURPOSE:  Load an Icon Resource from a DLL/EXE file
*
*     PARAMS:   LPCSTR szFileName - name of DLL/EXE file
*               LPCSTR lpID - Index of DLL/EXE file
*
*     RETURNS:  LPICONRESOURCE - pointer to icon resource
*
*
\****************************************************************************/
LPICONRESOURCE MyIcon::ReadIconFromEXEFile(LPCSTR szFileName, LPCSTR lpID)
{
    LPICONRESOURCE    	lpIR = NULL, lpNew = NULL;
    HINSTANCE        	hLibrary;
    EXEDLLICONINFO    	EDII;

    // Load the DLL/EXE - NOTE: must be a 32bit EXE/DLL for this to work
    if ((hLibrary = LoadLibraryExA(szFileName, NULL, LOAD_LIBRARY_AS_DATAFILE)) == NULL)
    {
        // Failed to load - abort
        //MessageBox(AfxGetMainWnd()->m_hWnd, "װ���ļ�ʱ���� - ��ѡ��һ��WIN32��DLL��EXE�ļ�!", szFileName, MB_OK);
        return NULL;
    }
    // Store the info
    EDII.szFileName = szFileName;
    EDII.hInstance = hLibrary;
    // Ask the user, "Which Icon?"
    if (lpID != NULL)
    {
        HRSRC        	hRsrc = NULL;
        HGLOBAL        	hGlobal = NULL;
        LPMEMICONDIR    lpIcon = NULL;
        UINT            i;

        // Find the group icon resource
        if ((hRsrc = FindResourceA(hLibrary, lpID, MAKEINTRESOURCEA((ULONG_PTR)(RT_ICON)+DIFFERENCE))) == NULL)
        {
            FreeLibrary(hLibrary);
            return NULL;
        }
        if ((hGlobal = LoadResource(hLibrary, hRsrc)) == NULL)
        {
            FreeLibrary(hLibrary);
            return NULL;
        }
        if ((lpIcon = (LPMEMICONDIR)LockResource(hGlobal)) == NULL)
        {
            FreeLibrary(hLibrary);
            return NULL;
        }
        // Allocate enough memory for the images
        if ((lpIR = (LPICONRESOURCE)malloc(sizeof(ICONRESOURCE) + ((lpIcon->idCount - 1) * sizeof(ICONIMAGE)))) == NULL)
        {
            //MessageBox(AfxGetMainWnd()->m_hWnd, "�ڴ�������!", szFileName, MB_OK);
            FreeLibrary(hLibrary);
            return NULL;
        }
        // Fill in local struct members
        lpIR->nNumImages = lpIcon->idCount;
        lstrcpyA(lpIR->szOriginalDLLFileName, szFileName);
        lstrcpyA(lpIR->szOriginalICOFileName, "");
        // Loop through the images
        for (i = 0; i < lpIR->nNumImages; i++)
        {
            // Get the individual image
            if ((hRsrc = FindResource(hLibrary, MAKEINTRESOURCE(lpIcon->idEntries[i].nID), RT_ICON)) == NULL)
            {
                free(lpIR);
                FreeLibrary(hLibrary);
                return NULL;
            }
            if ((hGlobal = LoadResource(hLibrary, hRsrc)) == NULL)
            {
                free(lpIR);
                FreeLibrary(hLibrary);
                return NULL;
            }
            // Store a copy of the resource locally
            lpIR->IconImages[i].dwNumBytes = SizeofResource(hLibrary, hRsrc);
            lpIR->IconImages[i].lpBits = (LPBYTE)malloc(lpIR->IconImages[i].dwNumBytes);
            memcpy(lpIR->IconImages[i].lpBits, LockResource(hGlobal), lpIR->IconImages[i].dwNumBytes);
            // Adjust internal pointers
            if (!AdjustIconImagePointers(&(lpIR->IconImages[i])))
            {
                //MessageBox(AfxGetMainWnd()->m_hWnd, "ת����ͼ���ڲ���ʽʱ����!", szFileName, MB_OK);
                free(lpIR);
                FreeLibrary(hLibrary);
                return NULL;
            }
        }
    }
    FreeLibrary(hLibrary);
    return lpIR;
}
/* End ReadIconFromEXEFile() ************************************************/

/****************************************************************************
*
*     FUNCTION: WriteICOHeader
*
*     PURPOSE:  Writes the header to an ICO file
*
*     PARAMS:   HANDLE hFile       - handle to the file
*               UINT   nNumEntries - Number of images in file
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
*
\****************************************************************************/
BOOL MyIcon::WriteICOHeader(HANDLE hFile, UINT nNumEntries)
{
    WORD    Output;
    DWORD	dwBytesWritten;

    // Write 'reserved' WORD
    Output = 0;
    if (!WriteFile(hFile, &Output, sizeof(WORD), &dwBytesWritten, NULL))
        return FALSE;
    // Did we write a WORD?
    if (dwBytesWritten != sizeof(WORD))
        return FALSE;
    // Write 'type' WORD (1)
    Output = 1;
    if (!WriteFile(hFile, &Output, sizeof(WORD), &dwBytesWritten, NULL))
        return FALSE;
    // Did we write a WORD?
    if (dwBytesWritten != sizeof(WORD))
        return FALSE;
    // Write Number of Entries
    Output = (WORD)nNumEntries;
    if (!WriteFile(hFile, &Output, sizeof(WORD), &dwBytesWritten, NULL))
        return FALSE;
    // Did we write a WORD?
    if (dwBytesWritten != sizeof(WORD))
        return FALSE;
    return TRUE;
}
/* End WriteICOHeader() ****************************************************/

/****************************************************************************
*
*     FUNCTION: CalculateImageOffset
*
*     PURPOSE:  Calculates the file offset for an icon image
*
*     PARAMS:   LPICONRESOURCE lpIR   - pointer to icon resource
*               UINT           nIndex - which image?
*
*     RETURNS:  DWORD - the file offset for that image
*
*
\****************************************************************************/
DWORD MyIcon::CalculateImageOffset(LPICONRESOURCE lpIR, UINT nIndex)
{
    DWORD	dwSize;
    UINT    i;

    // Calculate the ICO header size
    dwSize = 3 * sizeof(WORD);
    // Add the ICONDIRENTRY's
    dwSize += lpIR->nNumImages * sizeof(ICONDIRENTRY);
    // Add the sizes of the previous images
    for (i = 0; i < nIndex; i++)
        dwSize += lpIR->IconImages[i].dwNumBytes;
    // we're there - return the number
    return dwSize;
}
/* End CalculateImageOffset() ***********************************************/

/****************************************************************************
*
*     FUNCTION: WriteIconToICOFile
*
*     PURPOSE:  Writes the icon resource data to an ICO file
*
*     PARAMS:   LPICONRESOURCE lpIR       - pointer to icon resource
*               LPCSTR        szFileName - name for the ICO file
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
*
\****************************************************************************/
BOOL MyIcon::WriteIconToICOFile(LPICONRESOURCE lpIR, LPCSTR szFileName)
{
    HANDLE    	hFile;
    UINT        i;
    DWORD    	dwBytesWritten;

    // open the file
    if ((hFile = CreateFileA(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        //MessageBox(AfxGetMainWnd()->m_hWnd, "�ļ�����ʱ����!", szFileName, MB_OK);
        return FALSE;
    }
    // Write the header
    if (!WriteICOHeader(hFile, lpIR->nNumImages))
    {
        //MessageBox(AfxGetMainWnd()->m_hWnd, "дͼ���ļ�ͷʱ����!", szFileName, MB_OK);
        CloseHandle(hFile);
        return FALSE;
    }
    // Write the ICONDIRENTRY's
    for (i = 0; i < lpIR->nNumImages; i++)
    {
        ICONDIRENTRY    ide;

        // Convert internal format to ICONDIRENTRY
        ide.bWidth = lpIR->IconImages[i].Width;
        ide.bHeight = lpIR->IconImages[i].Height;
        ide.bReserved = 0;
        ide.wPlanes = lpIR->IconImages[i].lpbi->bmiHeader.biPlanes;
        ide.wBitCount = lpIR->IconImages[i].lpbi->bmiHeader.biBitCount;
        if ((ide.wPlanes * ide.wBitCount) >= 8)
            ide.bColorCount = 0;
        else
            ide.bColorCount = 1 << (ide.wPlanes * ide.wBitCount);
        ide.dwBytesInRes = lpIR->IconImages[i].dwNumBytes;
        ide.dwImageOffset = CalculateImageOffset(lpIR, i);
        // Write the ICONDIRENTRY out to disk
        if (!WriteFile(hFile, &ide, sizeof(ICONDIRENTRY), &dwBytesWritten, NULL))
            return FALSE;
        // Did we write a full ICONDIRENTRY ?
        if (dwBytesWritten != sizeof(ICONDIRENTRY))
            return FALSE;
    }
    // Write the image bits for each image
    for (i = 0; i < lpIR->nNumImages; i++)
    {
        DWORD dwTemp = lpIR->IconImages[i].lpbi->bmiHeader.biSizeImage;

        // Set the sizeimage member to zero
        lpIR->IconImages[i].lpbi->bmiHeader.biSizeImage = 0;
        // Write the image bits to file
        if (!WriteFile(hFile, lpIR->IconImages[i].lpBits, lpIR->IconImages[i].dwNumBytes, &dwBytesWritten, NULL))
            return FALSE;
        if (dwBytesWritten != lpIR->IconImages[i].dwNumBytes)
            return FALSE;
        // set it back
        lpIR->IconImages[i].lpbi->bmiHeader.biSizeImage = dwTemp;
    }
    CloseHandle(hFile);
    return FALSE;
}
/* End WriteIconToICOFile() **************************************************/

/****************************************************************************
*
*     FUNCTION: IconImageToClipBoard
*
*     PURPOSE:  Copies an icon image to the clipboard in CF_DIB format
*
*     PARAMS:   LPICONIMAGE lpii - pointer to icon image data
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
*
\****************************************************************************/
BOOL MyIcon::IconImageToClipBoard(LPICONIMAGE lpii)
{
    HANDLE	hGlobal;
    LPSTR	lpBits;

    // Open the clipboard
    if (OpenClipboard(0))
    {
        // empty it
        if (EmptyClipboard())
        {
            if (lpii->dwNumBytes == NULL)
                return false;
            // Make a buffer to send to clipboard
            hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, lpii->dwNumBytes);
            lpBits = (LPSTR)GlobalLock(hGlobal);
            // Copy the bits to the buffer
            memcpy(lpBits, lpii->lpBits, lpii->dwNumBytes);
            // Adjust for funky height*2 thing
            ((LPBITMAPINFOHEADER)lpBits)->biHeight /= 2;
            GlobalUnlock(hGlobal);
            // Send it to the clipboard
            SetClipboardData(CF_DIB, hGlobal);
            CloseClipboard();
            return TRUE;
        }
    }
    return FALSE;
}

BOOL MyIcon::DIBToIconImage(LPICONIMAGE lpii, LPBYTE lpDIB, BOOL bStretch)
{
    LPBYTE    	lpNewDIB;

    // Sanity check
    if (lpDIB == NULL)
        return FALSE;

    // Let the DIB engine convert color depths if need be
    lpNewDIB = pDib->ConvertDIBFormat((LPBITMAPINFO)lpDIB, lpii->Width, lpii->Height, lpii->Colors, bStretch);

    // Now we have a cool new DIB of the proper size/color depth
    // Lets poke it into our data structures and be done with it

    // How big is it?
    lpii->dwNumBytes = sizeof(BITMAPINFOHEADER)                    	// Header
        + pDib->PaletteSize((LPSTR)lpNewDIB)                    // Palette
        + lpii->Height * pDib->BytesPerLine((LPBITMAPINFOHEADER)lpNewDIB)	// XOR mask
        + lpii->Height * WIDTHBYTES(lpii->Width);        	// AND mask

// If there was already an image here, free it
    if (lpii->lpBits != NULL)
        free(lpii->lpBits);
    // Allocate enough room for the new image
    if ((lpii->lpBits = (LPBYTE)malloc(lpii->dwNumBytes)) == NULL)
    {
        free(lpii);
        return FALSE;
    }
    // Copy the bits
    memcpy(lpii->lpBits, lpNewDIB, sizeof(BITMAPINFOHEADER) + pDib->PaletteSize((LPSTR)lpNewDIB));
    // Adjust internal pointers/variables for new image
    lpii->lpbi = (LPBITMAPINFO)(lpii->lpBits);
    lpii->lpbi->bmiHeader.biHeight *= 2;
    lpii->lpXOR = (LPBYTE)pDib->FindDIBBits((LPSTR)(lpii->lpBits));
    memcpy(lpii->lpXOR, pDib->FindDIBBits((LPSTR)lpNewDIB), lpii->Height * pDib->BytesPerLine((LPBITMAPINFOHEADER)lpNewDIB));
    lpii->lpAND = lpii->lpXOR + lpii->Height * pDib->BytesPerLine((LPBITMAPINFOHEADER)lpNewDIB);
    memset(lpii->lpAND, 0, lpii->Height * WIDTHBYTES(lpii->Width));
    // Free the source
    free(lpNewDIB);
    return TRUE;
}
/* End DIBToIconImage() ***************************************************/

/****************************************************************************
*
*     FUNCTION: IconImageFromBMPFile
*
*     PURPOSE:  Creates an icon image from a BMP file
*
*     PARAMS:   LPCSTR     szFileName    - Filename for BMP file
*               LPICONIMAGE lpii          - pointer to icon image data
*               BOOL        bStretchToFit - TRUE to stretch, FALSE to take
*                                           the upper left corner of the DIB
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
*
\****************************************************************************/
BOOL MyIcon::IconImageFromBMPFile(LPCSTR szFileName, LPICONIMAGE lpii, BOOL bStretchToFit)
{
    LPBYTE        	lpDIB = NULL;
    BOOL            bRet = FALSE;

    if ((lpDIB = pDib->ReadBMPFile(szFileName)) == NULL)
        return FALSE;
    // Convert it to an icon image
    bRet = DIBToIconImage(lpii, lpDIB, bStretchToFit);
    free(lpDIB);
    return bRet;
}
/* End IconImageFromBMPFile() ********************************************/

/****************************************************************************
*
*     FUNCTION: IconImageToBMPFile
*
*     PURPOSE:  Creates BMP file from an icon image
*
*     PARAMS:   LPCSTR     szFileName    - Filename for BMP file
*               LPICONIMAGE lpii          - pointer to icon image data
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
*
\****************************************************************************/
BOOL MyIcon::IconImageToBMPFile(LPCSTR szFileName, LPICONIMAGE lpii)
{
    return pDib->WriteBMPFile(szFileName, (LPBYTE)lpii->lpbi);
}
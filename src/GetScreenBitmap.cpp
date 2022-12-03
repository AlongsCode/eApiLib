#include<windows.h>

int SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName) //hBitmap Ϊ�ղŵ���Ļλͼ���
{      //lpFileName Ϊλͼ�ļ���
    HDC     hDC;
    //�豸������
    int     iBits;
    //��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���
    WORD    wBitCount;
    //λͼ��ÿ��������ռ�ֽ���
    //�����ɫ���С�� λͼ�������ֽڴ�С ��  λͼ�ļ���С �� д���ļ��ֽ���
    DWORD           dwPaletteSize = 0, dwBmBitsSize, dwDIBSize, dwWritten;
    BITMAP          Bitmap;
    //λͼ���Խṹ
    BITMAPFILEHEADER   bmfHdr;
    //λͼ�ļ�ͷ�ṹ
    BITMAPINFOHEADER   bi;
    //λͼ��Ϣͷ�ṹ 
    LPBITMAPINFOHEADER lpbi;
    //ָ��λͼ��Ϣͷ�ṹ
    HANDLE          fh, hDib, hPal;
    HPALETTE     hOldPal = NULL;
    //�����ļ��������ڴ�������ɫ����

    //����λͼ�ļ�ÿ��������ռ�ֽ���
    hDC = CreateDCW(L"DISPLAY", NULL, NULL, NULL);
    iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
    DeleteDC(hDC);
    if (iBits <= 1)
        wBitCount = 1;
    else if (iBits <= 4)
        wBitCount = 4;
    else if (iBits <= 8)
        wBitCount = 8;
    else if (iBits <= 32)
        wBitCount = 24;
    //�����ɫ���С
    if (wBitCount <= 8)
        dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);

    //����λͼ��Ϣͷ�ṹ
    GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = Bitmap.bmWidth;
    bi.biHeight = Bitmap.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = wBitCount;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;
    //Ϊλͼ���ݷ����ڴ�
    hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;
    // �����ɫ��   
    hPal = GetStockObject(DEFAULT_PALETTE);
    if (hPal)
    {
        hDC = ::GetDC(NULL);
        hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
        RealizePalette(hDC);
    }
    // ��ȡ�õ�ɫ�����µ�����ֵ
    GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, (BITMAPINFO*)lpbi, DIB_RGB_COLORS);
    //�ָ���ɫ��   
    if (hOldPal)
    {
        SelectPalette(hDC, hOldPal, TRUE);
        RealizePalette(hDC);
        ::ReleaseDC(NULL, hDC);
    }
    //����λͼ�ļ�    
    fh = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (fh == INVALID_HANDLE_VALUE)
        return FALSE;
    // ����λͼ�ļ�ͷ
    bmfHdr.bfType = 0x4D42;  // "BM"
    dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
    bmfHdr.bfSize = dwDIBSize;
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
    // д��λͼ�ļ�ͷ
    WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
    // д��λͼ�ļ���������
    WriteFile(fh, (LPSTR)lpbi, dwDIBSize,
        &dwWritten, NULL);
    //���   
    GlobalUnlock(hDib);
    GlobalFree(hDib);
    CloseHandle(fh);
    return TRUE;
}
int  CopyScreenToBitmap(RECT* lprc, int Type, LPSTR lpFileName)
{
    BOOL result=FALSE;

    if (!IsRectEmpty(lprc))
    {
        HDC hdc = CreateDCW(L"DISPLAY", 0, 0, 0);
        HDC  hMemDC = CreateCompatibleDC(hdc);
        int left, right, bottom, top, maxw, maxh;
        left = lprc->left;
        right = lprc->right;
        bottom = lprc->bottom;
        top = lprc->top;
        maxw = GetDeviceCaps(hdc, HORZRES);
        maxh = GetDeviceCaps(hdc, VERTRES);
        if (left < 0) left = 0;
        if (top < 0) top = 0;
        if (right > maxw) right = maxw;
        if (bottom > maxh) bottom = maxh;
        int cx = right - left;
        int cy = bottom - top;
        HBITMAP hMema = CreateCompatibleBitmap(hdc, cx, cy);
        SelectObject(hMemDC, hMema);
        BitBlt(hMemDC, 0, 0, cx, cy, hdc, left, top, SRCCOPY);
        DeleteDC(hdc);
        DeleteDC(hMemDC);
        if (Type)
        {
            if (Type == 1)
            {
                if (OpenClipboard(NULL))
                {
                    EmptyClipboard();
                    SetClipboardData(CF_BITMAP, hMema);
                    result = CloseClipboard();
                }
            }
        }
        else
        {
            result = SaveBitmapToFile(hMema, lpFileName);
        }
        DeleteObject(hMema);
    }

    return result;
}




HBITMAP  CopyScreenToBitmap(RECT* lprc)
{
    HBITMAP result = 0;
    if (!IsRectEmpty(lprc))
    {
        HDC hdc = CreateDCW(L"DISPLAY", 0, 0, 0);;
        HDC hMemDc = CreateCompatibleDC(hdc);
        int left, right, bottom, top;
        left = lprc->left;
        right = lprc->right;
        bottom = lprc->bottom;
        top = lprc->top;

        int  maxw = GetDeviceCaps(hdc, 8);
        int  maxh = GetDeviceCaps(hdc, 10);
        if (left < 0)left = 0;
        if (top < 0) top = 0;
        if (right > maxw) right = maxw;
        if (bottom > maxh) bottom = maxh;
        int cx = right - left;
        int cy = bottom - top;
        HBITMAP hbmp = CreateCompatibleBitmap(hdc, cx, cy);
        SelectObject(hMemDc, hbmp);
        BitBlt(hMemDc, 0, 0, cx, cy, hdc, left, (int)top, 0xCC0020u);
        DeleteDC(hdc);
        DeleteDC(hMemDc);
        result = hbmp;
    }

    return result;
}
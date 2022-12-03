#include<windows.h>

int SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName) //hBitmap 为刚才的屏幕位图句柄
{      //lpFileName 为位图文件名
    HDC     hDC;
    //设备描述表
    int     iBits;
    //当前显示分辨率下每个像素所占字节数
    WORD    wBitCount;
    //位图中每个像素所占字节数
    //定义调色板大小， 位图中像素字节大小 ，  位图文件大小 ， 写入文件字节数
    DWORD           dwPaletteSize = 0, dwBmBitsSize, dwDIBSize, dwWritten;
    BITMAP          Bitmap;
    //位图属性结构
    BITMAPFILEHEADER   bmfHdr;
    //位图文件头结构
    BITMAPINFOHEADER   bi;
    //位图信息头结构 
    LPBITMAPINFOHEADER lpbi;
    //指向位图信息头结构
    HANDLE          fh, hDib, hPal;
    HPALETTE     hOldPal = NULL;
    //定义文件，分配内存句柄，调色板句柄

    //计算位图文件每个像素所占字节数
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
    //计算调色板大小
    if (wBitCount <= 8)
        dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);

    //设置位图信息头结构
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
    //为位图内容分配内存
    hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;
    // 处理调色板   
    hPal = GetStockObject(DEFAULT_PALETTE);
    if (hPal)
    {
        hDC = ::GetDC(NULL);
        hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
        RealizePalette(hDC);
    }
    // 获取该调色板下新的像素值
    GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, (BITMAPINFO*)lpbi, DIB_RGB_COLORS);
    //恢复调色板   
    if (hOldPal)
    {
        SelectPalette(hDC, hOldPal, TRUE);
        RealizePalette(hDC);
        ::ReleaseDC(NULL, hDC);
    }
    //创建位图文件    
    fh = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (fh == INVALID_HANDLE_VALUE)
        return FALSE;
    // 设置位图文件头
    bmfHdr.bfType = 0x4D42;  // "BM"
    dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
    bmfHdr.bfSize = dwDIBSize;
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
    // 写入位图文件头
    WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
    // 写入位图文件其余内容
    WriteFile(fh, (LPSTR)lpbi, dwDIBSize,
        &dwWritten, NULL);
    //清除   
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
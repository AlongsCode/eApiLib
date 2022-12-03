//#define _AFXDLL
#include<string>
#include<afxdlgs.h>
#include<Winspool.h>
#pragma comment(lib,"Winspool.lib")

using namespace std;
//MFC命令，少用
string MyGetDefaultPrinter();
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
char* eapi_CloneTextData(char* ps);
short EPaperSizeToC(int EPaperSize)
{
    short  result;

    switch (EPaperSize + 1)
    {
    case 0:
        result = 256;
        break;
    case 2:
        result = 8;
        break;
    case 4:
        result = 11;
        break;
    case 5:
        result = 12;
        break;
    case 6:
        result = 13;
        break;
    case 7:
        result = 15;
        break;
    case 8:
        result = 93;
        break;
    case 9:
        result = 94;
        break;
    case 10:
        result = 1;
        break;
    case 11:
        result = 5;
        break;
    case 12:
        result = 7;
        break;
    case 13:
        result = 6;
        break;
    case 14:
        result = 3;
        break;
    case 15:
        result = 18;
        break;
    case 16:
        result = 4;
        break;
    case 17:
        result = 14;
        break;
    default:
        result = 9;
        break;
    }
    return result;
}
int  CPaperSizeToE(short CPaperSize)
{
    int result;

    result = CPaperSize;
    if (CPaperSize > 93)
    {
        if (CPaperSize == 94)
        {
            result = 8;
        }
        else if (CPaperSize == 256)
        {
            result = -1;
        }
    }
    else if (CPaperSize == 93)
    {
        result = 7;
    }
    else
    {
        switch (CPaperSize)
        {
        case 8:
            result = 1;
            break;
        case 9:
            result = 2;
            break;
        case 11:
            result = 3;
            break;
        case 12:
            result = 4;
            break;
        case 13:
            result = 5;
            break;
        case 15:
            result = 6;
            break;
        case 1:
            result = 9;
            break;
        case 5:
            result = 10;
            break;
        case 7:
            result = 11;
            break;
        case 6:
            result = 12;
            break;
        case 3:
            result = 13;
            break;
        case 18:
            result = 14;
            break;
        case 4:
            result = 15;
            break;
        case 14:
            result = 16;
            break;
        default:
            return result;
        }
    }
    return result;
}
int  OpenPrintSetupDlg(DEVMODE  ININFO, MYPRINTINFO* OUTINFO, BOOL ONLYSET) {
    CPrintDialog Dlg(ONLYSET);
    HANDLE phPrinter;
    if (OpenPrinter((LPSTR)ININFO.dmDeviceName, &phPrinter, 0) || !phPrinter) {
        LONG DataLenth = DocumentProperties(0, phPrinter, (LPSTR)ININFO.dmDeviceName, 0, 0, 0);
        if (DataLenth > 0)
        {

            PDEVMODE OutData = (PDEVMODE)GlobalAlloc(GMEM_ZEROINIT, DataLenth);

            if (OutData)
            {
                if (DocumentProperties(0, phPrinter, (LPSTR)ININFO.dmDeviceName, OutData, 0, DM_OUT_BUFFER) == IDOK)
                {
                    memcpy(OutData, &ININFO, sizeof(DEVMODE));
                    Dlg.m_pd.hDevMode = OutData;
                    if (Dlg.DoModal() == IDOK)
                    {
                        OutData = Dlg.GetDevMode();
                        OUTINFO->DeviceName = eapi_CloneTextData((LPSTR)OutData->dmDeviceName);
                        OUTINFO->Orientation = OutData->dmOrientation;
                        OUTINFO->PaperSize = CPaperSizeToE(OutData->dmPaperSize);
                        OUTINFO->PaperWidth = OutData->dmPaperWidth;
                        OUTINFO->PaperLength = OutData->dmPaperLength;
                        OUTINFO->Copies = OutData->dmCopies;
                        if (phPrinter) ClosePrinter(phPrinter);
                        GlobalFree(OutData);//内部重新realloc，Print内部自动释放
                        return 1;
                    }
                }
                GlobalFree(OutData);
            }
        }
        ClosePrinter(phPrinter);
    }
    return  2;
}

INT OpenPrintPropertyDlg(DEVMODE  ININFO, MYPRINTINFO* OUTINFO) {

    LONG Ret;
    HANDLE phPrinter;

    phPrinter = 0;

    if (OpenPrinter((LPSTR)ININFO.dmDeviceName, &phPrinter, 0) || !phPrinter) {
        LONG DataLenth = DocumentProperties(0, phPrinter, (LPSTR)ININFO.dmDeviceName, 0, 0, 0);

        if (DataLenth)
        {
            PDEVMODE OutData = (PDEVMODE)GlobalAlloc(GMEM_ZEROINIT, DataLenth);
            if (OutData)
            {
                if (DocumentProperties(0, phPrinter, (LPSTR)ININFO.dmDeviceName, OutData, 0, DM_OUT_BUFFER) == IDOK)
                {
                    if (OutData->dmFields & DMCOLLATE_TRUE)
                    {
                        memcpy(OutData, &ININFO, sizeof(DEVMODE));
                        Ret = DocumentProperties(0, phPrinter, (LPSTR)ININFO.dmDeviceName, OutData, OutData, DM_IN_BUFFER | DM_OUT_BUFFER | DM_IN_PROMPT);
                        if (Ret == IDOK)//确定
                        {
                            if (DocumentProperties(0, phPrinter, (LPSTR)ININFO.dmDeviceName, OutData, OutData, DM_IN_BUFFER | DM_OUT_BUFFER) == IDOK)
                            {
                                SendMessageTimeout(HWND_BROADCAST, WM_DEVMODECHANGE, 0, (LPARAM)ININFO.dmDeviceName, SMTO_NORMAL, 1000, 0);
                                if (OUTINFO)
                                {
                                    // 输出打印信息->名称 = OutData->dmDeviceName;
                                    OUTINFO->Orientation = OutData->dmOrientation;
                                    OUTINFO->PaperSize = OutData->dmPaperSize;
                                    OUTINFO->PaperLength = OutData->dmPaperLength;
                                    OUTINFO->PaperWidth = OutData->dmPaperWidth;
                                    OUTINFO->Copies = OutData->dmCopies;
                                }
                            }
                            ClosePrinter(phPrinter);
                            GlobalFree(OutData);
                            return 1;

                        }
                    }

                }
                GlobalFree(OutData);
            }
        }
        ClosePrinter(phPrinter);

    }
    return 2;

}


int OpenPrintDlg(INT TYPE, DEVMODE  ININFO, MYPRINTINFO* OUTINFO, BOOL INDEXCODE) {
    int result = 0;
    if (TYPE <= 1)
    {
        //wcout << 输入打印信息.dmDeviceName;
        result = OpenPrintSetupDlg(ININFO, OUTINFO, INDEXCODE);
    }
    else if (TYPE == 2)
    {

        result = OpenPrintPropertyDlg(ININFO, OUTINFO);
    }
    else
    {

        result = 2;
    }
    return result;
}
INT OpenPrintSetDlg(INT Type, MYPRINTINFO* pPrintInfo) {

    int Ret = 0;
    if (Type > 2 || Type < 0)
    {
        Type = 0;
    }
    DEVMODE PrintData = { 0 };
    if (pPrintInfo->DeviceName && strlen(pPrintInfo->DeviceName)>0)
    {
        strcpy((LPSTR)PrintData.dmDeviceName, pPrintInfo->DeviceName);
    }
    else
    {
        strcpy((LPSTR)PrintData.dmDeviceName, MyGetDefaultPrinter().c_str());
    }

    if (pPrintInfo)
    {

        PrintData.dmOrientation = pPrintInfo->Orientation == DMORIENT_LANDSCAPE ? DMORIENT_LANDSCAPE : DMORIENT_PORTRAIT;
        PrintData.dmPaperSize = EPaperSizeToC(pPrintInfo->PaperSize);
        PrintData.dmPaperWidth = (short)pPrintInfo->PaperWidth;
        PrintData.dmPaperLength = (short)pPrintInfo->PaperLength;
        PrintData.dmCopies = (short)pPrintInfo->Copies;
    }
    MYPRINTINFO pBuffer;
    if (!Type)
    {
        Ret = OpenPrintDlg(0, PrintData, &pBuffer, 1);
    }
    if (Type == 1)
    {
        Ret = OpenPrintDlg(1, PrintData, &pBuffer, 0);

    }
    if (Type == 2)
    {
        Ret = OpenPrintDlg(2, PrintData, &pBuffer, 1);

    }
    if (pPrintInfo != NULL && Ret == 1)
    {
        pPrintInfo->DeviceName = pBuffer.DeviceName;
        memcpy((BYTE*)pPrintInfo + sizeof(string), ((BYTE*)&pBuffer + sizeof(string)), sizeof(MYPRINTINFO));
    }
    return Ret;
}


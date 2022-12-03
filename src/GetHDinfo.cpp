#include <windows.h>
#include"string"
#include"eapi.h"
#include"syse.h"
using namespace std;

#define IDE_ATA_IDENTIFY  0xEC;			//读取ATA设备的命令
inline string Trim(string str)			
{
	string::size_type pos = str.find_last_not_of(' ');
	if (pos != wstring::npos)
	{
		str.erase(pos + 1);
		pos = str.find_first_not_of(L' ');
		if (pos != string::npos)
			str.erase(0, pos);
	}
	else
		str.erase(str.begin(), str.end());

	return str;
}
inline BOOL DoIdentify(HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP, PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum, PDWORD lpcbBytesReturned)
{
	// Set up data structures for IDENTIFY command.
	pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;
	pSCIP->irDriveRegs.bFeaturesReg = 0;
	pSCIP->irDriveRegs.bSectorCountReg = 1;
	pSCIP->irDriveRegs.bSectorNumberReg = 1;
	pSCIP->irDriveRegs.bCylLowReg = 0;
	pSCIP->irDriveRegs.bCylHighReg = 0;

	//Compute the drive number.(主盘和从盘所对应的值是不一样的)
	pSCIP->irDriveRegs.bDriveHeadReg = (bDriveNum & 1) ? 0xB0 : 0xA0;

	// The command can either be IDE identify or ATAPI identify.
	pSCIP->irDriveRegs.bCommandReg = bIDCmd;
	pSCIP->bDriveNumber = bDriveNum;
	pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;

	return DeviceIoControl(hPhysicalDriveIOCTL, SMART_RCV_DRIVE_DATA, (LPVOID)pSCIP, sizeof(SENDCMDINPARAMS) - 1,
		(LPVOID)pSCOP, sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1, lpcbBytesReturned, NULL);
}
inline  string ChangeByteOrder(unsigned char* first, size_t len)
{

	char* ret = new char[len + 1];
	memset(ret, 0, len + 1);
	for (size_t i = 0; i < len - 1; i += 2)
	{
		ret[i] = first[i + 1];
		ret[i + 1] = first[i];
	}
	string result = string(string(ret, len).c_str());//截断结束符
	delete[] ret;
	return Trim(result);
}
bool GetHDInfo(HDInfo* pHDInfo, int HDIndex) {
	BYTE IdOutCmd[sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
	HANDLE hPhysicalDriveIOCTL;
	char DriveName[32];
	bool ret = false;
	sprintf(DriveName, "\\\\.\\PhysicalDrive%d", HDIndex);
	hPhysicalDriveIOCTL = CreateFileA(DriveName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	memset(pHDInfo, 0, sizeof(HDInfo));
	if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
	{
		DWORD cbBytesReturned = 0;
		GETVERSIONINPARAMS VersionParams;
		ZeroMemory(&VersionParams, sizeof(GETVERSIONINPARAMS));
		if (DeviceIoControl(hPhysicalDriveIOCTL, SMART_GET_VERSION, NULL, 0, &VersionParams, sizeof(VersionParams), &cbBytesReturned, NULL))
		{
			if (VersionParams.bIDEDeviceMap > 0)
			{
				BYTE bIDCmd = 0;
				SENDCMDINPARAMS InParams;
				bIDCmd = IDE_ATA_IDENTIFY;
				ZeroMemory(&InParams, sizeof(SENDCMDINPARAMS));
				ZeroMemory(IdOutCmd, sizeof(IdOutCmd));
				if (DoIdentify(hPhysicalDriveIOCTL, (PSENDCMDINPARAMS)&InParams, (PSENDCMDOUTPARAMS)IdOutCmd, (BYTE)bIDCmd, (BYTE)HDIndex, &cbBytesReturned))
				{
					
					unsigned char* pIDSector = ((SENDCMDOUTPARAMS*)IdOutCmd)->bBuffer;												// 对应结构IDSECTOR，见头文件
					pHDInfo->model = eapi_CloneTextData(const_cast<char*>(ChangeByteOrder(pIDSector + 54, 0x28u).c_str()));
					pHDInfo->Version = eapi_CloneTextData(const_cast<char*>(ChangeByteOrder((pIDSector + 46), 8).c_str()));
					pHDInfo->serial = eapi_CloneTextData(const_cast<char*>(ChangeByteOrder((pIDSector + 20), 0x14u).c_str()));
					pHDInfo->capacity = (*(DWORD*)(pIDSector + 120) >> 11);//容量
					pHDInfo->heads = *(WORD*)(pIDSector + 6);//磁头数
					pHDInfo->sectorspertrack = *(WORD*)(pIDSector + 12);//扇区数
					pHDInfo->cachesize = (*(WORD*)(pIDSector + 42) << 9) / 1024 / 1024;//缓存大小
					pHDInfo->cylinders = *(DWORD*)(pIDSector + 120) / (unsigned int)*(WORD*)(pIDSector + 6) / *(WORD*)(pIDSector + 12);//柱面数
					ret = true;
				}

			}
		}
		CloseHandle(hPhysicalDriveIOCTL);
	}
	return ret;
}
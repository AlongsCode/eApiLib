#include <Shlwapi.h>
#include <windows.h>
#include <string>
#include"Pdh.h"
using namespace std;
#pragma comment(lib, "Pdh.lib")
#pragma comment(lib, "Shlwapi.lib")


double GetCpuUsges() {
	PDH_HQUERY		m_CpuQuery;
	PDH_HCOUNTER	m_CpuTotal;
	m_CpuQuery = NULL;
	m_CpuTotal = NULL;
	PDH_STATUS stateinit;
	stateinit = PdhOpenQueryW(NULL, NULL, &m_CpuQuery);
	if ((DWORD)(LOWORD(GetVersion())) >= 10) {
		stateinit = PdhAddCounterW(m_CpuQuery, L"\\Processor Information(_Total)\\% Processor Utility", NULL, &m_CpuTotal);
	}
	else {
		stateinit = PdhAddCounterW(m_CpuQuery, L"\\Processor Information(_Total)\\% Processor Time", NULL, &m_CpuTotal);
	}
	stateinit = PdhCollectQueryData(m_CpuQuery);
	Sleep(100);
	PDH_FMT_COUNTERVALUE counterVal;
	PdhCollectQueryData(m_CpuQuery);
	PDH_STATUS state = PdhGetFormattedCounterValue(m_CpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
	double CpuMemDisk = counterVal.doubleValue;//PDH_INVALID_ARGUMENT PDH_INVALID_DATA 
	if (m_CpuTotal) {
		PdhRemoveCounter(m_CpuTotal);
		m_CpuTotal = NULL;
	}
	if (m_CpuQuery) {
		PdhCloseQuery(m_CpuQuery);
		m_CpuQuery = NULL;
	}
	if (CpuMemDisk <= 0 || CpuMemDisk > 100)
	{
		CpuMemDisk = -1;
	}
	return CpuMemDisk;
}


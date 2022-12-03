#include"windows.h"
#include"string"
#include"intrin.h"
#include"eapi.h"
#include"myhelp.h"
#include"syse.h"
#include <iphlpapi.h>
#include <Wbemidl.h>
#include <comdef.h>
#pragma comment(lib, "wbemuuid.lib") 
using namespace std;


inline static string GetCPUcomp()
{
    char ComName[13];
    int cpuid[4] = {};

    int i, k;

    memset((void*)ComName, 0, sizeof(ComName));
    __cpuid(cpuid, 0);

    for (i = 0; cpuid[1] > 0; i++)
    {
        k = cpuid[1];
        k = (k >> 8);
        k = (k << 8);
        ComName[i] = cpuid[1] - k;
        cpuid[1] = (cpuid[1] >> 8);
    }
    for (; cpuid[3] > 0; i++)
    {
        k = cpuid[3];
        k = (k >> 8);
        k = (k << 8);
        ComName[i] = cpuid[3] - k;
        cpuid[3] = (cpuid[3] >> 8);
    }
    for (; cpuid[2] > 0; i++)
    {
        k = cpuid[2];
        k = (k >> 8);
        k = (k << 8);
        ComName[i] = cpuid[2] - k;
        cpuid[2] = (cpuid[2] >> 8);
    }
    ComName[12] = '\0';
    string str = ComName;
    string wstr;
    if (str == "GenuineIntel") {
        wstr = "Intel Corporation.";
    }
    else if (str == "AuthenticAMD") {
        wstr = "Advanced Micro Devices.";
    }
    else if (str == "AMD ISBETTER") {
        wstr = "Advanced Micro Devices.";
    }
    else if (str == "Geode By NSC") {
        wstr = "National Semiconductor.";
    }
    else if (str == "CyrixInstead") {
        wstr = "Cyrix Corp., VIA Inc.";
    }
    else if (str == "NexGenDriven") {
        wstr = "NexGen Inc., Advanced Micro Devices.";
    }
    else if (str == "CentaurHauls") {
        wstr = "IDT\\Centaur, Via Inc.";
    }
    else if (str == "UMC UMC UMC ") {
        wstr = "United Microelectronics Corp.";
    }
    else if (str == "RiseRiseRise") {
        wstr = "Rise.";
    }
    else if (str == "GenuineTMx86") {
        wstr = "Transmeta.";
    }
    else if (str == "TransmetaCPU") {
        wstr = "Transmeta.";
    }
    else {
        wstr = "Unknown Manufacturer.";
    }
    return wstr;
}
inline static string GetCpName()
{
    int cpuid[4] = {};
    unsigned int cpu_brand_buf[13] = {};
    int i = 0, k = 0;

    memset((void*)cpu_brand_buf, 0, sizeof(cpu_brand_buf));
    /**
    * eax == 0x800000000
    * 如果CPU支持Brand String，则在EAX中返 >= 0x80000004的值。
    */
    __cpuid(cpuid, 0x80000000);
    if (cpuid[0] < 0x80000004)
    {
        return "Unknown CPU";
    }

    for (i = 0x80000002; i <= 0x80000004; i++)
    {
        __cpuid(cpuid, i);
        cpu_brand_buf[k++] = cpuid[0];
        cpu_brand_buf[k++] = cpuid[1];
        cpu_brand_buf[k++] = cpuid[2];
        cpu_brand_buf[k++] = cpuid[3];
    }
    char* buf = (char*)cpu_brand_buf;

    return buf;
}
inline  static string GetCpuID_()
{
    int cpuid[4] = {};
    char cpuid_buf[17] = {};
    __cpuid(cpuid, 1);
    sprintf_s(cpuid_buf, "%08X%08X", cpuid[3], cpuid[0]);
    return cpuid_buf;
}
inline double GetCpuTime()
{

    LARGE_INTEGER nFreq = {}, nCtrStop = {}, nCtrStart = {};
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nCtrStop);
    nCtrStop.QuadPart += nFreq.QuadPart;
    DWORD64 cuStart = __rdtsc();
    do {
        QueryPerformanceCounter(&nCtrStart);
    } while (nCtrStart.QuadPart < nCtrStop.QuadPart);
    return (__rdtsc() - cuStart) / 1000000;
}






bool GetCpuOther(CPUINFO* PCPU) {
    IWbemServices* pSvc = NULL;
    IWbemLocator* pLoc = NULL;
    IEnumWbemClassObject* pEnumerator = NULL;
    BOOL Ret = FALSE;
    //初始化 COM.
    if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED))) {
        return FALSE;
    }
    BOOL blSucceeded = FALSE;
    HRESULT hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
    if (FAILED(hr))
    {
        CoUninitialize();
        return FALSE;

    }
    //创建一个CLSID_WbemLocator对象
    if (FAILED(CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc)) || !pLoc)
    {
        CoUninitialize();
        return Ret;
    }
    if (FAILED(pLoc->ConnectServer(_bstr_t((L"ROOT\\CIMV2")), NULL, NULL, 0, NULL, 0, 0, &pSvc)) || !pSvc) {
        CoUninitialize();
        return Ret;
    }
    if (FAILED(CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
        RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE))) {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return Ret;
    }
    BSTR strQuery = bstr_t((L"SELECT * FROM Win32_Processor"));
    hr = pSvc->ExecQuery(bstr_t((L"WQL")), strQuery, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
    IWbemClassObject* pclsObj = NULL;
    while (pEnumerator)
    {
        ULONG uReturn = 0;
        hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (0 == uReturn)
            break;
        VARIANT vtProp = { 0 };

        hr = pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
        PCPU->Description = W2Estr(vtProp.bstrVal);

        hr = pclsObj->Get(L"DataWidth", 0, &vtProp, 0, 0);
        PCPU->Bit = vtProp.intVal;
        hr = pclsObj->Get(L"L2CacheSize", 0, &vtProp, 0, 0);
        PCPU->L2 = vtProp.llVal;
        hr = pclsObj->Get(L"L1CacheSize", 0, &vtProp, 0, 0);
        PCPU->L1 = vtProp.llVal;
        hr = pclsObj->Get(L"L3CacheSize", 0, &vtProp, 0, 0);
        PCPU->L3 = vtProp.llVal;
        hr = pclsObj->Get(L"NumberOfCores", 0, &vtProp, 0, 0);
        PCPU->cores = vtProp.llVal;
        hr = pclsObj->Get(L"ThreadCount", 0, &vtProp, 0, 0);
        PCPU->threadcount = vtProp.llVal;
        VariantClear(&vtProp);

    }
    if (pclsObj != NULL) {
        pclsObj->Release();
    }
    if (pEnumerator != NULL) {
        pEnumerator->Release();
    }
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();
    return TRUE;
}


BOOL GetCpuInfo(CPUINFO* pCpuinfo) {
    //CPU指令取CPUID，微软接口有时候取不到
    pCpuinfo->name = A2Estr(GetCpName());
    pCpuinfo->Vendor = A2Estr(GetCPUcomp());
    pCpuinfo->hz = GetCpuTime();
    pCpuinfo->ID = A2Estr(GetCpuID_());
    return GetCpuOther(pCpuinfo);
    
}
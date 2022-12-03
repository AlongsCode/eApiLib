#include"windows.h"
#include<STRING>
#include<vector>
using namespace std;


int  SubtextReplaceAux(char* str1, char* str2)
{
	register char* cp = str1;
	register char* s1, * s2;
	while (*cp)
	{
		s1 = cp;
		s2 = str2;
		while (*s1 && *s2 && !(*s1 - *s2))
			s1++, s2++;
		if (!*s2)
			return cp - str1;

		if (*cp < 0)
		{
			cp++;
			if (!*cp)
				return -1;
		}
		cp++;
	}
	return -1;
}
string ReplaceSubText(string str, string wcstr, string cstr, size_t bg, size_t num, bool Casesensitive) {// �����ߺ� ��
	if (wcstr.empty())
	{
		return str;

	}
	char* �����滻�����ı�_ = &wcstr[0];
	//��ʼ�滻λ��
	size_t ��ʼλ�� = bg;
	if (��ʼλ�� <= 1)
		��ʼλ�� = 0;
	else
		��ʼλ�� = bg - 1;
	//�жϿ�ʼλ��
	if (wcstr.empty())
	{
		return str;

	}
	char* cp = &str[0];
	char* pstart = cp + ��ʼλ��;
	for (; *cp && cp < pstart; cp++)
		if (*cp < 0) cp++; // ����

	size_t nSlen = (cp + strlen(cp)) - &str[0];

	//�������ı�

	size_t ndlen = 0;
	if (&wcstr[0]) {
		ndlen = strlen(wcstr.c_str());
	};
	//�滻����

	size_t �滻���д��� = num;
	if (�滻���д��� == 0) {
		�滻���д��� = 0x7fffffff;// ����滻����21��
	}
	size_t nSublen = strlen(cstr.c_str());

	// ��ʼ����
	string ����ֵ;
	int ��һ����ͬ������ʼ��ַ;
	int nPos;
	char* pFirst = cp;
	char* pLast = cp + nSlen;

	if (Casesensitive) // ���ִ�Сд
	{
		for (; �滻���д��� > 0; �滻���д���--)
		{

			nPos = SubtextReplaceAux(cp, �����滻�����ı�_);

			if (nPos == -1)
				break;
			if (cp + nPos - pFirst > 0) {
				����ֵ.append(pFirst, cp + nPos - pFirst);
			}
			if (nSublen > 0) {
				����ֵ = ����ֵ + cstr;

			}
			cp += nPos + ndlen;
			pFirst = cp;
		}
	}
	else
	{
		for (; �滻���д��� > 0; �滻���д���--)
		{
			nPos = SubtextReplaceAux(cp, �����滻�����ı�_);
			if (nPos == -1)
				break;
			if (cp + nPos - pFirst > 0)
				����ֵ.append(pFirst, cp + nPos - pFirst);

			if (nSublen > 0)
				����ֵ = ����ֵ + cstr;

			cp += nPos + ndlen;
			pFirst = cp;
		}
	}

	if (pLast - pFirst > 0)
		����ֵ.append(pFirst, pLast - pFirst);

	// ���Ƽ�����
	return ����ֵ;
}

vector<string> EnumRegistryKey(HKEY root, string path)
{
	REGSAM Type;
	HKEY pHkey;
	SYSTEM_INFO INFO;
	std::vector<string> ret;
	pHkey = 0;
	GetNativeSystemInfo(&INFO);
	if (INFO.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || (Type = KEY_WOW64_32KEY | KEY_ALL_ACCESS, INFO.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)) {

		Type = KEY_WOW64_64KEY | KEY_ALL_ACCESS;
	}

	RegOpenKeyExA(root, path.c_str(), 1, Type, &pHkey);
	char name[MAX_PATH] = {};
	if (!RegEnumKeyA(pHkey, 0, name, MAX_PATH))
	{
		ret.push_back(name);
		if (!RegEnumKeyA(pHkey, 1, name, MAX_PATH))
		{
			DWORD i = 2;
			do {
				ret.push_back(name);
			} while (!RegEnumKeyA(pHkey, i++, name, MAX_PATH));
		}
		RegCloseKey(pHkey);
	}
	return ret;
}
void static DleteMore(string name, HKEY hkey, string parpath, HKEY handle, string livepath)
{

	vector<string> data;
	DWORD samDesired;
	SYSTEM_INFO SystemInfo;
	string needhandle;
	GetNativeSystemInfo(&SystemInfo);
	if (SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 || (samDesired = KEY_WOW64_32KEY, SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)) {
		samDesired = KEY_WOW64_64KEY;
	}
	do
	{
		data = EnumRegistryKey(hkey, livepath);


		for (size_t i = 0; i < data.size(); ++i)
		{

			if (!EnumRegistryKey(hkey, livepath + "\\" + data[i]).empty()) {
				DleteMore(name, hkey, parpath, handle, livepath + "\\" + data[i]);
			}
			else {
				needhandle = ReplaceSubText(livepath + "\\" + data[i], parpath + "\\", string(), 1, 1, true);;
				RegDeleteKeyExA(handle, needhandle.c_str(), samDesired, 0);

			}
		}
	} while (EnumRegistryKey(hkey, livepath).size() >= 1);
	needhandle = ReplaceSubText(livepath, parpath + "\\", string(), 1, 0, true);
	RegDeleteKeyExA(handle, needhandle.c_str(), samDesired, 0);
}
bool AddRightMenu(string Rangeorextensiontobeused, string Title, string comline, string shortkey, string icon, bool shiftdisplay) {
	string Actionpath;
	if (Rangeorextensiontobeused == "*")
	{
		Actionpath = "Directory\\Background\\shell";
	}
	else if (Rangeorextensiontobeused == "D")
	{
		Actionpath = "DesktopBackground\\Shell";
	}
	else if (Rangeorextensiontobeused == "URL")
	{
		Actionpath = "Directory\\shell";
	}
	else
	{
		Actionpath = "*\\shell";
		if (Rangeorextensiontobeused != "SAVER") {
			Actionpath = Rangeorextensiontobeused;
		}
	}
	HKEY phkResult = 0;
	SYSTEM_INFO SystemInfo;
	GetNativeSystemInfo(&SystemInfo);
	REGSAM Accessrights, samDesired;
	if (SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || (Accessrights = KEY_WOW64_32KEY | KEY_ALL_ACCESS, SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)) {
		Accessrights = KEY_WOW64_64KEY | KEY_ALL_ACCESS;
	}
	if (SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || (samDesired = KEY_WOW64_32KEY, SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64))
	{
		samDesired = KEY_WOW64_64KEY;
	}

	RegCreateKeyExA(HKEY_CLASSES_ROOT, Actionpath.c_str(), 0, 0, 0, Accessrights, 0, &phkResult, 0);
	if (!phkResult) {
		return false;
	}
	RegSetValueExA(phkResult, "SubCommands", 0, REG_SZ, 0, 0);
	RegCloseKey(phkResult);
	string lpSubKey = Actionpath + "\\shell";
	GetNativeSystemInfo(&SystemInfo);
	RegCreateKeyExA(HKEY_CLASSES_ROOT, lpSubKey.c_str(), 0, 0, 0, Accessrights, 0, &phkResult, 0);
	if (!phkResult) {
		return false;
	}
	HKEY hKey = 0;
	RegOpenKeyExA(HKEY_CLASSES_ROOT, lpSubKey.c_str(), 0, Accessrights, &hKey);
	string lpPstr = lpSubKey;
	lpSubKey = lpSubKey + "\\" + Actionpath + "\\shell" + "\\" + Title;
	if (EnumRegistryKey(HKEY_CLASSES_ROOT, lpSubKey).size() <= 0) {
		RegDeleteKeyExA(hKey, (Actionpath + "\\shell" + "\\" + Title).c_str(), samDesired, 0);
	}
	else
	{
		DleteMore((Actionpath + "\\shell" + "\\" + Title), HKEY_CLASSES_ROOT, lpPstr, hKey, lpSubKey);
	}
	RegCloseKey(hKey);
	;
	RegCloseKey(phkResult);
	RegCreateKeyExA(HKEY_CLASSES_ROOT, (Actionpath + "\\shell" + "\\" + Title).c_str(), 0, 0, 0, Accessrights, 0, &phkResult, 0);
	if (!phkResult) {
		return false;
	}
	if (!shortkey.empty())
	{
		string temp = Title + "(&" + shortkey + ")";
		RegSetValueExA(phkResult, "MUIVerb", 0, REG_SZ, (const BYTE*)temp.c_str(), temp.size());
	}
	else
	{

		RegSetValueExA(phkResult, "MUIVerb", 0, REG_SZ, (const BYTE*)Title.c_str(), Title.size());
	}
	if (!icon.empty())
	{

		RegSetValueExA(phkResult, "icon", 0, REG_SZ, (const BYTE*)icon.c_str(), icon.size());
	}
	if (shiftdisplay) {
		RegSetValueExA(phkResult, "Extended", 0, REG_SZ, 0, 0);
	}
	RegCloseKey(phkResult);
	RegCreateKeyExA(HKEY_CLASSES_ROOT, (Actionpath + "\\shell" + "\\" + Title + "\\command").c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, Accessrights, NULL, &phkResult, NULL);
	if (phkResult)
	{
		RegSetValueExA(phkResult, 0, 0, REG_SZ, (const BYTE*)comline.c_str(), comline.size());
		return 1;
	}
	return 0;
}

bool DeleteRightMenu(string Rangeorextensiontobeused, string Title) {

	SYSTEM_INFO SystemInfo;
	GetNativeSystemInfo(&SystemInfo);
	REGSAM Accessrights, samDesired;
	if (SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || (Accessrights = KEY_WOW64_32KEY | KEY_ALL_ACCESS, SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)) {
		Accessrights = KEY_WOW64_64KEY | KEY_ALL_ACCESS;
	}
	if (SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || (samDesired = KEY_WOW64_32KEY, SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64))
	{
		samDesired = KEY_WOW64_64KEY;
	}
	HKEY hKey;
	;
	if (RegOpenKeyExA(HKEY_CLASSES_ROOT, 0, 0, Accessrights, &hKey) != ERROR_SUCCESS)
	{
		return false;
	}
	
	if (!EnumRegistryKey(HKEY_CLASSES_ROOT, "\\" + Title).empty())
	{
		DleteMore(Title, HKEY_CLASSES_ROOT, "", hKey, "\\" + Title);
	}
	if (RegDeleteKeyExA(hKey, Title.c_str(), samDesired, 0)) {
		RegCloseKey(hKey);
		return false;
	};
	RegCloseKey(hKey);
	return true;
}
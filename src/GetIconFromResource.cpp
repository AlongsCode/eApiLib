#include<windows.h>
#include<string>
#include <algorithm>
using namespace std;
#include"IconHelp.h"

inline string TakeUnifiedExtName(string paht){
    string result(paht);
    std::transform(paht.begin(), paht.end(), result.begin(), tolower);
    if (!result.empty())
    {
        result = result.substr(result.rfind(".") + 1);
    }
    return result;
}
typedef struct ICONINDEXMAT
{
    DWORD TargetIndex;
    DWORD Count;
    char* IndexId;

}*LPICONINDEXMAT;
char* Mystrdup(const char* str)
{
    int len = 0;
    const char* pstr = str;
    while (*pstr++ != '\0')
    {
        len++;
    }

    char* pdest = (char*)malloc(len + 1);

    int word_num = len / sizeof(size_t);
    int byte_num = len % sizeof(size_t);

    const size_t* wsrc = (size_t*)str;
    size_t* wdest = (size_t*)pdest;
    while (word_num--)
    {
        *wdest++ = *wsrc++;
    }

    const char* bsrc = (char*)wsrc;
    char* bdest = (char*)wdest;
    while (byte_num--)
    {
        *bdest++ = *bsrc++;
    }

    pdest[len] = '\0';

    return pdest;
}

BOOL CALLBACK MyEnumProcedure(HMODULE hModule, LPCSTR lpType, LPSTR lpName, LONG_PTR lParam)
{
    LPICONINDEXMAT MatchObj = (LPICONINDEXMAT)lParam;//����ȫ�ֱ���ʹ��
    if (++MatchObj->Count == MatchObj->TargetIndex)
    {
        if (IS_INTRESOURCE(lpName) == FALSE) {

            MatchObj->IndexId = Mystrdup(lpName);//�������죬��ΪID�п���ʱ����������û�취��string�����ܣ���
        }
        else
        {
            MatchObj->IndexId = (char*)(int)lpName;
        }

    }
    return 1;
}
//�ͷŴ���Щ���⣬�����Ժ󷵻صĺ�����û��ȥ�ͷţ������������ں�����ʹ��Ƶ�ʣ��������ַ����ڴ泤��Ҳ��С�����������
int GetIconFromResource(string PathName, bool Extract2ClipBoard, string SaveName, int _Index) {
    LPICONRESOURCE ObjIcon = NULL;
    MyIcon pIcon;
    ICONINDEXMAT MatchObj = { _Index,0,(char*)-1 };
    string ExtName = TakeUnifiedExtName(PathName);

    if (ExtName == "ico")
    {
        ObjIcon = pIcon.ReadIconFromICOFile(PathName.c_str());
        ++MatchObj.Count;
    }
    else {
        if (ExtName == "exe" || ExtName == "dll" || ExtName == "icl")
        {
            HMODULE  hLibModule = LoadLibraryExA(PathName.c_str(), 0, LOAD_LIBRARY_AS_DATAFILE);
            if (hLibModule)
            {
                if (!EnumResourceNamesA(hLibModule, MAKEINTRESOURCEA((ULONG_PTR)(RT_ICON)+DIFFERENCE), (ENUMRESNAMEPROCA)MyEnumProcedure, (LONG_PTR)&MatchObj))
                {
                    FreeLibrary(hLibModule);
                    return 0;
                }
                FreeLibrary(hLibModule);
                if (MatchObj.IndexId != (char*)-1)
                {
                    ObjIcon = pIcon.ReadIconFromEXEFile(PathName.c_str(), MatchObj.IndexId);
                }
            }
        }
    }
    if (!ObjIcon)
    {
        return 0;
    }
    if (MatchObj.Count > 0 && MatchObj.TargetIndex <= MatchObj.Count)
    {
        string SaveExtName = TakeUnifiedExtName(SaveName);
        if (Extract2ClipBoard)//��������
        {
            if (ObjIcon)
            {
                pIcon.IconImageToClipBoard(ObjIcon->IconImages);
            }
        }
        if (!SaveName.empty()) {//���ļ�

            if (SaveExtName == "ico" && ObjIcon) {
                pIcon.WriteIconToICOFile(ObjIcon, SaveName.c_str());
            }
            else if (SaveExtName == "bmp" && ObjIcon)
            {
                pIcon.IconImageToBMPFile(SaveName.c_str(), ObjIcon->IconImages);
            }
        }//���Ƿ���Ҫ���ֽڼ�����

    }
    if (ObjIcon)
    {
        if (ObjIcon->nNumImages > 0)//�����ͼ����������0
        {
            for (UINT i = 0; i < ObjIcon->nNumImages; i++)
            {
                free(ObjIcon->IconImages[i].lpBits);
            }

        }
        free(ObjIcon);
    }
    return MatchObj.Count;
}//
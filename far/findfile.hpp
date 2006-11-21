#ifndef __FINDFILES_HPP__
#define __FINDFILES_HPP__
/*
findfile.hpp

����� (Alt-F7)

*/

/* Revision: 1.18 11.07.2006 $ */

/*
Modify:
  11.07.2006 EL
    + DoScanTree()
  22.07.2005 SVS
    + SEARCH_INPATH - ������ �� PATH`�
  24.04.2005 KM
    ! ��������� � ����� � ������ ������� �������������� ���������� ������.
  12.04.2005 KM
    + ����� ������� ��� ��������� ������� ����������� ������ � ������
      �������� ��������� �������� ���������
  19.01.2003 KM
    + RemovePseudoBackSlash
    ! ����� �������� UpdatePanels � ������� SetPluginDirectory
  25.04.2002 IS
    ! ��������� const
  07.04.2002 KM
    + _FINDLIST.Used - ���� ��������� ��� ����������� �������������
      ��������� ����� ����� �� ������ �� ��������� ������.
  02.04.2002 KM
   + SEARCH_ALL_BUTNETWORK - ����� �� ���� ������, ����� ������� � �������.
   + PrepareDriveNameStr - ��������� ������������ �� ���� ���� ��� ����������
     ������ � ������ ����� ������� ������ ������.
  30.01.2002 VVM
   + � ��������� _ARCLIST ��������� ���� RootPath - ���� �� ������ �������
     ����� ����� �������� ��� ������. ����� ��� ����������� ��������� ������
     � ������ ������ �� ������ �������.
  23.01.2002 VVM
    + GetPluginFile() - �������� ���� ��� ��������� � ������ �������.
      � ������� �� ����������� ������� - ��������� ����������� �����
      � ������ ��� ��� SetDirectory()
  16.01.2002 VVM
    ! � ������� AddMenuRecord �� ���������� �������� Path, �� ��� ������...
  13.10.2001 VVM
    ! ��� ��� ������ � ����-������.
    + ����� ������� - �������� ������. ���-�� ������ ����������� ������
      ����� ������� �� [New search]
  12.10.2001 VVM
    ! ��������� �������� ������. ����������� �� ���������� ����������,
      ������� ����� �������������. ������ ������� ������ ������ �����
      ������ � ����� ��� ����� ������.
  09.10.2001 VVM
    ! ��������� ������ - ��������� ����������� :))))
  31.07.2001 KM
    ������� ����������� ������� �� ������ � ���� ������.
  05.06.2001 SVS
    + ���������� ������� (��� ���� ������� �� ����� "[View]" ���������� ���)
  06.05.2001 DJ
    ! �������� #include
  25.06.2000 SVS
    ! ���������� Master Copy
    ! ��������� � �������� ���������������� ������
*/

#include "plugin.hpp"

#undef SEARCH_ALL
enum {
  SEARCH_ALL=0,
  SEARCH_ALL_BUTNETWORK,
  SEARCH_INPATH,
  SEARCH_ROOT,
  SEARCH_FROM_CURRENT,
  SEARCH_CURRENT_ONLY,
  SEARCH_SELECTED
};

typedef struct _ARCLIST {
  char ArcName[NM];
  HANDLE hPlugin;    // Plugin handle
  DWORD Flags;       // OpenPluginInfo.Flags
  char RootPath[NM]; // Root path in plugin after opening.
} ARCLIST, *LPARCLIST;

typedef struct _FINDLIST {
  WIN32_FIND_DATA   FindData;
  DWORD             ArcIndex;
  DWORD             Used;
//  BYTE Addons[6];
} FINDLIST, *LPFINDLIST;

class FindFiles
{
  private:

    static BOOL FindListGrow();
    static BOOL ArcListGrow();
    static DWORD AddFindListItem(WIN32_FIND_DATA *FindData);
    static DWORD AddArcListItem(const char *ArcName, HANDLE hPlugin,
                                DWORD dwFlags, const char *RootPath);
    static void ClearAllLists();
    static void AdvancedDialog();

    int FindFilesProcess();
    static LONG_PTR WINAPI FindDlgProc(HANDLE hDlg,int Msg,int Param1,LONG_PTR Param2);
    static LONG_PTR WINAPI MainDlgProc(HANDLE hDlg,int Msg,int Param1,LONG_PTR Param2);
    static LONG_PTR WINAPI AdvancedDlgProc(HANDLE hDlg,int Msg,int Param1,LONG_PTR Param2);

    static void SetPluginDirectory(char *DirName,HANDLE hPlugin,int UpdatePanel=FALSE);
    static void _cdecl DoScanTree(char* Root, WIN32_FIND_DATA& FindData, char* FullName, size_t cbFullName);
    static void _cdecl PrepareFilesList(void *Param);
    static void _cdecl PreparePluginList(void *Param);
    static void _cdecl WriteDialogData(void *Param);
    static void ScanPluginTree(HANDLE hPlugin, DWORD Flags);
    static int LookForString(char *Name);
    static int IsFileIncluded(PluginPanelItem *FileItem,char *FullName,DWORD FileAttr);
    static void ArchiveSearch(char *ArcName);
//    static void AddMenuRecord(char *FullName,char *Path,WIN32_FIND_DATA *FindData);
    static void AddMenuRecord(char *FullName, WIN32_FIND_DATA *FindData);
//    static void RereadPlugin(HANDLE hPlugin);
    static int GetPluginFile(DWORD ArcIndex, struct PluginPanelItem *PanelItem,
                             char *DestPath, char *ResultName);
    static char *PrepareDriveNameStr(char *SearchFromRoot,size_t sz);
    static char *RemovePseudoBackSlash(char *FileName);
    static __int64 __fastcall GetSearchInFirst(char *DigitStr);

  public:

    FindFiles();
    ~FindFiles();

};


#endif  // __FINDFILES_HPP__

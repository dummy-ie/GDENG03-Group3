#include "FileUtils.h"

#include <algorithm>

#include "LogUtils.h"

void FileUtils::getFilePath(std::string& meshFilePath)
{
    gdeng03::LogUtils::log("OpenFile");
    wchar_t path[MAX_PATH] = L"";

    OPENFILENAME openFile = OPENFILENAME();
    openFile.lStructSize = sizeof(OPENFILENAME);
    openFile.hwndOwner = nullptr;
    openFile.nMaxFile = MAX_PATH;
    openFile.lpstrFile = path;
    openFile.lpstrFilter = L"OBJ Files\0*.obj\0All Files\0*.*\0";
    openFile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&openFile)) {
        std::wstring ws(path);
        std::string str(ws.begin(), ws.end());
        std::replace(str.begin(), str.end(), '\\', '/');
        meshFilePath = str;
    }
}

#include "dir_scanner.h"

#include "wx/dir.h"
#include <iostream>

class ScanDirSink : public wxDirTraverser {
public:
    ScanDirSink(FilenameMatcher & filenameMatcher,
                bool includeSubDir) :
        m_FilenameMatcher(filenameMatcher)
        , m_IncludeSubDir(includeSubDir)
    {
    }

    ~ScanDirSink()
    {
    }

public:
    virtual wxDirTraverseResult OnFile(const wxString& filename)
    {
        std::cout << filename.utf8_str() << std::endl;

        m_FilenameMatcher.MatchFile(filename);
        wxTheApp->Yield();
        return wxDIR_CONTINUE;
    }

    virtual wxDirTraverseResult OnDir(const wxString& /*dirname*/)
    {
        return m_IncludeSubDir ? wxDIR_CONTINUE : wxDIR_STOP;
    }

private:
    FilenameMatcher & m_FilenameMatcher;
    bool m_IncludeSubDir;
};

ScanDirErrorCodes scan_dir(const wxString & dirToScan,
                           FilenameMatcher & filenameMatcher,
                           bool includeSubDir)
{
    wxDir dir(dirToScan);

    if (!dir.IsOpened())
    {
        return INVALID_DIRECTORY;
    }

    ScanDirSink sink(filenameMatcher, includeSubDir);

    if ((size_t)-1 == dir.Traverse(sink,
                                   wxEmptyString,
                                   wxDIR_DEFAULT | wxDIR_NO_FOLLOW))
    {
        return SCAN_DIR_FAIL;
    }

    return SUCCESS;
}

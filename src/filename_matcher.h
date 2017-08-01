#pragma once

#include "wx/wx.h"
#include "wx/hashmap.h"
#include "wx/regex.h"

typedef struct __filename_pair {
    wxString src_path;
    wxString dst_path;
} filename_pair;

WX_DECLARE_OBJARRAY(filename_pair, FilenamePairArray);

class FilenameMatcher {
public:
    FilenameMatcher(const wxString & baseFolder,
                    bool useWildcard,
                    const wxString & srcPattern,
                    const wxString & dstPattern,
                    FilenamePairArray & filepathMap);
    ~FilenameMatcher();

private:
    bool m_UseWildcard;
    wxString m_SrcPattern;
    wxString m_DstPattern;
    FilenamePairArray & m_FilepathMap;
    wxString m_BaseFolder;
    wxRegEx m_FilepathMatcher;
    wxString m_DstRegex;

    bool GenRegexFromWildcard(wxString & srcRegex,
                              wxString & dstRegex);
public:
    bool Init();
    void MatchFile(const wxString & filepath);
};

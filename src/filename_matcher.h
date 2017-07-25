#pragma once

#include "wx/wx.h"
#include "wx/hashmap.h"
#include "wx/regex.h"

WX_DECLARE_STRING_HASH_MAP(wxString, StringHashMap);

class FilenameMatcher {
public:
    FilenameMatcher(bool useWildcard,
                    const wxString & srcPattern,
                    const wxString & dstPattern,
                    StringHashMap & filepathMap);
    ~FilenameMatcher();

private:
    bool m_UseWildcard;
    wxString m_SrcPattern;
    wxString m_DstPattern;
    StringHashMap & m_FilepathMap;
    wxRegEx m_FilepathMatcher;
    wxString m_DstRegex;

    bool GenRegexFromWildcard(wxString & srcRegex,
                              wxString & dstRegex);
public:
    bool Init();
    void MatchFile(const wxString & filepath);
};

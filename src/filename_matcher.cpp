#include "filename_matcher.h"

#include <iostream>

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(FilenamePairArray);

FilenameMatcher::FilenameMatcher(bool useWildcard,
                                 const wxString & srcPattern,
                                 const wxString & dstPattern,
                                 FilenamePairArray & filepathMap) :
    m_UseWildcard(useWildcard)
    , m_SrcPattern(srcPattern)
    , m_DstPattern(dstPattern)
    , m_FilepathMap(filepathMap)
{
}

FilenameMatcher::~FilenameMatcher()
{
}

bool FilenameMatcher::Init()
{
    wxString srcRegex(m_SrcPattern), dstRegex(m_DstPattern);

    if (m_UseWildcard)
    {
        if (!GenRegexFromWildcard(srcRegex, dstRegex))
            return false;
    }

    std::cout << "src:" << srcRegex.utf8_str() << ", dst:" << dstRegex.utf8_str() << std::endl;

    if (!m_FilepathMatcher.Compile(srcRegex))
    {
        return false;
    }

    m_DstRegex = dstRegex;

    return true;
}

void FilenameMatcher::MatchFile(const wxString & filepath)
{
    if (m_FilepathMatcher.Matches(filepath))
    {
        wxString dstPath(filepath);

        if (m_FilepathMatcher.Replace(&dstPath, m_DstRegex) == 1)
        {
            filename_pair pair = {filepath, dstPath};

            m_FilepathMap.Add(pair);

            std::cout << "src:" << filepath.utf8_str() << ", dst:" << dstPath.utf8_str() << std::endl;
        }
    }
}

bool FilenameMatcher::GenRegexFromWildcard(wxString & srcRegex,
                                           wxString & dstRegex)
{
    int dst_any_count = 0;
    int dst_single_count = 0;
    wxArrayInt any_match_index, single_match_index;
    int match_index = 0;

    srcRegex = wxT("");
    dstRegex = wxT("");

    srcRegex << wxT("^");
    for(int i=0; i < m_SrcPattern.length(); i++)
    {
        if (m_SrcPattern[i] == '*')
        {
            match_index++;
            any_match_index.Add(match_index);
            srcRegex << ("(.*)");
        }
        else if (m_SrcPattern[i] == '?')
        {
            match_index++;
            single_match_index.Add(match_index);
            srcRegex.append("(.)");
        }
        else if (m_SrcPattern[i] == '(')
        {
            srcRegex.append("\\(");
        }
        else if (m_SrcPattern[i] == ')')
        {
            srcRegex.append("\\)");
        }
        else
        {
            srcRegex.append(m_SrcPattern[i]);
        }
    }
    srcRegex << wxT("$");

    for(int i=0; i < m_DstPattern.length(); i++)
    {
        if (m_DstPattern[i] == '*')
        {
            if (dst_any_count >= any_match_index.GetCount())
                return false;

            dstRegex.append("\\") << (any_match_index[dst_any_count]);
            dst_any_count++;
        }
        else if (m_DstPattern[i] == '?')
        {
            if (dst_single_count >= single_match_index.GetCount())
                return false;

            dstRegex.append("\\") << (single_match_index[dst_single_count]);
            dst_single_count++;
        }
        else
        {
            dstRegex.append(m_DstPattern[i]);
        }
    }

    return true;
}

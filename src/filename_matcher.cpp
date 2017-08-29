#include "filename_matcher.h"
#include "wx/filename.h"

#include <iostream>

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(FilenamePairArray);

FilenameMatcher::FilenameMatcher(const wxString & baseFolder,
                                 bool useWildcard,
                                 const wxString & srcPattern,
                                 const wxString & dstPattern,
                                 FilenamePairArray & filepathMap) :
    m_UseWildcard(useWildcard)
    , m_SrcPattern(srcPattern)
    , m_DstPattern(dstPattern)
    , m_FilepathMap(filepathMap)
    , m_BaseFolder(baseFolder)
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

    if (!m_FilepathMatcher.Compile(srcRegex))
    {
        wxLogError(wxT("Invalid source patter:%s"), m_SrcPattern.utf8_str());

        return false;
    }

    m_DstRegex = dstRegex;

    return true;
}

void FilenameMatcher::MatchFile(const wxString & filepath)
{
    //only match file name, exclude dir path
    wxFileName fn(filepath);

    wxString filename = fn.GetFullName();

    if (m_FilepathMatcher.Matches(filename))
    {
        wxString dstPath(filename);

        if (m_FilepathMatcher.Replace(&dstPath, m_DstRegex) >= 1)
        {
            wxFileName dstFn(fn);
            wxFileName tmpDst( wxFileName::FileName(dstPath));

            std::cout << "dst dir:" << tmpDst.GetPath().utf8_str()
                      << ", dst file:" << tmpDst.GetFullName().utf8_str()
                      << std::endl;

            if (tmpDst.GetDirCount() > 0)
                dstFn.AppendDir(wxFileName::FileName(dstPath).GetPath());
            dstFn.SetFullName(wxFileName::FileName(dstPath).GetFullName());

            dstPath = dstFn.GetFullPath();

            filename_pair pair = {filepath, dstPath};

            m_FilepathMap.Add(pair);

            std::cout << "src:" << filepath.utf8_str() << ", dst:" << dstPath.utf8_str() << std::endl;
        }
    }
    else
    {
        fn.MakeRelativeTo(m_BaseFolder);
        wxString fullpath = fn.GetFullPath();
        wxLogMessage(wxT("File:%s 's name is not matching source pattern."), fullpath);
    }
}

static
const
char escape_chars[] = {
    '(', ')', '.', '\\'
};

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
        else
        {
            for(int j = 0;j < sizeof(escape_chars) / sizeof(char); j++)
            {
                if (m_SrcPattern[i] == escape_chars[j])
                {
                    srcRegex.append("\\");
                    break;
                }
            }

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

    std::cout << "src regex:" << srcRegex.utf8_str() << ", dst regex:" << dstRegex.utf8_str() << std::endl;

    return true;
}

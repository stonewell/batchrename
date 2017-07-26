#include "wx/wx.h"
#include "wx/filename.h"

#include "preview_listctrl.h"

#include <iostream>

wxBEGIN_EVENT_TABLE(PreviewListCtrl, wxListCtrl)
wxEND_EVENT_TABLE()

wxString PreviewListCtrl::OnGetItemText(long item, long column) const
{
    if (item >= m_pFilepathArray->GetCount())
        return wxT("");

    wxString result(wxT(""));

    switch(column)
    {
    case 0:
        result = m_pFilepathArray->Item(item).src_path;
        break;
    case 1:
        result = m_pFilepathArray->Item(item).dst_path;
        break;
    default:
        break;
    }

    wxFileName fn(result);
    fn.MakeRelativeTo(m_SrcFolder);

    return fn.GetFullPath();
}

void PreviewListCtrl::SetFilenameArray(const wxString & srcFolder,
                                       FilenamePairArray * pFilepathArray)
{
    m_SrcFolder = srcFolder;
    m_pFilepathArray = pFilepathArray;

    SetItemCount(m_pFilepathArray->GetCount());
}

#include "wx/wx.h"

#include "preview_listctrl.h"

wxBEGIN_EVENT_TABLE(PreviewListCtrl, wxListCtrl)
wxEND_EVENT_TABLE()

wxString PreviewListCtrl::OnGetItemText(long item, long column) const
{
    if (item >= m_pFilepathArray->GetCount())
        return wxT("");

    switch(column)
    {
    case 0:
        return m_pFilepathArray->Item(item).src_path;
    case 1:
        return m_pFilepathArray->Item(item).dst_path;
    default:
        break;
    }

    return wxT("");
}

void PreviewListCtrl::SetFilenameArray(FilenamePairArray * pFilepathArray)
{
    m_pFilepathArray = pFilepathArray;
    SetItemCount(m_pFilepathArray->GetCount());
}

#pragma once

#include "wx/wx.h"
#include "wx/listctrl.h"

#include "filename_matcher.h"

class PreviewListCtrl: public wxListCtrl
{
public:
    PreviewListCtrl(wxWindow *parent,
               const wxWindowID id,
               const wxPoint& pos,
               const wxSize& size,
               long style)
        : wxListCtrl(parent, id, pos, size, style)
        {
        }

public:
    void SetFilenameArray(const wxString & srcFolder, FilenamePairArray * pFilepathArray);
private:
    FilenamePairArray * m_pFilepathArray;
    wxString m_SrcFolder;

    virtual wxString OnGetItemText(long item, long column) const wxOVERRIDE;

    wxDECLARE_NO_COPY_CLASS(PreviewListCtrl);
    wxDECLARE_EVENT_TABLE();
};

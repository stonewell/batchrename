#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>

#include "filename_matcher.h"

class PreviewListCtrl;

class MainDialog : public wxDialog
{
public:
    MainDialog(const wxString& title);

private:
    enum
    {
        ID_BTN_BROWSE = wxID_HIGHEST + 1,
    };

    wxTextCtrl * m_tcFolder;
    wxTextCtrl * m_tcSourcePattern;
    wxTextCtrl * m_tcTargetPattern;

    wxCheckBox * m_cbIncludeSubDir;

    wxRadioButton * m_rbWildcards;
    wxRadioButton * m_rbRegex;

    PreviewListCtrl * m_lcPreview;

    FilenamePairArray m_FilepathArray;

    void OnUpdatePreview(wxCommandEvent & event);
    void OnButtonClick(wxCommandEvent & event);

    void UpdatePreview(const wxString & folder,
                       bool includeSubDir,
                       bool useWildcard,
                       const wxString & srcPattern,
                       const wxString & targeParttern);
};

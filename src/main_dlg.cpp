#include "main_dlg.h"

#include <iostream>

MainDialog::MainDialog(const wxString & title)
    : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(800, 600))
{
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags szDefaultFlags(0);
    szDefaultFlags.Expand().Center().Border(wxTOP|wxLEFT|wxRIGHT, 5);
    wxSizerFlags szBottomFlags(0);
    szBottomFlags.Expand().Center().Border(wxALL, 5);

    //folder name
    wxStaticBoxSizer *sz = new wxStaticBoxSizer(wxVERTICAL,
                                                this,
                                                wxT(""));

    wxBoxSizer *hboxFolder = new wxBoxSizer(wxHORIZONTAL);
    m_tcFolder = new wxTextCtrl(sz->GetStaticBox(), wxID_ANY, wxT(""));

    wxButton *folderButton = new wxButton(sz->GetStaticBox(), ID_BTN_BROWSE, wxT("Browse"));

    hboxFolder->Add(m_tcFolder,
                    wxSizerFlags(1).Expand().Border(wxBOTTOM | wxTOP | wxRIGHT, 5));
    hboxFolder->Add(folderButton,
                    wxSizerFlags(0)
                    .Center().Right()
                    .Border(wxBOTTOM | wxTOP, 5));

    sz->Add(new wxStaticText(sz->GetStaticBox(), wxID_ANY, wxT("Choose folder for batch renaming")),
            szDefaultFlags);
    sz->Add(hboxFolder, szDefaultFlags);

    m_cbIncludeSubDir = new wxCheckBox(sz->GetStaticBox(), wxID_ANY, wxT("including sub directories"));
    sz->Add(m_cbIncludeSubDir, szBottomFlags);

    //match method
    wxStaticBoxSizer *sz2 = new wxStaticBoxSizer(wxVERTICAL,
                                                 this,
                                                 wxT(""));

    m_rbWildcards = new wxRadioButton(sz2->GetStaticBox(), wxID_ANY,
                                      wxT("Use Wildcard"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);

    m_rbRegex = new wxRadioButton(sz2->GetStaticBox(), wxID_ANY,
                                  wxT("Use Regexp"), wxDefaultPosition);

    sz2->Add(new wxStaticText(sz2->GetStaticBox(), wxID_ANY, wxT("Choose file name matching/replacing method")),
             szDefaultFlags);
    sz2->Add(m_rbWildcards, szDefaultFlags);
    sz2->Add(m_rbRegex, szDefaultFlags);
    sz2->Add(new wxStaticText(sz2->GetStaticBox(), wxID_ANY, wxT("Source file pattern")),
             szDefaultFlags);

    m_tcSourcePattern = new wxTextCtrl(sz2->GetStaticBox(), wxID_ANY, wxT("*"));
    sz2->Add(m_tcSourcePattern, szDefaultFlags);

    sz2->Add(new wxStaticText(sz2->GetStaticBox(), wxID_ANY, wxT("Target file pattern")),
             szDefaultFlags);

    m_tcTargetPattern = new wxTextCtrl(sz2->GetStaticBox(), wxID_ANY, wxT("*"));
    sz2->Add(m_tcTargetPattern, szBottomFlags);

    wxStaticBoxSizer *sz3 = new wxStaticBoxSizer(wxVERTICAL,
                                                 this,
                                                 wxT(""));
    sz3->Add(new wxStaticText(sz3->GetStaticBox(), wxID_ANY, wxT("File rename preview")),
             szDefaultFlags);

    wxListCtrl * m_lcPreview = new wxListCtrl(sz3->GetStaticBox(), wxID_ANY,
                                              wxDefaultPosition, wxDefaultSize,
                                              wxLC_REPORT | wxLC_VIRTUAL);

    wxListItem itemCol;
    itemCol.SetText(wxT("Source"));
    itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    m_lcPreview->InsertColumn(0, itemCol);

    itemCol.SetText(wxT("Target"));
    itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    m_lcPreview->InsertColumn(1, itemCol);

    m_lcPreview->SetColumnWidth( 0, wxLIST_AUTOSIZE_USEHEADER );
    m_lcPreview->SetColumnWidth( 1, wxLIST_AUTOSIZE_USEHEADER );

    sz3->Add(m_lcPreview, szBottomFlags);

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    hbox->Add(new wxButton(this, wxID_REPLACE, wxT("Go Rename")),
              wxSizerFlags(1).Center());

    vbox->Add(sz, szDefaultFlags);
    vbox->Add(sz2, szDefaultFlags);
    vbox->Add(sz3, szDefaultFlags);
    vbox->Add(hbox, wxSizerFlags(1).Center());

    SetSizer(vbox);

    //Connect to Events
    Connect(wxEVT_TEXT, wxCommandEventHandler(MainDialog::OnUpdatePreview));
    Connect(wxEVT_CHECKBOX, wxCommandEventHandler(MainDialog::OnUpdatePreview));
    Connect(wxEVT_RADIOBUTTON, wxCommandEventHandler(MainDialog::OnUpdatePreview));

    Connect(wxEVT_BUTTON, wxCommandEventHandler(MainDialog::OnButtonClick));

    Centre();
    ShowModal();

    Destroy();
}

void MainDialog::OnUpdatePreview(wxCommandEvent & event)
{
    UpdatePreview(m_tcFolder->GetValue(),
                  m_cbIncludeSubDir->GetValue(),
                  m_rbWildcards->GetValue(),
                  m_tcSourcePattern->GetValue(),
                  m_tcTargetPattern->GetValue());
}

void MainDialog::OnButtonClick(wxCommandEvent & event)
{
    wxButton * btn = dynamic_cast<wxButton*>(event.GetEventObject());

    if (btn->GetId() == ID_BTN_BROWSE)
    {
        wxDirDialog dlg(this, wxT("Choose directory for file renaming"), wxT(""),
                        wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

        dlg.SetPath(m_tcFolder->GetValue());

        if (wxID_OK == dlg.ShowModal())
        {
            m_tcFolder->SetValue(dlg.GetPath());
        }
    }
}

void MainDialog::UpdatePreview(const wxString & folder,
                               bool includeSubDir,
                               bool useWildcard,
                               const wxString & srcPattern,
                               const wxString & targeParttern)
{
}

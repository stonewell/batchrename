#include "main_dlg.h"

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
    wxTextCtrl *tcFolder = new wxTextCtrl(sz->GetStaticBox(), wxID_ANY, wxT(""),
                                          wxDefaultPosition, wxDefaultSize);
    wxButton *folderButton = new wxButton(sz->GetStaticBox(), -1, wxT("Browse"),
                                      wxDefaultPosition, wxDefaultSize);

    hboxFolder->Add(tcFolder,
                    wxSizerFlags(1).Expand().Border(wxBOTTOM | wxTOP | wxRIGHT, 5));
    hboxFolder->Add(folderButton,
                    wxSizerFlags(0)
                    .Center().Right()
                    .Border(wxBOTTOM | wxTOP, 5));

    sz->Add(new wxStaticText(sz->GetStaticBox(), wxID_ANY, wxT("Choose folder for batch renaming")),
            szDefaultFlags);
    sz->Add(hboxFolder, szDefaultFlags);
    sz->Add(new wxCheckBox(sz->GetStaticBox(), wxID_ANY, wxT("including sub directories")),
            szBottomFlags);

    //match method
    wxStaticBoxSizer *sz2 = new wxStaticBoxSizer(wxVERTICAL,
                                                this,
                                                wxT(""));

    wxRadioButton *rb = new wxRadioButton(sz2->GetStaticBox(), wxID_ANY,
                                          wxT("Use Wildcard"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);

    wxRadioButton *rb1 = new wxRadioButton(sz2->GetStaticBox(), wxID_ANY,
                                           wxT("Use Regexp"), wxDefaultPosition);

    sz2->Add(new wxStaticText(sz2->GetStaticBox(), wxID_ANY, wxT("Choose file name matching/replacing method")),
            szDefaultFlags);
    sz2->Add(rb, szDefaultFlags);
    sz2->Add(rb1, szDefaultFlags);
    sz2->Add(new wxStaticText(sz2->GetStaticBox(), wxID_ANY, wxT("Source file pattern")),
            szDefaultFlags);
    sz2->Add(new wxTextCtrl(sz2->GetStaticBox(), wxID_ANY, wxT("*")),
            szDefaultFlags);
    sz2->Add(new wxStaticText(sz2->GetStaticBox(), wxID_ANY, wxT("Target file pattern")),
            szDefaultFlags);
    sz2->Add(new wxTextCtrl(sz2->GetStaticBox(), wxID_ANY, wxT("*")),
            szBottomFlags);

    wxStaticBoxSizer *sz3 = new wxStaticBoxSizer(wxVERTICAL,
                                                this,
                                                wxT(""));
    sz3->Add(new wxStaticText(sz3->GetStaticBox(), wxID_ANY, wxT("File rename preview")),
            szDefaultFlags);

    wxListCtrl * lcPreview = new wxListCtrl(sz3->GetStaticBox(), wxID_ANY,
                                            wxDefaultPosition, wxDefaultSize,
                                            wxLC_REPORT);

    wxListItem itemCol;
    itemCol.SetText(wxT("Source"));
    itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    lcPreview->InsertColumn(0, itemCol);

    itemCol.SetText(wxT("Target"));
    itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    lcPreview->InsertColumn(1, itemCol);

    lcPreview->SetColumnWidth( 0, wxLIST_AUTOSIZE_USEHEADER );
    lcPreview->SetColumnWidth( 1, wxLIST_AUTOSIZE_USEHEADER );

    sz3->Add(lcPreview, szBottomFlags);

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    hbox->Add(new wxButton(this, wxID_ANY, wxT("Go")),
                           wxSizerFlags(1).Center());

    vbox->Add(sz, szDefaultFlags);
    vbox->Add(sz2, szDefaultFlags);
    vbox->Add(sz3, szDefaultFlags);
    vbox->Add(hbox, wxSizerFlags(1).Center());

    SetSizer(vbox);

    Centre();
    ShowModal();

    Destroy();
}

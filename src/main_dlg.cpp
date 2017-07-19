#include "main_dlg.h"

MainDialog::MainDialog(const wxString & title)
    : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(420, 330))
{
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags sz2Flags(0);
    sz2Flags.Expand().Center().Border(wxTOP|wxLEFT|wxRIGHT, 5);

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
            sz2Flags);
    sz->Add(hboxFolder, sz2Flags);

    //match method
    wxStaticBoxSizer *sz2 = new wxStaticBoxSizer(wxVERTICAL,
                                                this,
                                                wxT(""));

    wxRadioButton *rb = new wxRadioButton(sz2->GetStaticBox(), wxID_ANY,
                                          wxT("Use Wildcard"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);

    wxRadioButton *rb1 = new wxRadioButton(sz2->GetStaticBox(), wxID_ANY,
                                           wxT("Use Regexp"), wxDefaultPosition);

    sz2->Add(new wxStaticText(sz2->GetStaticBox(), wxID_ANY, wxT("Choose file name matching/replacing method")),
            sz2Flags);
    sz2->Add(rb, sz2Flags);
    sz2->Add(rb1, sz2Flags);

    vbox->Add(sz, sz2Flags);
    vbox->Add(sz2, sz2Flags);

    SetSizer(vbox);

    Centre();
    ShowModal();

    Destroy();
}

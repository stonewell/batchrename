#include "app.h"
#include "main_dlg.h"

IMPLEMENT_APP(BatchRenameApp)

bool BatchRenameApp::OnInit()
{

    MainDialog * mainDlg = new MainDialog(wxT("Batch Rename File Name"));
    mainDlg->Show(true);

    return true;
}

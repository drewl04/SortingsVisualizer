#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainWindow* window = new MainWindow("Sortings Visualizer");
    window->SetIcon(wxICON(aaaa));
    window->Center();
    window->Show();

    return true;
}


#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    /* initializes a GUI app,
    sets title, icon,
    centers the window,
    and starts the GUI loop */
    MainWindow* window = new MainWindow("Sortings Visualizer");
    window->SetIcon(wxICON(aaaa));
    window->Center();
    window->Show();

    return true;
}


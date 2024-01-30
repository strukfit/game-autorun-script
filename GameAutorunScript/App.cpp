// App.cpp : Defines the entry point for the application.

#include "App.h"

// Entry point
wxIMPLEMENT_APP(App);

int main(int argc, char* argv[])
{
	return wxEntry(argc, argv);
}

bool App::OnInit()
{
	GUI* gui = new GUI("Game Autorun Script", wxPoint(50, 50), wxSize(400, 200));

	gui->Show(true);

	return true;
}
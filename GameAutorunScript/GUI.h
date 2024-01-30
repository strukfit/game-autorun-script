#pragma once
#include <wx/wx.h>

class GUI : public wxFrame
{
private:
	wxFrame* mainWindow;		// Main application window
	int hotKeyID;
	int wHotKeyID;
	int shiftHotKeyID;

public:
	bool scriptActivated;

	GUI(const wxString& title, const wxPoint& pos, const wxSize& size);
	void OnHotKey(wxKeyEvent& event);
	void keyPress(WORD keyCode);
	void keyRelease(WORD keyCode);
	void OnKeyPress(wxKeyEvent& event);
	void OnChangeHotkey(wxCommandEvent& event);
};
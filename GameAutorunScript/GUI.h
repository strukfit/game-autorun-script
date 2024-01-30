#pragma once
#include <wx/wx.h>
#include <iostream>
#include <fstream>
#include <string>

class GUI : public wxFrame
{
private:
	int hotKeyID;
	wxButton* changeHotkeyBtn;

public:
	bool scriptActivated;
	int hotKeyCode;

	GUI(const wxString& title, const wxPoint& pos, const wxSize& size);
	void OnHotKey(wxKeyEvent& event);
	void keyPress(WORD keyCode);
	void keyRelease(WORD keyCode);
	void OnKeyPress(wxKeyEvent& event);
	void OnChangeHotkey(wxCommandEvent& event);
	static std::string KeyToString(int keycode);
};

class ChangeHotKeyDialog : public wxDialog
{
private:
	int keyCode;

public:
	ChangeHotKeyDialog(wxWindow* parent);
	void OnKeyPress(wxKeyEvent& event);
	int getKeyCode();
};
#include "GUI.h"
#include <iostream>
#include <fstream>

GUI::GUI(const wxString& title, const wxPoint& pos, const wxSize& size) :
	wxFrame(NULL, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)),
	scriptActivated(false)
{
	Bind(wxEVT_HOTKEY, &GUI::OnHotKey, this);
	Bind(wxEVT_CHAR_HOOK, &GUI::OnKeyPress, this);

	SetBackgroundColour(wxColour(43, 43, 43, 255));
	
	hotKeyID = wxNewId();
	RegisterHotKey(hotKeyID, wxMOD_NONE, VK_RIGHT);

	/*wHotKeyID = wxNewId();
	RegisterHotKey(wHotKeyID, wxMOD_NONE, 'W');

	shiftHotKeyID = wxNewId();
	RegisterHotKey(shiftHotKeyID, wxMOD_SHIFT, WXK_NONE);*/
	
	wxStaticText* textHotkey = new wxStaticText(this, wxID_ANY, "Autorun Hotkey");
	textHotkey->SetForegroundColour(wxColour(255, 255, 255, 255));

	// Changing font size
	wxFont font = textHotkey->GetFont();
	font.MakeBold();
	font.SetPointSize(15);
	textHotkey->SetFont(font);

	wxButton* changeHotkeyBtn = new wxButton(this, wxID_ANY, "Hotkey");
	Bind(wxEVT_BUTTON, &GUI::OnChangeHotkey, this, changeHotkeyBtn->GetId());

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(textHotkey, 0, wxALIGN_CENTER | wxALL, 10);
	sizer->Add(changeHotkeyBtn, 0, wxALIGN_CENTER | wxALL, 10);

	SetSizerAndFit(sizer);

	Centre();
}

//void GUI::OnHotKey(wxKeyEvent& event)
//{
//	if (event.GetId() == wHotKeyID || event.GetId() == shiftHotKeyID)
//	{
//		if (scriptActivated)
//		{
//			keyRelease(VK_SHIFT);	// Release SHIFT button
//			keyRelease('W');	// Release W button
//
//			scriptActivated = false;
//		}
//	}
//	else
//	{
//		if (scriptActivated)
//		{
//			keyRelease(VK_SHIFT);	// Release SHIFT button
//			keyRelease('W');	// Release W button
//		}
//		else
//		{
//			keyPress(VK_SHIFT);	// Press SHIFT button
//			keyPress('W');	// Press W button
//		}
//
//		scriptActivated = !scriptActivated;
//	}
//	
//	event.Skip();
//}

void GUI::OnHotKey(wxKeyEvent& event)
{
	if (scriptActivated)
	{
		keyRelease(VK_SHIFT);	// Release SHIFT button
		keyRelease('W');	// Release W button
	}
	else
	{
		keyPress(VK_SHIFT);	// Press SHIFT button
		keyPress('W');	// Press W button
	}

	scriptActivated = !scriptActivated;

	event.Skip();
}

void GUI::OnChangeHotkey(wxCommandEvent& event)
{

}

void GUI::keyPress(WORD keyCode)
{
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(keyCode, MAPVK_VK_TO_VSC);
	input.ki.dwFlags = 0;

	SendInput(1, &input, sizeof(INPUT));
}

void GUI::keyRelease(WORD keyCode)
{
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(keyCode, MAPVK_VK_TO_VSC);
	input.ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(1, &input, sizeof(INPUT));
}

void GUI::OnKeyPress(wxKeyEvent& event)
{
	if (event.GetKeyCode() == WXK_ESCAPE)
	{
		// Закрываем окно
		Close();
	}
	else
	{
		// Передаем событие дальше для обработки по умолчанию
		event.Skip();
	}
}

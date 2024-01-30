#include "GUI.h"

GUI::GUI(const wxString& title, const wxPoint& pos, const wxSize& size) :
	wxFrame(NULL, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)),
	scriptActivated(false)
{
	Bind(wxEVT_HOTKEY, &GUI::OnHotKey, this);
	Bind(wxEVT_CHAR_HOOK, &GUI::OnKeyPress, this);

	SetBackgroundColour(wxColour(43, 43, 43, 255));

	hotKeyID = wxNewId();
	RegisterHotKey(hotKeyID, wxMOD_NONE, WXK_RIGHT);

	//std::ofstream outFile("hotkey.txt", std::ios::app);
	
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
	ChangeHotKeyDialog* dialog = new ChangeHotKeyDialog(this, hotKeyID);
	dialog->Show();
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
	//if (event.GetKeyCode() == WXK_ESCAPE)
	//{
	//	// Closing the window
	//	Close();
	//}
	//else
	//{
	//	// Passing the event on for default processing
	//	event.Skip();
	//}
}

ChangeHotKeyDialog::ChangeHotKeyDialog(wxWindow* parent, int hotKeyID) :
	wxDialog(parent, wxID_ANY, "Change HotKey"),
	hotKeyID(hotKeyID)
{
	Bind(wxEVT_CHAR_HOOK, &ChangeHotKeyDialog::OnKeyPress, this);

	wxStaticText* textChangehotKey = new wxStaticText(this, wxID_ANY, "Press any key to change hotkey");

	// Changing font size
	wxFont font = textChangehotKey->GetFont();
	font.MakeBold();
	font.SetPointSize(15);
	textChangehotKey->SetFont(font);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(textChangehotKey, 0, wxALIGN_CENTER | wxALL, 20);

	SetSizerAndFit(sizer);

	Centre();
}

void ChangeHotKeyDialog::OnKeyPress(wxKeyEvent& event)
{
	int keycode = event.GetKeyCode();
	
	if (keycode != WXK_SHIFT && keycode != 'W')
	{
		wxMessageBox(KeyToString(keycode) + std::to_string(keycode));
	}
	
	event.Skip();
}

std::string ChangeHotKeyDialog::KeyToString(int keycode)
{
	// Reserved codes for the standard ASCII characters
	if ((keycode >= 33 && keycode <= 126) || (keycode >= 128 && keycode <= 255)) {
		return std::string(1, static_cast<char>(keycode));
	}

	// Reserved wxWidgets codes
	switch (keycode)
	{
    case WXK_BACK:              return "Backspace";
    case WXK_TAB:               return "Tab";
    case WXK_RETURN:            return "Return";
    case WXK_ESCAPE:            return "Escape";
    case WXK_SPACE:             return "Space";
    case WXK_DELETE:            return "Delete";
    case WXK_START:             return "Start";
    case WXK_CANCEL:            return "Cancel";
    case WXK_CLEAR:             return "Clear";
	case WXK_SHIFT:				return "Shift";
    case WXK_ALT:               return "Alt";
    case WXK_CONTROL:           return "Ctrl";
    case WXK_MENU:              return "Menu";
    case WXK_PAUSE:             return "Pause";
    case WXK_CAPITAL:           return "CapsLock";
    case WXK_END:               return "End";
    case WXK_HOME:              return "Home";
    case WXK_LEFT:              return "Left";
    case WXK_UP:                return "Up";
    case WXK_RIGHT:             return "Right";
    case WXK_DOWN:              return "Down";
    case WXK_SELECT:            return "Select";
    case WXK_PRINT:             return "Print";
    case WXK_EXECUTE:           return "Execute";
    case WXK_INSERT:            return "Insert";
    case WXK_HELP:              return "Help";
    case WXK_NUMPAD0:           return "Num0";
    case WXK_NUMPAD1:           return "Num1";
    case WXK_NUMPAD2:           return "Num2";
    case WXK_NUMPAD3:           return "Num3";
    case WXK_NUMPAD4:           return "Num4";
    case WXK_NUMPAD5:           return "Num5";
    case WXK_NUMPAD6:           return "Num6";
    case WXK_NUMPAD7:           return "Num7";
    case WXK_NUMPAD8:           return "Num8";
    case WXK_NUMPAD9:           return "Num9";
    case WXK_F1:                return "F1";
    case WXK_F2:                return "F2";
    case WXK_F3:                return "F3";
    case WXK_F4:                return "F4";
    case WXK_F5:                return "F5";
    case WXK_F6:                return "F6";
    case WXK_F7:                return "F7";
    case WXK_F8:                return "F8";
    case WXK_F9:                return "F9";
    case WXK_F10:               return "F10";
    case WXK_F11:               return "F11";
    case WXK_F12:               return "F12";
    case WXK_NUMLOCK:           return "NumLock";
    case WXK_PAGEUP:            return "PageUp";
    case WXK_PAGEDOWN:          return "PageDown";
    case WXK_NUMPAD_SPACE:      return "NumSpace";
    case WXK_NUMPAD_TAB:        return "NumTab";
    case WXK_NUMPAD_ENTER:      return "NumEnter";
    case WXK_NUMPAD_HOME:       return "NumHome";
    case WXK_NUMPAD_LEFT:       return "NumLeft";
    case WXK_NUMPAD_UP:         return "NumUp";
    case WXK_NUMPAD_RIGHT:      return "NumRight";
    case WXK_NUMPAD_DOWN:       return "NumDown";
    case WXK_NUMPAD_PAGEUP:     return "NumPageUp";
    case WXK_NUMPAD_PAGEDOWN:   return "NumPageDown";
    case WXK_NUMPAD_END:        return "NumEnd";
    case WXK_NUMPAD_BEGIN:      return "NumBegin";
    case WXK_NUMPAD_INSERT:     return "NumInsert";
    case WXK_NUMPAD_DELETE:     return "NumDelete";
    case WXK_NUMPAD_EQUAL:      return "NumEqual";
    case WXK_NUMPAD_MULTIPLY:   return "NumMult";
    case WXK_NUMPAD_ADD:        return "NumAdd";
    case WXK_NUMPAD_SEPARATOR:  return "NumSeparator";
    case WXK_NUMPAD_SUBTRACT:   return "NumSubtract";
    case WXK_NUMPAD_DECIMAL:    return "NumDecimal";
    case WXK_NUMPAD_DIVIDE:     return "NumDivide";
    case WXK_WINDOWS_LEFT:      return "WinLeft";
    case WXK_WINDOWS_RIGHT:     return "WinRight";
    case WXK_WINDOWS_MENU:      return "WinMenu";
	default:
		return "undefined";
	}
}
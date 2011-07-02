#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::Control::HostWindow

	The rendering window wapper used by WPF.
	The engine's rendering window is the child window of this one.

	@todo DPI setting
    
    (C) 2010 xoyojank
*/
using System::IntPtr;
using System::Windows::SizeChangedInfo;
using namespace System::Windows::Interop;
using namespace System::Windows::Input;
using System::Runtime::InteropServices::HandleRef;
//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
namespace Control
{

class WindowMessageHandler;
public ref class HostWindow : public HwndHost
{
public:
	HostWindow();

	HWND GetParentWnd();

	virtual HandleRef BuildWindowCore(HandleRef hwndParent) override;
	virtual void DestroyWindowCore(HandleRef hwnd) override;
	virtual IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, bool% handled) override;

private:
	HWND hParentWnd;
	WindowMessageHandler* wndMsgHandler;
};

//------------------------------------------------------------------------------
inline HWND
HostWindow::GetParentWnd()
{
	return this->hParentWnd;
}

}// Control

}// Editor

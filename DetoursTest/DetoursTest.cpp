#include <stdio.h>
#include <Windows.h>
#include <string>
#include "detours.h"
using std::wstring;
int main() {
	STARTUPINFO startinfo = { sizeof(startinfo) };
	PROCESS_INFORMATION procinfo = {};
	//
	wchar_t modulePathW[MAX_PATH];
	GetModuleFileName(NULL, modulePathW, MAX_PATH);
	wstring modulePath = modulePathW;
	auto moduleSlash = modulePath.find_last_of(L"\\/");
	wstring moduleDir = modulePath.substr(0, moduleSlash);
	//
	auto ok = DetourCreateProcessWithDllEx(
		moduleDir.append(L"/DetoursTarget.exe").c_str(), // path
		nullptr, // command-line
		NULL, // process attributes
		NULL, // thread attributes
		FALSE, // inherit handles
		0, // creation flags
		NULL, // environment
		NULL, // current directory
		&startinfo, // startup info
		&procinfo, // process information
		"DetoursHook.dll",
		NULL
	);
	if (!ok) {
		wprintf(L"Error %d\n", GetLastError());
	}
	else wprintf(L"OK!\n");
}
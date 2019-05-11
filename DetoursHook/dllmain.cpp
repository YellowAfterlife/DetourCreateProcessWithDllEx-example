// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include "detours.h"

int WINAPI myMessageBox(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) {
	wprintf(L"Title: %s\n", lpCaption);
	wprintf(L"Text: %s\n", lpText);
	wprintf(L"Type: %d\n", uType);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (DetourIsHelperProcess()) return TRUE;
    switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH: {
			wprintf(L"We've attached!\n");
			// for example, we're going to hook MessageBox
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			int (WINAPI * pMessageBox)(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) = MessageBoxW;
			DetourAttach(&(PVOID&)pMessageBox, myMessageBox);
			if (DetourTransactionCommit() == NO_ERROR) {
				wprintf(L"Detoured MessageBox!\n");
			}
			else wprintf(L"Failed to detour MessageBox!\n");
		} break;
		case DLL_PROCESS_DETACH: {
			wprintf(L"We've detached!\n");
		} break;
    }
    return TRUE;
}

BOOL APIENTRY Detours_Func() {
	wprintf(L"It doesn't seem like we actually need to do anything here\n");
	return TRUE;
}

#include <stdio.h>
#include <Windows.h>
#define DLL_EXPORT
#include "mydll.h"


extern "C"
{
    DECLDIR void Share() {
        printf("I am exported\n");
    }

    void Keep() {
        MessageBoxA(NULL, "Text boxxed!", "Title", MB_OK);
    }
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        Keep();
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
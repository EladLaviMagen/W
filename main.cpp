#include <Windows.h>

#define LIBRARY "C:\\DLLproj.dll"

typedef void(*PFUNC)(void);

int main() {
	HMODULE hModule = LoadLibraryA(LIBRARY);
	return 0;
}
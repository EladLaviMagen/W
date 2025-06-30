#include <Windows.h>
#include <stdio.h>


int main() {
	char str[] = "C:\\my_awesome_dll.dll";
	LPVOID pathptr = str;
	int pid = 9236;
	HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	PVOID baseAddr = VirtualAllocEx(proc, pathptr, 1024, MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(proc, baseAddr, pathptr, 22, NULL);
	CreateRemoteThread(proc, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, baseAddr, 0, NULL);
	CloseHandle(proc);
	return 0;
}
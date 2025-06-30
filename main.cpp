#include <Windows.h>
#include <stdio.h>


int main() {
	CHAR str[] = "C:\\my_awesome_dll.dll";

	//LPTHREAD_START_ROUTINE func = (LPTHREAD_START_ROUTINE)LoadLibraryA;
	//func(str);

	//HANDLE testThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, str, 0 ,NULL);
	//WaitForSingleObject(testThread, INFINITE);

	DWORD pid = 0;
	scanf_s("%d", &pid);
	HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);
	LPVOID baseAddr = VirtualAllocEx(proc, NULL, strlen(str) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	SIZE_T written = 0;
	
	
	BOOL check = WriteProcessMemory(proc, baseAddr, str, strlen(str) + 1, &written);

	//THREAD_ALL_ACCESS 
	HANDLE thread = CreateRemoteThread(proc, 
										NULL,
										0, 
										(LPTHREAD_START_ROUTINE)LoadLibraryA, 
										baseAddr, 
										0,
										NULL);

	DWORD res = WaitForSingleObject(thread, INFINITE);
	DWORD test = 0;
	check = TerminateThread(thread, GetExitCodeThread(thread, &test));
	check = CloseHandle(thread);
	check = VirtualFreeEx(proc, baseAddr, 0, MEM_RELEASE);
	check = CloseHandle(proc);
	return 0;
}
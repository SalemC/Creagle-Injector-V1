#include "Injector.hpp"

void Injector::Log(std::string msg, int time, bool error) {
	std::cout << msg << std::endl;

	// Sleep with our provided time so the user can see the exit message.
	Sleep(time);

	// Exit our program if an error has occured.
	if (error) {
		exit(1);
	}
}

bool Injector::Exists() {
	struct stat buffer;

	return (stat(fileName.c_str(), &buffer) == 0);
}

DWORD Injector::OpenHandle() {
	auto Handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	PROCESSENTRY32 processEntry;

	processEntry.dwSize = sizeof(processEntry);

	while (Process32Next(Handle, &processEntry)) {
		if (strcmp(processEntry.szExeFile, processName) == 0) {
			auto processID = processEntry.th32ProcessID;

			CloseHandle(Handle);

			return processID;
		}
	}

	CloseHandle(Handle);

	// We've looped through all processes and haven't found our target.
	Log("Process isn't running!", 1000, true);

	// This will never occur because Log will exit the program.
	return 0;
}

static void Injector::Inject() {
	GetFullPathName(fileName.c_str(), MAX_PATH, dllPath, 0);

	auto handle = OpenHandle();

	if (!Exists()) {
		Log("File doesn't exist!", 1000, true);
	}

	auto process = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, handle);

	auto allocatedMemory = VirtualAllocEx(process, NULL, sizeof(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(process, allocatedMemory, dllPath, sizeof(dllPath), NULL);

	CreateRemoteThread(process, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMemory, 0, 0);

	if (CloseHandle(process)) {
		Log("Successfully Injected!", 1000);
	}
}

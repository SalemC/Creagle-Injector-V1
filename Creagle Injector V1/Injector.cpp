#include "Injector.hpp"

void Injector::log(std::string msg, int time) {
	std::cout << msg << std::endl;

	if (time > 0) {
		Sleep(time);
	}
}

bool Injector::exists() {
	struct stat buffer;

	return stat(this->fileName.c_str(), &buffer) == 0;
}

DWORD Injector::openHandle() {
	auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	PROCESSENTRY32 processEntry;

	processEntry.dwSize = sizeof(processEntry);

	while (Process32Next(handle, &processEntry)) {
		if (strcmp(processEntry.szExeFile, this->processName) == 0) {
			auto processID = processEntry.th32ProcessID;

			CloseHandle(handle);

			return processID;
		}
	}

	CloseHandle(handle);

	// We've looped through all processes and haven't found our target.
	this->log("Process isn't running!", 1000);

	exit(1);
}

void Injector::inject() {
	GetFullPathName(this->fileName.c_str(), MAX_PATH, this->dllPath, 0);

	auto handle = this->openHandle();

	if (!this->exists()) {
		this->log("File doesn't exist!", 1000);

		exit(1);
	}

	auto process = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, handle);

	auto allocatedMemory = VirtualAllocEx(process, NULL, sizeof(this->dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(process, allocatedMemory, this->dllPath, sizeof(this->dllPath), NULL);

	CreateRemoteThread(process, 0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibrary), allocatedMemory, 0, 0);

	if (CloseHandle(process)) {
		this->log("Successfully Injected!", 1000);
	}
}

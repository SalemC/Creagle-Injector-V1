#pragma once
// C++
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <stdio.h>
#include <string>

class Injector {
private:
	/*
	 * @brief Log a message to our console.
	 *
	 * @param {std::string} msg - The message to log
	 * @param {int} time - The time to wait
	 * @param {bool} error - Have we called this because of an error?
	 *
	 * Logs a message to our console and exits the program if error is true.
	 */
	void Log(std::string msg, int time, bool error);

	/*
	 * @brief Check if our target dll exists in our current directory.
	 *
	 */
	bool Exists();

	/*
	 * @brief Open a handle to our target process
	 *
	 */
	DWORD OpenHandle();

	std::string fileName = "[placeholder].dll";
	const char* processName = "[placeholder].exe";
	char dllPath[MAX_PATH];

public:
	/*
	 * @brief Inject the target dll into target process.
	 *
	 */
	void Inject();
};
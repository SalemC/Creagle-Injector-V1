#pragma once

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
	 * @param {std::string} msg - The message to log.
	 * @param {int} time - The time to wait.
	 */
	void log(std::string msg, int time = 0);

	/*
	 * @brief Check if our target dll exists in our current directory.
	 */
	bool exists();

	/*
	 * @brief Open a handle to our target process.
	 */
	DWORD openHandle();

	/**
	 * @brief The target file to inject.
	 */
	std::string fileName = "[placeholder].dll";

	/**
	 * @brief The target process to inject into.
	 */
	const char* processName = "[placeholder].exe";

	/**
	 * The file path to the dll.
	 */
	char dllPath[MAX_PATH];

public:
	/*
	 * @brief Inject the target dll into target process.
	 */
	void inject();
};

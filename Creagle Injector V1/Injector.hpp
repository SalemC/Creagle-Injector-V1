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
	 * @param {bool} error - Have we called this because of an error?
	 *
	 * @note Exits the program if error == true.
	 */
	void Log(std::string msg, int time, bool error = false);

	/*
	 * @brief Check if our target dll exists in our current directory.
	 */
	bool Exists();

	/*
	 * @brief Open a handle to our target process.
	 */
	DWORD OpenHandle();

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
	static void Inject();
};

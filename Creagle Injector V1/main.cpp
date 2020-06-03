#pragma once

#include <Windows.h>

#include "Injector.hpp"

int main() {
	auto injector = new Injector();
	
	injector->Inject();

	return 0;
}


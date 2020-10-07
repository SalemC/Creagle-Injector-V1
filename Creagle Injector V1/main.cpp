#pragma once

#include "Injector.hpp"

int main() {
	auto injector = new Injector();
	
	injector->inject();

	return 0;
}


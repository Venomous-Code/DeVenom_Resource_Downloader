#include "Dependencies.h"

//- SPDLOG - Done
//- SDL3 
//- IMGUI 
//- FILESYSTEM 
//- SYS / STAT(MAY BE) 
//- LIBARCHIVE

int main() {

	PackageInstaller::Core core;
	core.InitializeApplication();

	PackageInstaller::Windowing window;

	std::cin.get();
}
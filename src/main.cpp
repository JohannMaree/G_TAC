#include "io/proxCommands.h"
#include "io/proxGmsh.h"
#include "external/include/gmsh.h"
#include <iostream>
#include <string>


int main(int argc, char *argv[]) {
	std::cout << argv[0] << std::endl; //TEST
	command::initialise();
	int ret = 1;
	if (argc>1) {	//argv input
		ret = command::processArgV(argc, argv);
	}
	else {			//User Command TUI
		bool exit = false;
		std::string inputtext;
		int pro = 0;
		while (!exit) {
			std::getline(std::cin, inputtext);
			pro = command::process(inputtext);
			if (pro == 1) {
				exit = true;
				ret = 0;
			}
			if (pgmsh::gmshUI && !gmsh::fltk::isAvailable()) {
				gmsh::fltk::initialize();
				gmsh::option::setNumber("General.ShowModuleMenu", 0);
				std::cout << "FLTK:initialize...\n";	//test
			}
			else if (pgmsh::gmshUI && gmsh::fltk::isAvailable()) {
				gmsh::fltk::run();
			}
			if (pgmsh::gmshUI && pgmsh::gmshUIupdate) {
				gmsh::fltk::update();
				gmsh::fltk::awake("update");
				std::cout << "FLTK:update.\n";	//test
				pgmsh::gmshUIupdate = false;
			}
		}
	}
	return ret;
}
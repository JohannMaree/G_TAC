#include "execute.h"
#include "command.h"
#include "proxFiles.h"
#include "proxCommands.h"
#include "proxStrings.h"
#include "gobject.h"
#include "variable.h"
#include "region.h"

#include <vector>
#include <string>
#include <iostream>

namespace execomm {

	void help(const std::vector<std::string>& parm) {
		if (parm.size() > 1) {
			int type = command::validate(parm[1]);
			if (type != 0) {
				displayCommHelp(type);
			}
			else {
				std::cerr << "help parameter not recognised. use HELP for list of available command parameters.\n";
			}
		}
		else {
			displayHelp();
		}
	}

	bool load(const std::vector<std::string>& parm) {
		int l = loadfile(parm[1]);
		if (l == 0) {
			return false;
		}
		else {
			return true;
		}
	}

	void save(const std::vector<std::string>& parm) {
		pfile::copy(recordfilepath, parm[1]);
	}

	void clcm() {

		//Clear Registers
		gobject::clearGlobalArrays();

		//Initialise G_Flags to defaults
		gobject::initGFlags();

		//Clear Record File
		pfile::clear(recordfilepath);

	}

	void list(const std::vector<std::string>& parm) {
		int listParametersSize = std::stoi(listParameters[0]);
		if (parm.size() > 1) {
			int par = 0, inc = 0;
			bool loop = true;
			while (loop) {
				if (pstring::icompare(parm[1], listParameters[inc])) {
					loop = false;
					par = inc;
				}
				else if (inc == listParametersSize) {
					loop = false;
				}
				++inc;
			}

			switch (par)
			{
			case 1:			//LIST ALL
				std::cout << variables::listAllVariables();
				std::cout << regions::listRegions();
				std::cout << regions::listGlobalRegions();
				break;
			case 2:			//LIST VAR
				std::cout << variables::listVariables();
				break;
			case 3:			//LIST IVAR
				std::cout << variables::listIVariables();
				break;
			case 4:			//LIST RGN
				std::cout << regions::listRegions();
				break;
			case 5:			//LIST GROUPS
				std::cout << regions::listGlobalRegions();
				break;

			default:
				std::cerr << "LIST PARAMETER:" << parm[1] << " NOT RECOGNISED.\n";
				break;
			}
		}
		else {
			//LIST all user created entities
			std::cout << variables::listAllVariables();
			std::cout << regions::listRegions();
			std::cout << regions::listGlobalRegions();
		}

	}

	void set(const std::vector<std::string>& parm) {
		if (parm.size() > 2) {
			regions::setRgn(parm);
		}
		else {
			std::cerr << "Not Enough SET Parameters Specified\n";
		}
	}


}
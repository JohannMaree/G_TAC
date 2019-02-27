#include "execute.h"
#include "command.h"
#include "io/proxFiles.h"
#include "io/proxCommands.h"
#include "io/proxStrings.h"
#include "gobjects/gobject.h"
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
		regions::clearRegion();
		regions::clearGlobalRegion();
		variables::clearVariable();

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

	void del(const std::vector<std::string>& parm) {
		if (pstring::icompare(parm[1], "VAR") || pstring::icompare(parm[1], "IVAR")) {
			int regpos = variables::inRegister(parm[2]);
			if (regpos >= 0) {
				variables::clearVariable(regpos);
				std::cout << "VAR:" << parm[2] << "(" << regpos << ") deleted.\n";
			}
			else {
				if (pstring::icompare(parm[2], "ALL")) {
					variables::clearVariable();
					std::cout << "ALL VARIABLES deleted.\n";
				}
				else {
					std::cerr << "VAR: " << parm[2] << " does not exist.\n";
				}
			}
		}
		else if (pstring::icompare(parm[1], "RGN")) {
			int regpos = regions::inRegister(parm[2], 0);
			if (regpos >= 0) {
				regions::clearRegion(regpos);
				std::cout << "RGN:" << parm[2] << "(" << regpos << ") deleted.\n";
			}
			else {
				if (pstring::icompare(parm[2], "ALL")) {
					regions::clearRegion();
					std::cout << "ALL REGIONS deleted.\n";
				}
				else {
					std::cerr << "RGN: " << parm[2] << " does not exist.\n";
				}
			}
		}
		else if (pstring::icompare(parm[1], "GROUP")) {
			int regpos = regions::inRegister(parm[2], 1);
			if (regpos >= 0) {
				regions::clearGlobalRegion(regpos);
				std::cout << "GROUP:" << parm[2] << "(" << regpos << ") deleted.\n";
			}
			else {
				if (pstring::icompare(parm[2], "ALL")) {
					regions::clearGlobalRegion();
					std::cout << "ALL GROUPS deleted.\n";
				}
				else {
					std::cerr << "GROUP: " << parm[2] << " does not exist.\n";
				}
			}
		}
		//End Delete FUnction
	}

}
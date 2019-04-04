#include "execute.h"
#include "command.h"
#include "io/proxFiles.h"
#include "io/proxCommands.h"
#include "io/proxStrings.h"
#include "io/proxGmsh.h"
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
		if (pstring::checkExtension(parm[1], "txt")) {//If LOAD text file
			int l = loadfile(parm[1]);
			if (l == 0) {
				return false;
			}
			else {
				return true;
			}
		}
		else if (pstring::checkExtension(parm[1], "geo")) {//If LOAD geometry file
			int l = pgmsh::readGeoFile(parm[1]);
			if (l == 0) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			std::cerr << "Unknown FileType extension.\n";
			return false;
		}
	}

	void save(const std::vector<std::string>& parm) {
		if (pstring::checkExtension(parm[1],"txt")) {
			if (pfile::copy(recordfilepath, parm[1])) {
				std::cout << "File: " << parm[1] << " created successfully.\n";
			}
			else {
				std::cerr << "Failed:" << parm[1] << " write failed.\n";
			}
		}
		else {
			std::string fn = parm[1];
			fn += ".txt";
			if (pfile::copy(recordfilepath, fn)) {
				std::cout << "File: " << fn << " created successfully.\n";
			}
			else {
				std::cerr << "Failed:" << fn << " write failed.\n";
			}
		}
	}

	void clcm() {
		//Clear Registers
		gobject::clearGlobalArrays();
		regions::clearRegion();
		regions::clearGlobalRegion();
		variables::clearVariable();

		//Initialise G_Flags to defaults
		gobject::initGFlags();

		//pgmsh clear
		pgmsh::close();

		//Clear Record File
		pfile::clear(recordfilepath);
	}

	void list(const std::vector<std::string>& parm) {
		if (parm.size() > 1) {
			for (ind i = 0; i < parm.size(); ++i) {
				if (pstring::icompare(parm[i], listParameters[1])) {	//ALL
					std::cout << variables::listAllVariables();
					std::cout << regions::listAllRegions();
				}
				else if (pstring::icompare(parm[i], listParameters[2])) {	//VAR
					std::cout << variables::listVariables();
				}
				else if (pstring::icompare(parm[i], listParameters[3])) {	//IVAR
					std::cout << variables::listIVariables();
				}
				else if (pstring::icompare(parm[i], listParameters[4])) {	//RGN
					std::cout << regions::listRegions();
				}
				else if (pstring::icompare(parm[i], listParameters[5])) {	//GROUP
					std::cout << regions::listGlobalRegions();
				}
				else {
					std::cerr << "LIST PARAMETER:" << parm[i] << " NOT RECOGNISED.\n";
				}
			}
		}
		else {
			//LIST all user created entities
			std::cout << variables::listAllVariables();
			std::cout << regions::listAllRegions();
		}

	}

	bool set(const std::vector<std::string>& parm) {
		if (parm.size() > 2) {
			if (regions::setRgn(parm)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			std::cerr << "Not Enough SET Parameters Specified\n";
			return false;
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
	}

}//end namespace execomm
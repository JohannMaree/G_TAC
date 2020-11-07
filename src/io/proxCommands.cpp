#include "proxCommands.h"
#include "proxStrings.h"
#include "proxFiles.h"
#include "proxGmsh.h"
#include "../gobjects/gobject.h"
#include "../variable.h"
#include "../region.h"
#include "../compile.h"
#include "../execute.h"
#include <iostream>//TEST

namespace command {

	void switchcase(const int ctype, const std::vector<std::string>& comm) {
		switch (ctype)
		{
		case 0:
			break;
		case 2:		//HELP command
			execomm::help(comm);
			break;
		case 3:		//LOAD command
			if (execomm::load(comm))
				execomm::addLogEntry(comm);
			break;
		case 4:		//SAVE command
			execomm::save(comm);
			break;
		case 5:		//CLEAR command
			execomm::clear(comm);
			break;
		case 6:		//LIST command
			execomm::list(comm);
			break;
		case 7:		//VAR command
			if (variables::validate(comm, 0))
				execomm::addLogEntry(comm);
			break;
		case 8:		//IVAR command
			if (variables::validate(comm, 1))
				execomm::addLogEntry(comm);
			break;
		case 9:		//RGN command
			if (regions::validate(comm, 1))
				execomm::addLogEntry(comm);
			break;
		case 10:	//GRGN command
			if (regions::validate(comm, 2))
				execomm::addLogEntry(comm);
			break;
		case 11:	//SET command
			if (execomm::set(comm))
				execomm::addLogEntry(comm);
			break;
		case 12:	//COMPILE command
			if (compile::validate(comm))
				execomm::addLogEntry(comm);
			break;
		case 13:	//DEL command
			execomm::del(comm);
			break;
		case 14:	//GMSH command
			if (pgmsh::validate(comm))
				execomm::addLogEntry(comm);
			break;
		case 15:	//GETDP command
			if (pgmsh::runGetDP(comm))
				execomm::addLogEntry(comm);
			break;

		default:
			std::cerr << "command:" << comm[0] << " not recognised. use HELP for a list of available commands.\n";
			break;
		}
	}

	int process(const std::string& comm) {
		int ctype = 0;
		std::string str = clean(comm);
		if (str != "") {
			std::vector<std::string> tmp = pstring::lex(str);
			ctype = validate(tmp[0]);
			if (ctype != 1) {
				switchcase(ctype, tmp);
			}
			else {
				exit();
			}
			//COMMAND TOKEN TEST
			/*
			for (int i = 0; i < tmp.size(); ++i) {
				std::cout << "T#" << i << ": " << tmp[i] << "\n";
			}
			*/
		}
		return ctype;
	}

	void exit() {
		pgmsh::close();
	}

	int validate(const std::string& commType) {
		int ctype = 0;
		bool loop = true;
		while (loop) {
			if (ctype == sizeof(commList)) {
				loop = false;
			}
			else if (pstring::icompare(commType, commList[ctype])) {
				loop = false;
				return ctype;
			}
			++ctype;
		}
		return (-1);
	}

	std::string clean(const std::string& str) {
		std::string ret = str;
		pstring::removePreWhitespace(&ret);
		pstring::removePostWhitespace(&ret);
		pstring::condenseWhitespace(&ret);
		return ret;
	}

	void initialise() {
		//Set gobject flags to defaults
		gobject::initGFlags();
		
		//Set gmsh flags to defaults
		pgmsh::init();

		//Clear record file
		pfile::clear(recordfilepath);
	}

	int processArgV(int argc, char* argv[]) {
		int ret = 0;
		for (int i = 1; i < argc; ++i) {
			if (process(argv[i]) == 0) {
				if (execomm::loadfile(argv[i]) == 0) {
					std::cerr << "argV[" << i << "]: " << argv[i] << " load failed.\n";
					ret = 1;
				}
			}
		}
		return ret;
	}

}//end namespace command

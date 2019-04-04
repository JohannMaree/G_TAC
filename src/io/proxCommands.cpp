#include "proxCommands.h"
#include "proxStrings.h"
#include "proxFiles.h"
#include "proxGmsh.h"
#include "../command.h"
#include "../gobjects/gobject.h"

#include <iostream>//TEST

namespace command {

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
		int ctype = 1;
		bool loop = true;
		while (loop) {
			if (ctype == commListSize) {
				loop = false;
			}
			else if (pstring::icompare(commType, commList[ctype])) {
				loop = false;
				return ctype;
			}
			++ctype;
		}
		return 0;
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

#include "proxCommands.h"
#include "proxStrings.h"
#include "proxFiles.h"
#include "command.h"
#include "gobject.h"

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
			//COMMAND TOKEN TEST
			/*
			for (int i = 0; i < tmp.size(); ++i) {
				std::cout << "T#" << i << ": " << tmp[i] << "\n";
			}
			*/
		}
		return ctype;
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
		gobject::initGFlags();
	}

}

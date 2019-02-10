#include "proxFiles.h"
#include "proxCommands.h"

#include <iostream>
#include <fstream>

namespace pfile {

	void log(const std::string& logtext) {
		write(recordfilepath, logtext);
	}

	bool write(const std::string& fileName, std::string text) {
		std::ofstream fo(fileName, std::ios::app);
		if (fo.is_open()) {
			fo << text << std::endl;
			return true;
		}
		else {
			return false;
		}
	}

	void copy(const std::string& src, const std::string& copy) {
		std::ifstream in(src);
		std::ofstream co(copy);

		co << in.rdbuf();
	}

	void clear(const std::string& fname) {
		std::ofstream out(fname, std::ofstream::out | std::ofstream::trunc);
		out.close();
	}

}

namespace execomm {

	int loadfile(const std::string& filename) {
		std::ifstream fl(filename);
		if (fl.is_open()) {
			std::string line;
			int com;
			while (getline(fl,line)) {
				com = command::process(line);
			}
			std::cout << "FILE:" << filename << " loaded.\n"; //TEST
			return com;
		}
		else {
			std::cerr << "ERROR: LOAD " << filename << "\n"; //TEST
			return 0;
		}
	}

	void displayHelp() {				//General HELP display
		std::string ln;
		std::ifstream helpfile(helpfilepath);
		if (helpfile.is_open()) {
			while (std::getline(helpfile, ln)) {
				std::cout << ln << "\n";
			}
			helpfile.close();
		}
		else {
			std::cerr << "Error Opening File:" << helpfilepath << "\n";
		}

	}

	void displayCommHelp(int htype) {	//Command-Specific HELP display
		std::string ln;
		int c = 0;
		bool red = false;
		int line = 0;
		std::ifstream helpfile(syntaxfilepath);
		if (helpfile.is_open()) {
			while (std::getline(helpfile, ln) || !red) {
				if (ln[0] == '#') {
					++c;
				}
				if (c == htype) {
					if (line > 0) {
						std::cout << ln << "\n";
					}
					++line;
				}
				else if (c == htype + 1) {
					red = true;
				}
			}
			helpfile.close();
		}
		else {
			std::cerr << "Error Opening File:" << syntaxfilepath << "\n";
		}
	}

}




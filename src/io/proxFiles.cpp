#include "proxFiles.h"
#include "proxCommands.h"
#include "proxStrings.h"

#include <iostream>
#include <fstream>
#include <Windows.h>

namespace pfile {

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

	bool copy(const std::string& src, const std::string& copy) {
		std::ifstream in(src);
		std::ofstream co(copy);
		if (co.fail())
			return false;
		co << in.rdbuf();
		return true;
	}

	void clear(const std::string& fname) {
		std::ofstream out(fname, std::ofstream::out | std::ofstream::trunc);
		out.close();
	}

	int run(const std::string& exepath, std::string args) {
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		if (CreateProcess(exepath.c_str(), &args[0], NULL, NULL, false, 0, NULL, NULL, &si, &pi)) {
			std::cout << "RUN:" << exepath << "\n" << std::endl;
			return 0;
		}
		else {
			int ierr = GetLastError();
			std::cout << "ERROR RUN:" << ierr << ", RUN:" << exepath << "\n";
			return ierr;
		}

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		std::cout << "getDP_exit.\n";
	}

}//end namespace pfile

namespace execomm {

	void addLogEntry(const std::vector<std::string>& logComm) {
		std::string add;
		for (ind i = 0; i < logComm.size(); ++i) {
			add += (recordfilepath, logComm[i]);
			add += " ";
		}
		add.pop_back();
		addLogEntry(add);
	}

	void addLogEntry(const std::string& logtext) {
		pfile::write(recordfilepath, logtext);
	}

	int loadfile(const std::string& filename) {
		std::ifstream fl(filename);
		if (fl.is_open()) {
			std::string line;
			int com;
			while (getline(fl,line)) {
				com = command::process(line);
			}
			std::cout << "FILE:" << filename << " loaded.\n"; //TEST
			addLogEntry("");
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


}//end namespace execomm




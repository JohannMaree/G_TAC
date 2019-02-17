#pragma once
#include <string>

#define helpfilepath "../src/io/help.txt"
#define syntaxfilepath "../src/io/syntax.txt"
#define recordfilepath "/log.txt"

namespace pfile {
	
	bool write(const std::string& fileName, std::string text = "\n");
	void copy(const std::string& src, const std::string& copy);
	void clear(const std::string& fname);

}

namespace execomm {

	void addLogEntry(const std::vector<std::string>& logComm);
	void addLogEntry(const std::string& logtext);
	int loadfile(const std::string& filename);
	void displayHelp();
	void displayCommHelp(int htype);

}
#pragma once
#include <string>
#include <vector>

#define helpfilepath "../src/io/help.txt"
#define syntaxfilepath "../src/io/syntax.txt"
#define recordfilepath "log.txt"
#define gmshfilepath "onelab-Windows64/gmsh.exe"
#define getdpfilepath "onelab-Windows64/getdp.exe"

namespace pfile {
	//system file operations
	bool write(const std::string& fileName, std::string text = "\n");
	bool copy(const std::string& src, const std::string& copy);
	void clear(const std::string& fname);
	int run(const std::string& exepath, std::string args);

	inline bool exists(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

}//end namespace pfile

namespace execomm {
	//command file operations
	void addLogEntry(const std::vector<std::string>& logComm);
	void addLogEntry(const std::string& logtext);
	int loadfile(const std::string& filename);
	void displayHelp();
	void displayCommHelp(int htype);

}//end namespace execomm
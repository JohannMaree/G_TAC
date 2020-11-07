#pragma once
#include <string>
#include <vector>

namespace command {

	//Command List
	const std::string commList[] = {
		"//",		//0
		"EXIT",		//1
		"HELP",		//2
		"LOAD",		//3
		"SAVE",		//4
		"CLEAR",	//5
		"LIST",		//6
		"VAR",		//7
		"IVAR",		//8
		"RGN",		//9
		"GROUP",	//10
		"SET",		//11
		"COMPILE",	//12
		"DEL",		//13
		"GMSH",		//14
		"GETDP",	//15

	};

	void switchcase(const int ctype, const std::vector<std::string>& comm);

	int process(const std::string& comm);
	void exit();
	int validate(const std::string& commType);
	std::string clean(const std::string& str);
	void initialise();
	int processArgV(int argc, char* argv[]);

}//end namespace command


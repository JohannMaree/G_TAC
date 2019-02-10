#pragma once
#include <vector>
#include <string>

#define commListSize (sizeof(commList)/sizeof(commList[0]))

namespace command {

	void switchcase(const int ctype, const std::vector<std::string>& comm);

	//Command List
	const std::string commList[] = {
		"N/A",		//0
		"EXIT",		//1
		"HELP",		//2
		"LOAD",		//3
		"SAVE",		//4
		"CLCM",		//5
		"LIST",		//6
		"VAR",		//7
		"IVAR",		//8
		"RGN",		//9
		"GROUP",	//10
		"SET",		//11
		"COMPILE",	//12

	};

}

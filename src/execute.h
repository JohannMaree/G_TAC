#pragma once
#include <vector>
#include <string>

namespace execomm {

	void help(const std::vector<std::string>& parm);
	bool load(const std::vector<std::string>& parm);
	void save(const std::vector<std::string>& parm);
	void clcm();
	void list(const std::vector<std::string>& parm);
	void set(const std::vector<std::string>& parm);


	const std::string listParameters[] = {
		"6",		//0 .:UPDATE:. amount of array elements
		"ALL",		//1
		"VAR",		//2
		"IVAR",		//3
		"RGN",		//4
		"GROUP",	//5

	};


}
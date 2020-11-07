#pragma once
#include <vector>
#include <string>

namespace execomm {

	void help(const std::vector<std::string>& parm);
	bool load(const std::vector<std::string>& parm);
	void save(const std::vector<std::string>& parm);
	void clear(const std::vector<std::string>& parm);
	void clearAll();
	void list(const std::vector<std::string>& parm);
	bool set(const std::vector<std::string>& parm);
	void del(const std::vector<std::string>& parm);

	const std::string listParameters[] = {
		"",			//0
		"ALL",		//1
		"VAR",		//2
		"IVAR",		//3
		"RGN",		//4
		"GROUP",	//5

	};

	const std::string listClear[] = {
		"ALL",		//0
		"MODEL",	//1

	};

}//end namespace execomm
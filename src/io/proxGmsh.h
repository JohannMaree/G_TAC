#pragma once
#include <string>
#include <vector>

namespace pgmsh {

	void init();

	//gmsh file operations
	int readGeoFile(const std::string& gfilename);
	void close();
	int getRgnDim(int id);

	//Command operations
	bool validate(const std::vector<std::string>& parm);
	void listPhysicalGroups();
	void loadRegions();
	void openInterface();
	bool runGetDP(const std::vector<std::string>& args);

	const std::string gmshParameters[] = {
		"READ",		//0
		"LOAD",		//1
		"LIST",		//2
		"RUN",		//3
		"CLEAR",	//4

	};

	const std::string getDPParameters[] = {
		"RUN",		//0

	};

	extern size_t gmshOpen;
	extern std::vector<std::string> GVecModelList;
	extern std::vector<std::string> GFileList;

}//end namespace pgmsh


#pragma once

#include <string>
#include <vector>

namespace pgmsh {

	void init();

	//gmsh file operations
	int readGeoFile(const std::string& gfilename);
	int reloadGeoFile(const int fileID = 0);
	void close();

	//Command operations
	bool validate(const std::vector<std::string>& parm);
	void listPhysicalGroups();
	void loadRegions();
	void openInterface();
	std::string onelabGet(const std::string& name);
	bool onelabSet(const std::string& name, const std::vector<std::string>& val);
	std::vector<int> getPSursForPVol(const int volID);
	std::string createPSurFromPVol(const int volID);
	std::string getPName(const int pDim, const int pTag);
	int getDimension(const int iD);
	void clearModel(const int model = 0, const std::string& name = "");
	void mesh(const std::string& filename, int modelID = -1);

	bool runGetDP(const std::vector<std::string>& args);

	const std::string gmshParameters[] = {
		"READ",		//0
		"LOAD",		//1
		"LIST",		//2
		"GUI",		//3
		"CLEAR",	//4
		"GET",		//5
		"SET",		//6
		"BOUND",	//7
		"MESH",		//8

	};

	const std::string getDPParameters[] = {
		"RUN",		//0

	};

	extern bool gmshUI;
	extern bool gmshUIupdate;
	extern size_t gmshOpen;
	extern std::vector<std::string> GVecModelList;
	extern std::vector<std::string> GFileList;

}//end namespace pgmsh


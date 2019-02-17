#pragma once
#include <vector>
#include <string>

namespace regions {

	struct constant {
		bool exists = false;
		std::string value;
	};

	class region {
	public:
		std::string name;
		std::string identifier;
		std::string description;

		constant conduction;
		constant convection;
		constant radiation;
		constant generation;

		constant bcType1;	//Temp
		constant bcType2;	//Flux

		constant temp_disc;		//Temp Discontinuity

	};

	class gregion {
	public:
		std::string name;
		std::string description;

		std::vector<regions::region *> regions;
	};

	const std::string regParmList[] = {
		"DESC",		//0
		"COND",		//1
		"CONV",		//2
		"RAD",		//3
		"TEMP",		//4
		"FLUX",		//5
		"GEN",		//6
		"JUMP",		//7

	};

	const std::string gRegParmList[] = {
		"DESC",		//0

	};

	void validate(const std::vector<std::string>& parm, int regType);
	void addRgn(const std::vector<std::string>& parm);
	void setProperties(const std::string& comm, region* rgn);
	void addGRgn(const std::vector<std::string>& parm);
	void setRgn(const std::vector<std::string>& parm);
	std::string listRegions();
	std::string listGlobalRegions();
	int inRegister(const std::string& rname, short int rType);

}

extern std::vector<regions::region> GRegister_Regions;
extern std::vector<regions::gregion> GRegister_GlobalRegions;
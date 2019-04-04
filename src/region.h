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
		std::string name;		//name string, unique to GMSH
		std::string identifier;	//id tag int, unique to GMSH
		constant description;	//One word string, description of region
		
		constant dimension;		//Val=0D,1D,2D,3D

		//Primary Conditions
		constant conduction;	//Val=cond coefficient k
		constant convection;	//Val=conv coefficient h
		constant radiation;		//Val=radiation emissivity e
		constant generation;	//Val=internal heat generation Q

		//Boundary Conditions
		constant temperature;	//Val=temp BC
		constant heatflux;		//Val=surface heatflux BC

		//Tertiary Conditions
		constant temp_disc;		//Val=temp discontinuity/jump

		//Primary operating points
		constant tconv;			//Val=conv fluid temp
		constant trad;			//Val=radiation emission surface temp

	};

	class gregion {
	public:
		std::string name;
		constant description;

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
		"DIM",		//8
		"TCONV",	//9
		"TRAD",		//10

	};

	const std::string gRegParmList[] = {
		"DESC",		//0

	};

	bool validate(const std::vector<std::string>& parm, int regType);
	bool addRgn(const std::vector<std::string>& parm);
	bool addGRgn(const std::vector<std::string>& parm);
	void setProperties(const std::string& comm, region* rgn);
	bool setRgn(const std::vector<std::string>& parm);

	std::string listRegions();
	std::string listGlobalRegions();
	std::string listAllRegions();

	int inRegister(const std::string& rname, short int rType);
	int inGRegion(const std::string& rgname, gregion* gr);

	void clearRegion(int pos = (-1));
	void clearGlobalRegion(int pos = (-1));

}//end namespace regions

extern std::vector<regions::region> GRegister_Regions;
extern std::vector<regions::gregion> GRegister_GlobalRegions;
#pragma once
#include <vector>
#include <string>

namespace regions {

	struct constant {
		bool exists = false;
		std::string value;
	};

	struct id {
		int first, last, range = 0;
	};

	class region {
	public:
		std::string name;		//name string, unique to GMSH
		id identifier;			//physical identifier, unique to GMSH
		constant description;	//One word string, description of region
		
		constant dimension;		//Val=0,1,2,3

		int mechanics = 0;

		//Primary Conditions
		constant conduction;	//Val=cond coefficient k
		constant convection;	//Val=conv coefficient h
		constant radiation;		//Val=radiation emissivity e
		constant generation;	//Val=internal heat generation Q

		//Boundary Conditions
		constant temperature;	//Val=temp BC
		constant heatflux;		//Val=surface heatflux BC

		//Tertiary Conditions
		constant temp_disc;		//Val=temp discontinuity/gap
		constant disc_surf;		//Val=interface surface to set gap
		short int discID;

		//Primary operating points
		constant tconv;			//Val=conv fluid temp
		constant trad;			//Val=radiation emission surface temp

	};

	class gregion {
	public:
		std::string name;

		std::vector<regions::region*> regions;
	};

	const std::string regParmList[] = {
		"DESC",		//0
		"COND",		//1
		"CONV",		//2
		"RAD",		//3
		"TEMP",		//4
		"FLUX",		//5
		"GEN",		//6
		"TDISC",	//7
		"DIM",		//8
		"TCONV",	//9
		"TRAD",		//10
		"DSURF",	//11

	};

	bool validate(const std::vector<std::string>& parm, int regType);
	int addRgn(const std::vector<std::string>& parm);
	int addGRgn(const std::vector<std::string>& parm);
	void setProperties(const std::string& comm, region* rgn);
	bool setRgn(const std::vector<std::string>& parm);

	std::string listRegions();
	std::string listGlobalRegions();

	int inRegister(const std::string& id);
	int inRegister(const int& id);
	int inGRegister(const std::string& id);
	int inGRegion(const std::string& rgname, gregion* gr);

	void clearRegion(int pos = (-1));
	void clearGlobalRegion(int pos = (-1));

}//end namespace regions

extern std::vector<regions::region> GRegister_Regions;
extern std::vector<regions::gregion> GRegister_GlobalRegions;
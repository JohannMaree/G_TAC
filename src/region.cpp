#include "region.h"
#include "proxStrings.h"

#include <iostream>

std::vector<regions::region> GRegister_Regions;
std::vector<regions::gregion> GRegister_GlobalRegions;

namespace regions {

	bool validate(const std::vector<std::string>& parm, int regType) {
		if (regType == 1) {
			addRgn(parm);
			return true;
		}
		else if (regType == 2) {
			addGRgn(parm);
			return true;
		}
	}
	 
	void addRgn(const std::vector<std::string>& parm) {
		region x;
		std::vector<std::string> def;
		def = pstring::lex(parm[1], '=');
		x.name = def[0];
		x.identifier = def[1];
		int check = inRegister(x.name,0);
		if (check == (-1)) {
			for (ind i = 2; i < parm.size(); ++i) {
				setProperties(parm[i],&x);
			}
			GRegister_Regions.push_back(x);
		}
		else {
			std::cerr << "Region:" << x.name << " already exists.\n";
		}
	}

	void setProperties(const std::string& comm, region* rgn) {
		std::vector<std::string> rs = pstring::lex(comm, '=');
		//Sub_Command Cases
		if (pstring::icompare(rs[0], regParmList[0])) {		//DESC
			rgn->description = rs[1];
		}
		else if (pstring::icompare(rs[0], regParmList[1])) {	//COND
			rgn->conduction.value = rs[1];
			rgn->conduction.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[2])) {	//CONV
			rgn->convection.value = rs[1];
			rgn->convection.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[3])) {	//RAD
			rgn->radiation.value = rs[1];
			rgn->radiation.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[4])) {	//TEMP
			rgn->bcType1.value = rs[1];
			rgn->bcType1.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[5])) {	//FLUX
			rgn->bcType2.value = rs[1];
			rgn->bcType2.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[6])) {	//GEN
			rgn->generation.value = rs[1];
			rgn->generation.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[7])) {	//JUMP
			rgn->temp_disc.value = rs[1];
			rgn->temp_disc.exists = true;
		}

	}

	void addGRgn(const std::vector<std::string>& parm) {
		int ex = inRegister(parm[1],1);
		if (ex >= 0) {										//If exists
			gregion y = GRegister_GlobalRegions[ex];
			for (ind i = 2; i < parm.size(); ++i) {
				int pos = inRegister(parm[i], 0);
				if (pos >= 0) {
					y.regions.emplace_back(&(GRegister_Regions[pos]));
				}
				else {
					std::cerr << "Region:" << parm[i] << " does not exist.\n";
				}
			}
			GRegister_GlobalRegions.erase(GRegister_GlobalRegions.begin() + ex);
			GRegister_GlobalRegions.push_back(y);
		}
		else {
			gregion y;
			y.name = parm[1];
			for (ind i = 2; i < parm.size(); ++i) {
				if (pstring::ifind(parm[i],gRegParmList[0])) {	//DESC
					std::vector<std::string> rs  = pstring::lex(parm[i], '=');
					y.description = rs[1];
				}
				else {
					int pos = inRegister(parm[i], 0);
					if (pos >= 0) {
						y.regions.push_back(&(GRegister_Regions[pos]));
					}
					else {
						std::cerr << "Region:" << parm[i] << " does not exist.\n";
					}
				}
			}
			GRegister_GlobalRegions.push_back(y);
		}
	}

	void setRgn(const std::vector<std::string>& parm) {
		int pos = inRegister(parm[1], 0);
		if (pos >= 0) {			//Add parameters to RGN
			for (ind i = 2; i < parm.size(); ++i) {
				setProperties(parm[i], &GRegister_Regions[pos]);
			}
		}
		else {
			pos = inRegister(parm[1], 1);
			if (pos >= 0) {		//Add parameters to GROUP region
				std::cout << "POS:G" << pos << "\n";
				for (ind i = 0; i < GRegister_GlobalRegions[pos].regions.size(); ++i) {
					pos = inRegister(GRegister_GlobalRegions[pos].regions[i]->name,0);
					for (ind j = 2; j < parm.size(); ++j) {
						std::cout << "NEWPOS:" << pos << ", J:" << j << "\n";
						setProperties(parm[j], &GRegister_Regions[pos]);
					}
				}
			}
			else {
				std::cerr << "Region:" << parm[1] << " not found.\n";
			}
		}
	}

	std::string listRegions() {
		std::string ret;
		ind size = GRegister_Regions.size();
		if (size > 0) {
			ret += "REGIONS:\n";
			for (ind i = 0; i < size; ++i) {
				ret += GRegister_Regions[i].name + "\t\tID:";
				ret += GRegister_Regions[i].identifier + "\t\t";
				if (GRegister_Regions[i].description != "")
					ret += "DESC:" + GRegister_Regions[i].description + " ";
				if (GRegister_Regions[i].conduction.exists)
					ret += "COND:" + GRegister_Regions[i].conduction.value + " ";
				if (GRegister_Regions[i].convection.exists)
					ret += "CONV:" + GRegister_Regions[i].convection.value + " ";
				if (GRegister_Regions[i].radiation.exists)
					ret += "RAD:" + GRegister_Regions[i].radiation.value + " ";
				if (GRegister_Regions[i].generation.exists)
					ret += "GEN:" + GRegister_Regions[i].generation.value + " ";
				if (GRegister_Regions[i].bcType1.exists)
					ret += "BC1_TEMP:" + GRegister_Regions[i].bcType1.value + " ";
				if (GRegister_Regions[i].bcType2.exists)
					ret += "BC2_FLUX:" + GRegister_Regions[i].bcType2.value + " ";
				if (GRegister_Regions[i].temp_disc.exists)
					ret += "T_JUMP:" + GRegister_Regions[i].temp_disc.value + " ";
				ret += "\n";
			}
		}
		ret += "\n";
		return ret;
	}

	std::string listGlobalRegions() {
		std::string ret;
		ind size = GRegister_GlobalRegions.size();
		if (size > 0) {
			ret += "GLOBAL REGIONS:\n";
			for (ind i = 0; i < size; ++i) {
				ret += GRegister_GlobalRegions[i].name;
				if (GRegister_GlobalRegions[i].description != "")
					ret += "DESC:" + GRegister_GlobalRegions[i].description + " ";
				ret += "\t\tREGIONS:";
				for (ind j = 0; j < GRegister_GlobalRegions[i].regions.size(); ++j) {
					ret += GRegister_GlobalRegions[i].regions[j]->name;
					ret += " ";
				}
				ret += "\n";
			}
		}
		ret += "\n";
		return ret;
	}

	int inRegister(const std::string& rname, short int rType) {
		if (rType == 0) {		//Search Rregister
			for (ind i = 0; i < GRegister_Regions.size(); ++i) {
				if (pstring::icompare(rname, GRegister_Regions[i].name)) {
					return static_cast<int>(i);
				}
			}
		}
		else if(rType == 1){	//Search GRregister
			for (ind i = 0; i < GRegister_GlobalRegions.size(); ++i) {
				if (pstring::icompare(rname, GRegister_GlobalRegions[i].name)) {
					return static_cast<int>(i);
				}
			}
		}
		return (-1);
	}

}
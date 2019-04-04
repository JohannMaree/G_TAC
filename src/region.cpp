#include "region.h"
#include "io/proxStrings.h"

#include <iostream>

std::vector<regions::region> GRegister_Regions;
std::vector<regions::gregion> GRegister_GlobalRegions;

namespace regions {

	bool validate(const std::vector<std::string>& parm, int regType) {
		if (regType == 1) {
			return addRgn(parm);
		}
		else if (regType == 2) {
			return addGRgn(parm);
		}
		return false;
	}
	
	bool addRgn(const std::vector<std::string>& parm) {
		region x;
		std::vector<std::string> def;
		def = pstring::lex(parm[1], '=');
		x.name = def[0];
		int check = inRegister(x.name,0);
		if (check == (-1)) {
			x.identifier = def[1];
			for (ind i = 2; i < parm.size(); ++i) {
				setProperties(parm[i],&x);
			}
			GRegister_Regions.push_back(x);
			return true;
		}
		else {
			std::cerr << "Region:" << x.name << " already exists.\n";
			return false;
		}
	}

	void setProperties(const std::string& comm, region* rgn) {
		std::vector<std::string> rs = pstring::lex(comm, '=');
		//Sub_Command Cases
		if (pstring::icompare(rs[0], regParmList[0])) {		//DESC
			rgn->description.value = rs[1];
			rgn->description.exists = true;
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
			rgn->temperature.value = rs[1];
			rgn->temperature.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[5])) {	//FLUX
			rgn->heatflux.value = rs[1];
			rgn->heatflux.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[6])) {	//GEN
			rgn->generation.value = rs[1];
			rgn->generation.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[7])) {	//JUMP
			rgn->temp_disc.value = rs[1];
			rgn->temp_disc.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[8])) {	//DIM
			rgn->dimension.value = rs[1];
			rgn->dimension.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[9])) {	//TCONV
			rgn->tconv.value = rs[1];
			rgn->tconv.exists = true;
		}
		else if (pstring::icompare(rs[0], regParmList[10])) {	//TRAD
			rgn->trad.value = rs[1];
			rgn->trad.exists = true;
		}

	}

	bool addGRgn(const std::vector<std::string>& parm) {
		int ex = inRegister(parm[1],1);
		if (ex >= 0) {		//If GRegion exists
			int reg = 0;
			for (ind i = 2; i < parm.size(); ++i) {
				int pos = inRegister(parm[i], 0);	
				if (pos >= 0) {		//Region exists
					if (inGRegion(parm[i], &GRegister_GlobalRegions[ex]) == (-1)) {	//If region not already in Group
						GRegister_GlobalRegions[ex].regions.push_back(&(GRegister_Regions[pos]));
						++reg;
					}
				}
				else {				//Region does not exist
					std::cerr << "Region:" << parm[i] << " does not exist.\n";
				}
			}

			if (reg > 0) {	//Verify something was added
				return true;
			}
			else {	//Nothing changed
				return false;
			}
		}
		else {				//Else Create new GRegion
			gregion y;
			y.name = parm[1];
			int reg = 0;
			for (ind i = 2; i < parm.size(); ++i) {
				if (pstring::ifind(parm[i],gRegParmList[0])) {	//DESC
					std::vector<std::string> rs  = pstring::lex(parm[i], '=');
					y.description.value = rs[1];
				}
				else {
					int pos = inRegister(parm[i], 0);
					if (pos >= 0) {//If rgn exists
						if (inGRegion(parm[i], &y) == (-1)) { //If rgn not already in group
							y.regions.push_back(&(GRegister_Regions[pos]));
							++reg;
						}
					}
					else {
						std::cerr << "Region:" << parm[i] << " does not exist.\n";
					}
				}
			}
			if (reg > 0) {
				GRegister_GlobalRegions.push_back(y);
				return true;
			}
			else {
				std::cerr << "GRegion NOT created, parameters contain no valid regions.\n";
				return false;
			}
		}
	}

	bool setRgn(const std::vector<std::string>& parm) {
		int pos = inRegister(parm[1], 0);
		if (pos >= 0) {			//Add parameters to RGN
			for (ind i = 2; i < parm.size(); ++i) {
				setProperties(parm[i], &GRegister_Regions[pos]);
			}
			return true;
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
				return true;
			}
			else {
				std::cerr << "Region:" << parm[1] << " not found.\n";
				return false;
			}
		}
	}

	std::string listRegions() {
		std::string ret;
		ind size = GRegister_Regions.size();
		if (size > 0) {
			ret += std::to_string(size);
			ret += " REGIONS:\n";
			for (ind i = 0; i < size; ++i) {
				ret += GRegister_Regions[i].name + "\t\tID:";
				ret += GRegister_Regions[i].identifier + "\t\t";
				ret += "DIM:" + GRegister_Regions[i].dimension.value + "\t";
				if (GRegister_Regions[i].description.exists)
					ret += "DESC:" + GRegister_Regions[i].description.value + " ";
				if (GRegister_Regions[i].conduction.exists)
					ret += "COND:" + GRegister_Regions[i].conduction.value + " ";
				if (GRegister_Regions[i].convection.exists)
					ret += "CONV:" + GRegister_Regions[i].convection.value + " ";
				if (GRegister_Regions[i].radiation.exists)
					ret += "RAD:" + GRegister_Regions[i].radiation.value + " ";
				if (GRegister_Regions[i].generation.exists)
					ret += "GEN:" + GRegister_Regions[i].generation.value + " ";
				if (GRegister_Regions[i].temperature.exists)
					ret += "TEMP:" + GRegister_Regions[i].temperature.value + " ";
				if (GRegister_Regions[i].heatflux.exists)
					ret += "FLUX:" + GRegister_Regions[i].heatflux.value + " ";
				if (GRegister_Regions[i].temp_disc.exists)
					ret += "T_JUMP:" + GRegister_Regions[i].temp_disc.value + " ";
				ret += "\n";
			}
			ret += "\n";
		}
		else {
			ret = "0 Regions.\n";
		}
		return ret;
	}

	std::string listGlobalRegions() {
		std::string ret;
		ind size = GRegister_GlobalRegions.size();
		if (size > 0) {
			ret += std::to_string(size);
			ret += " GLOBAL_REGIONS:\n";
			for (ind i = 0; i < size; ++i) {
				ret += GRegister_GlobalRegions[i].name;
				if (GRegister_GlobalRegions[i].description.exists)
					ret += "DESC:" + GRegister_GlobalRegions[i].description.value + " ";
				ret += "\t\tREGIONS:";
				for (ind j = 0; j < GRegister_GlobalRegions[i].regions.size(); ++j) {
					ret += GRegister_GlobalRegions[i].regions[j]->name;
					ret += " ";
				}
				ret += "\n";
			}
			ret += "\n";
		}
		else {
			ret = "0 Global Regions.\n";
		}
		return ret;
	}

	std::string listAllRegions() {
		std::string r = listRegions();
		std::string gr = listGlobalRegions();
		std::string s;
		if (r.at(0) == '0') {
			if (gr.at(0) == '0') {
				s = "0 Regions/G_Regions.\n";
			}
			else {
				s = r + gr;
			}
		}
		else {
			s = r + gr;
		}
		return s;
	}

	int inRegister(const std::string& rname, short int rType) {
		if (rType == 0) {		//Search Region register
			for (ind i = 0; i < GRegister_Regions.size(); ++i) {
				if (pstring::icompare(rname, GRegister_Regions[i].name)) {
					return static_cast<int>(i);
				}
			}
		}
		else if(rType == 1){	//Search Global Region register
			for (ind i = 0; i < GRegister_GlobalRegions.size(); ++i) {
				if (pstring::icompare(rname, GRegister_GlobalRegions[i].name)) {
					return static_cast<int>(i);
				}
			}
		}
		return (-1);
	}

	int inGRegion(const std::string& rgname, gregion* gr) {
		for (int i = 0; i < gr->regions.size(); ++i) {
			if (pstring::icompare(rgname, gr->regions[i]->name))
				return i;
		}
		return (-1);
	}

	void clearRegion(int pos) {
		if (pos >= 0) {
			GRegister_Regions.erase(GRegister_Regions.begin() + pos);
		}
		else {
			GRegister_Regions.clear();
		}
	}

	void clearGlobalRegion(int pos) {
		if (pos >= 0) {
			GRegister_GlobalRegions.erase(GRegister_GlobalRegions.begin() + pos);
		}
		else {
			GRegister_GlobalRegions.clear();
		}
	}



}//end namespace regions
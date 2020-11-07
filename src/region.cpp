#include "region.h"
#include "io/proxStrings.h"

#include <iostream>

std::vector<regions::region> GRegister_Regions;
std::vector<regions::gregion> GRegister_GlobalRegions;

namespace regions {

	bool validate(const std::vector<std::string>& parm, int regType) {
		std::vector<std::string> def;
		if (regType == 1) {
			for (size_t i = 2; i < parm.size(); ++i){
				def = pstring::lex(parm[i],'=');
				for (size_t j = 0; j < regParmList->size(); ++j){
					if (!pstring::icompare(def[0], regParmList[j])) {
						std::cerr << "region add:" << parm[1] << " failed. '" << parm[i] << "' not recognised." << std::endl;
						return false;
					}
				}
			}
			return addRgn(parm);
		}
		else if (regType == 2) {
			return addGRgn(parm);
		}
		return false;
	}
	
	int addRgn(const std::vector<std::string>& parm) {
		region x;
		std::vector<std::string> def,range;
		def = pstring::lex(parm[1], '=');
		x.name = def[0];

		range = pstring::lex(def[1], ':');
		x.identifier.first = std::stoi(range[0]);
		if (range.size() == 2) {				//check if rgn range used as id
			x.identifier.last = std::stoi(range[1]);
			x.identifier.range = (x.identifier.last - x.identifier.first) + 1;

			for (ind i = 2; i < parm.size(); ++i) {
				setProperties(parm[i], &x);
			}
			GRegister_Regions.push_back(x);
			return static_cast<int>(GRegister_Regions.size() - 1);
		}
		else {
			if (inRegister(x.name) == (-1)) {	//check if name already exists
				if (inRegister(x.identifier.first) == (-1)) {	//check if id already exists
					for (ind i = 2; i < parm.size(); ++i) {
						setProperties(parm[i], &x);
					}
					GRegister_Regions.push_back(x);
					return static_cast<int>(GRegister_Regions.size() - 1);
				}
				else {
					std::cerr << "Region_ID:" << x.identifier.first << " already exists.\n";
					return -1;
				}
			}
			else {
				std::cerr << "Region:" << x.name << " already exists.\n";
				return -1;
			}
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
		else if (pstring::icompare(rs[0], regParmList[7])) {	//TDISC
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
		else if (pstring::icompare(rs[0], regParmList[11])) {	//DSURF
			rgn->disc_surf.value = rs[1];
			rgn->disc_surf.exists = true;
		}

	}

	int addGRgn(const std::vector<std::string>& parm) {
		std::vector<std::string> sv = pstring::lex(parm[1], '=');
		int ex = inRegister(sv[0]);	//If Region name exists
		if (ex >= 0) {
			std::cerr << "Name Conflict: Local Region:" << sv[0] << " exists.\n";
			return (-1);
		}

		ex = inGRegister(sv[0]);
		if (ex >= 0) {		//If GRegion exists
			int reg = 0;
			std::vector<std::string> rv = pstring::lex(sv[1], ',');
			for (ind j = 0; j < rv.size(); ++j) {
				if (pstring::ifind(rv[j],":")) {		//range of regions
					//TODO
				}
				else {									//singular region
					int pos = inRegister(rv[j]);
					if (pos >= 0) {		//Region exists
						if (inGRegion(rv[j], &GRegister_GlobalRegions[ex]) == (-1)) {	//If region not already in Group
							GRegister_GlobalRegions[ex].regions.push_back(&(GRegister_Regions[pos]));
							++reg;
						}
					}
					else {				//Region does not exist
						std::cerr << "Region:" << rv[j] << " does not exist.\n";
					}
				}
				
			}

			if (reg > 0) {	//Verify something was added
				return ex;
			}
			else {	//Nothing changed
				return (-1);
			}
		}
		else {				//Else Create new GRegion
			gregion y;
			y.name = sv[0];
			int reg = 0, pos = -1;
			std::vector<std::string> rv = pstring::lex(sv[1], ',');
			for (ind j = 0; j < rv.size(); ++j) {
				pos = inRegister(rv[j]);
				if (pos >= 0) {	//If rgn exists
					if (inGRegion(rv[j], &y) == (-1)) { //If rgn not already in group
						y.regions.push_back(&(GRegister_Regions[pos]));
						++reg;
					}
				}
				else {
					if (pstring::isWholeNumber(rv[j])) {
						pos = inRegister(std::stoi(rv[j]));
						if (pos >= 0) {
							if (inGRegion(rv[j], &y) == (-1)) { //If rgn not already in group
								y.regions.push_back(&(GRegister_Regions[pos]));
								++reg;
							}
						}
						else {
							std::cerr << "Region_ID:" << rv[j] << " does not exist.\n";
						}
					}
					else {
						std::cerr << "Region:" << rv[j] << " does not exist.\n";
					}
				}
			}
			if (reg > 0) {	//If regions successfully added
				GRegister_GlobalRegions.push_back(y);
				return static_cast<int>(GRegister_GlobalRegions.size() - 1);
			}
			else {
				std::cerr << "GRegion NOT created, parameters contain no valid regions.\n";
				return (-1);
			}
		}
	}

	bool setRgn(const std::vector<std::string>& parm) {
		int pos = inRegister(parm[1]);
		ind ar = parm.size();
		if (pos >= 0) {			//Add parameters to RGN that already exists
			for (ind i = 2; i < ar; ++i) {
				setProperties(parm[i], &GRegister_Regions[pos]);
			}
			return true;
		}
		else {
			if (pstring::isWholeNumber(parm[1])) {
				pos = inRegister(std::stoi(parm[1]));
			}
			if (pos >= 0) {		//Add parameters to RGN that already exists
				for (ind i = 2; i < ar; ++i) {
					setProperties(parm[i], &GRegister_Regions[pos]);
				}
				return true;
			}
			else {
				int posG = inGRegister(parm[1]);	//search for GRegion by name
				if (posG >= 0) {		//Add parameters to GROUP region
					for (ind i = 0; i < GRegister_GlobalRegions[posG].regions.size(); ++i) {
						pos = inRegister(GRegister_GlobalRegions[posG].regions[i]->name);
						for (ind j = 2; j < ar; ++j) {
							setProperties(parm[j], &GRegister_Regions[pos]);
						}
					}
					return true;
				}
				else {		//no region found
					std::cerr << "No Region/GRegion:" << parm[1] << " found." << std::endl;
					return false;
				}
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
				if (GRegister_Regions[i].identifier.range > 0) {
					ret += std::to_string(GRegister_Regions[i].identifier.first) + ":";
					ret += std::to_string(GRegister_Regions[i].identifier.last) + "\t\t";
				}
				else {
					ret += std::to_string(GRegister_Regions[i].identifier.first) + "\t\t";
				}
				
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
					ret += "TDISC:" + GRegister_Regions[i].temp_disc.value + " ";
				if (GRegister_Regions[i].tconv.exists)
					ret += "TinfCONV:" + GRegister_Regions[i].tconv.value + " ";
				if (GRegister_Regions[i].trad.exists)
					ret += "TinfRAD:" + GRegister_Regions[i].trad.value + " ";
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
		ind si = GRegister_GlobalRegions.size();
		std::string ret = std::to_string(si);
		if (si > 0) {
			ret += " GLOBAL_REGIONS:\n";
			for (ind i = 0; i < si; ++i) {
				ret += GRegister_GlobalRegions[i].name;
				ret += "\tREGIONS:";
				for (ind j = 0; j < GRegister_GlobalRegions[i].regions.size(); ++j) {
					if (!GRegister_GlobalRegions[i].regions[j]->name.empty()) {
						ret += GRegister_GlobalRegions[i].regions[j]->name;
						ret += ", ";
					}
					else {
						if (GRegister_GlobalRegions[i].regions[j]->identifier.range > 0) {
							ret += GRegister_GlobalRegions[i].regions[j]->identifier.first + ":";
							ret += GRegister_GlobalRegions[i].regions[j]->identifier.last;
						}
						else {
							ret += GRegister_GlobalRegions[i].regions[j]->identifier.first;
						}
						ret += ", ";
					}
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

	int inRegister(const std::string& name) {
		for (ind i = 0; i < GRegister_Regions.size(); ++i) {
			if (pstring::icompare(name, GRegister_Regions[i].name)) {
				return static_cast<int>(i);
			}
		}
		return (-1);
	}

	int inRegister(const int& id) {
		for (ind i = 0; i < GRegister_Regions.size(); ++i) {
			if (GRegister_Regions[i].identifier.range == 0) {
				if (id == GRegister_Regions[i].identifier.first) {
					return static_cast<int>(i);
				}
			}
			else {
				if (id > GRegister_Regions[i].identifier.first && id <= GRegister_Regions[i].identifier.last) {
					return static_cast<int>(i);
				}
			}
		}
		return (-1);
	}

	int inGRegister(const std::string& id) {
		for (ind i = 0; i < GRegister_GlobalRegions.size(); ++i) {
			if (pstring::icompare(id, GRegister_GlobalRegions[i].name)) {
				return static_cast<int>(i);
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
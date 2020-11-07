#include "proxGmsh.h"
#include "proxStrings.h"
#include "proxFiles.h"
#include "../region.h"
#include "../external/include/gmsh.h"
#include "../gobjects/gobject.h"
#include <sstream>
#include <iostream>

namespace pgmsh {

	bool gmshUI;
	bool gmshUIupdate;
	size_t GFlagOpen;
	std::vector<std::string> GVecModelList;
	std::vector<std::string> GFileList;

	void init() {
		gmshUI = 0;
		gmshUIupdate = false;
		GFlagOpen = 0;
		GVecModelList.clear();
		GFileList.clear();
	}

	int readGeoFile(const std::string& gfilename) {
		gmsh::initialize();
		gmsh::onelab::run();
		gmsh::option::setNumber("General.Terminal", 1);
		try
		{
			gmsh::open(gfilename);
			gmsh::model::list(GVecModelList);
			GFlagOpen = GVecModelList.size();
			GFileList.push_back(gfilename);
		}
		catch (int ierr)
		{
			std::cerr << "readGeoFile::ierr:" << ierr << std::endl;
			return ierr;
		}
		return 0;
	}

	void close() {
		if (GFlagOpen > 0) {
			gmsh::onelab::clear();
			gmsh::finalize();
		}
		init();
	}

	bool validate(const std::vector<std::string>& parm) {
		if (parm.size() > 1) {
			if (GFlagOpen > 0) {
				for (ind i = 1; i < parm.size(); ++i) {
					if (pstring::icompare(parm[i], gmshParameters[0])) {		//READ
						readGeoFile(parm[i+1]);
					}
					else if (pstring::icompare(parm[i],gmshParameters[1])) {	//LOAD
						loadRegions();
					}
					else if (pstring::icompare(parm[i], gmshParameters[2])) {	//LIST
						listPhysicalGroups();
					}
					else if (pstring::icompare(parm[i], gmshParameters[3])) {	//GUI
						openInterface();
					}
					else if (pstring::icompare(parm[i], gmshParameters[4])) {	//CLEAR
						close();
					}
					else if (pstring::icompare(parm[i], gmshParameters[5])) {	//GET
						if (parm.size() > i+1) {
							std::cout << onelabGet(parm[i + 1]) << std::endl;
							++i;
						}
						else {
							std::cout << onelabGet("") << std::endl;
						}
					}
					else if (pstring::icompare(parm[i], gmshParameters[6])) {	//SET
						if (parm.size() > i + 1) {
							std::vector<std::string> str = pstring::lex(parm[i+1],'=');
							std::vector<std::string> val = pstring::lex(str[1], ',');
							if (onelabSet(str[0],val)) {
								std::cout << "ONELAB SET:" << str[0] << " VAL:" << str[1] << std::endl;
							}
							else {
								std::cerr << "SET Failed, variable NAME:" << str[0];
								std::cerr << " does not exist." << std::endl;
							}
							++i;
						}
						else {
							std::cerr << "Missing SET parameter:";
						}
					}
					else if (pstring::icompare(parm[i], gmshParameters[7])) {	//BOUND
						std::cout << "ID:" << parm[i+1] << "&" << parm[i+2] << ":\n";
						gmsh::vectorpair vpin,vpout;
						std::pair<int, int> sp;
						sp.first = std::stoi(parm[i + 1]);
						sp.second = std::stoi(parm[i + 2]);
						vpin.push_back(sp);
						std::vector<int> vi;
						gmsh::model::getBoundary(vpin,vpout,false);
						for (ind j = 0; j < vpout.size(); ++j) {
							std::cout << "i:" << j << " ";
							std::cout << "1st:" << vpout[j].first;
							std::cout << " 2nd:" << vpout[j].second;
							gmsh::model::getPhysicalGroupsForEntity(vpout[j].first,vpout[j].second,vi);
							if (!vi.empty()) {
								std::cout << " PG::" ;
								for (ind k = 0; k < vi.size(); ++k) {
									std::cout << k << ":" << vi[k] << ",";
								}
								vi.clear();
							}
							std::cout << "\n";
						}
					}
					else if (pstring::icompare(parm[i], gmshParameters[8])) {	//MESH
						if (!parm[i + 1].empty()) {
							mesh(parm[i + 1]);
							++i;
						}
						else {
							std::cerr << "MESH failed, filename not specified;";
						}
					}
					else {
						std::cerr << "Unknown GMSH arg: " << parm[i] << ".\n";
					}
				}
				return true;
			}
			else if (pstring::icompare(parm[1], gmshParameters[0])) {	
				readGeoFile(parm[2]);
				return true;
			}
			else {
				std::cerr << "No GMSH file loaded.\n";
				return false;
			}
		}
		else {
			std::cerr << "Not enough Parameters. See HELP GMSH for correct usage.\n";
			return false;
		}
	}

	void listPhysicalGroups() {
		gmsh::vectorpair p;
		
		for (ind j = 0; j < GVecModelList.size(); ++j) {
			gmsh::model::setCurrent(GVecModelList[j]);
			gmsh::model::getPhysicalGroups(p);
			std::cout << "GMSH Model:" << GVecModelList[j] << "\nPhysical_Groups:\n";
			//Print Vpair

			for (ind i = 0; i < p.size(); ++i) {
				std::cout << "DIM:" << p[i].first;
				std::cout << ", ID:" << p[i].second;
				std::string str;
				gmsh::model::getPhysicalName(p[i].first, p[i].second, str);
				std::cout << ", Name:" << str;
				std::cout << "\n";
			}
			std::cout << std::endl;

		}

	}

	void loadRegions() {
		std::cout << GFlagOpen << " MODELS:\n";
		for (ind j = 0; j < GFlagOpen; ++j) {
			gmsh::model::setCurrent(GVecModelList[j]);
			std::cout << "M(" << j << ")=" << GVecModelList[j] << ":\n";
			gmsh::vectorpair p;
			gmsh::model::getPhysicalGroups(p);

			for (ind i = 0; i < p.size(); ++i) {
				regions::region r;
				r.dimension.exists = true;
				r.dimension.value = std::to_string(p[i].first);
				r.identifier.first = p[i].second;
				gmsh::model::getPhysicalName(p[i].first, p[i].second, r.name);

				std::cout << "\n";
				if (r.name.empty() || pstring::isWholeNumber(r.name)) {//create name for region
					if (p[i].first == 0) {
						r.name = "p" + std::to_string(r.identifier.first);
					}
					else if (p[i].first == 1) {
						r.name = "lin" + std::to_string(r.identifier.first);
					}
					else if (p[i].first == 2) {
						r.name = "sur" + std::to_string(r.identifier.first);
					}
					else {
						r.name = "vol" + std::to_string(r.identifier.first);
					}
					GRegister_Regions.push_back(r);
				}
				else {	//add named GMSH regions to register
					GRegister_Regions.push_back(r);
				}

				std::cout << "RGN ADD: Name:" << r.name;
				std::cout << ", DIM:" << r.dimension.value;
				std::cout << ", ID:" << r.identifier.first;
			}
			std::cout << std::endl << "MODEL:" << GVecModelList[j] << ":";
			std::cout << "[" << (p.size()) << "] GMSH Regions Added." << std::endl;
		}
	}

	void openInterface() {
		std::string arg;
		ind files = GFileList.size();
		if (files > 0) {
			for (ind i = 0; i < files; ++i) {
				arg += GFileList[i];
				arg += " ";
			}
			std::cout << "Opening GMSH interface: " << arg << "\n";
			gmshUI = 1;
		}
		else {
			std::cerr << "No GMSH files loaded.\n";
			std::cout << "Opening GMSH:\n";
			gmshUI = 1;
		}
	}

	std::string onelabGet(const std::string& name) {
		std::string data;
		std::string format = "json";
		std::vector<double> bdubz;
		std::vector<std::string> bstr;
		bdubz.push_back(0.0);
		if (name.empty()) {							//Return ALL OneLAB data
			gmsh::onelab::get(data);
		}
		else {										//Return NUMBER or STRING data
			gmsh::onelab::getNumber(name, bdubz);
			if (!bdubz.empty()) {
				data = "NUM:" + name;
				for (ind i = 0; i < bdubz.size(); ++i) {
					data += "<" + i;
					data += ">" + std::to_string(bdubz[i]);
				}
			}
			else {
				gmsh::onelab::getString(name, bstr);
				if (!bstr.empty()) {
					data = "STR:" + name;
					for (ind i = 0; i < bdubz.size(); ++i) {
						data += "<" + i;
						data += ">" + bstr[i];
					}
				}
				else {
					data = "No ONELAB variable found with name:" + name;
				}
			}
		}
		return data;
	}

	bool onelabSet(const std::string& name,const std::vector<std::string>& val) {
		std::string oget = onelabGet(name);
		if (pstring::find(oget,"NUM:")) {
			std::vector<double> bdubz;
			for (ind i = 0; i < val.size(); ++i) {
				bdubz.push_back(std::stod(val[i]));
			}
			gmsh::onelab::setNumber(name,bdubz);
			gmshUIupdate = true;
			reloadGeoFile();
			return true;
		}
		else if (pstring::find(name,"STR:")) {
			gmsh::onelab::setString(name,val);
			gmshUIupdate = true;
			reloadGeoFile();
			return true;
		}
		else {
			return false;
		}
	}

	int reloadGeoFile(const int fileID) {
		std::string gfilename = GFileList[fileID];
		try
		{	
			//flush old data
			gmsh::clear();
			
			regions::clearRegion();
			regions::clearGlobalRegion();

			gobject::clearGlobalArrays();

			//load new gmsh data & regions
			gmsh::open(gfilename);
			loadRegions();
		}
		catch (int ierr)
		{
			std::cerr << "readGeoFile::ierr:" << ierr << std::endl;
			return ierr;
		}
		return 0;
	}

	std::vector<int> getPSursForPVol(const int volID) {
		std::vector<int> vout,vvol;
		gmsh::vectorpair vpin, vpout;
		std::pair<int, int> sp;
		
		gmsh::model::getEntitiesForPhysicalGroup(3, volID, vvol);
		ind vols = vvol.size();
		if (vols > 0) {
			for (ind i = 0; i < vols; ++i) {
				//std::cout << "vvol:" << i << ":" << vvol[i] << "\n"; //TEST
				sp.first = 3;
				sp.second = vvol[i];
				vpin.push_back(sp);
			}
		}
		else {
			std::cerr << "GetEntities_ERROR: Returned no entities for PHysical Group:" << volID << "\n";
		}

		gmsh::model::getBoundary(vpin, vpout);
		/*ind bounds = vpout.size();	//TEST getBoundary entities
		if (bounds > 0) {
			for (ind i = 0; i < bounds; ++i) {
				std::cout << "vpout:" << i << ":" << vpout[i].first << ":" << vpout[i].second << "\n";
			}
		}
		else {
			std::cerr << "GetBoundary_ERROR: Returned no bounding entities\n";
		}*/

		gmsh::model::getPhysicalGroupsForEntity(2,vpout[0].second,vout);
		/*ind ptags = vout.size();		//TEST getPhysicalGroups for entities
		if (ptags > 0) {
			for (ind i = 0; i < ptags; ++i) {
				std::cout << "vout:" << i << ":" << vout[i] << "\n";
			}
		}
		else {
			std::cerr << "GetPGroups_ERROR: Returned no physical groups for entity:" << vpout[0].second << "\n";
		}*/
		return vout;
	}

	std::string createPSurFromPVol(const int volID) {
		std::string surID;
		std::vector<int> vi;
		gmsh::model::getEntitiesForPhysicalGroup(3, volID, vi);
		if (vi.empty()) {
			std::cerr << "GetEntities_ERROR: Returned no entities for Physical Group:" << volID << "\n";
			return "";
		}
		else {
			gmsh::vectorpair vpin, vpout;
			std::pair<int, int> sp;
			sp.first = 3;
			sp.second = vi[0];
			vpin.push_back(sp);
			gmsh::model::getBoundary(vpin, vpout);

			int rgnID = regions::inRegister(std::to_string(volID));
			regions::region rgn = GRegister_Regions[rgnID];
			int id = gmsh::model::addPhysicalGroup(2, {vpout[0].second});
			surID = rgn.name + "_PSUR" + std::to_string(id);
			gmsh::model::setPhysicalName(2, { id }, surID);

			//add region
			
			std::vector<std::string> vs;
			vs.push_back("RGN");
			vs.push_back(rgn.name + "_PSUR" + std::to_string(id) + "=" + std::to_string(id));
			if (rgn.conduction.exists) {
				vs.push_back("COND=" + rgn.conduction.value);
			}

			regions::addRgn(vs);

			//Group Definition
			std::ostringstream def;
			def << rgn.name << "_PSUR" << id << " = ";
			def << "Region[{" << id << "}]";
			GArr_Groups.push_back(def.str());

			return surID;
		}
	}

	std::string getPName(const int pDim, const int pTag) {
		std::string name;
		gmsh::model::getPhysicalName(pDim,pTag,name);
		return name;
	}

	int getDimension(const int iD) {
		gmsh::vectorpair vp;
		gmsh::model::getPhysicalGroups(vp);
		for (ind i = 0; i < vp.size(); ++i) {
			if (iD == vp[i].second) {
				return vp[i].first;
			}
		}
		return 1;
	}

	void clearModel(const int model, const std::string& name) {
		if (model >= 0) {
			gmsh::model::setCurrent(GVecModelList[model]);
			gmsh::model::remove();
			std::cout << "cleared MODEL:" << model << ":" << GVecModelList[model] << std::endl;
		}
		else if (!name.empty()) {
			gmsh::model::setCurrent(name);
			gmsh::model::remove();
			std::cout << "cleared MODEL:" << name << std::endl;
		}
		else {
			std::vector<std::string> modnames;
			gmsh::model::list(modnames);
			for (ind i = 0; i < modnames.size(); ++i) {
				gmsh::model::setCurrent(modnames[i]);
				gmsh::model::remove();
				std::cout << "cleared MODEL:" << i << ":" << modnames[i] << std::endl;
			}
		}
	}

	void mesh(const std::string& filename, int modelID) {
		int d;
		if (modelID >= 0) {
			gmsh::model::setCurrent(GVecModelList[modelID]);
			d = gmsh::model::getDimension();
		}
		else {
			d = gmsh::model::getDimension();
		}
		gmsh::model::geo::synchronize();
		gmsh::model::mesh::generate(d);
		gmsh::write(filename);
	}

	bool runGetDP(const std::vector<std::string>& args) {
		std::string argstr;
		for (ind i = 0; i < args.size(); ++i) {
			if (pstring::icompare(args[i], getDPParameters[0])) {
				//TODO
			}
			else {
				argstr += args[i];
				argstr += " ";
			}
		}
		if (pfile::run(getdpfilepath, argstr) > 0) {
			return false;
		}
		else {
			return true;
		}
	}

}//end namespace pgmsh


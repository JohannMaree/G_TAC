#include "proxGmsh.h"
#include "proxStrings.h"
#include "proxFiles.h"
#include "../external/include/gmsh.h"
#include "../region.h"

#include <iostream>

namespace pgmsh {

	size_t GFlagOpen;
	std::vector<std::string> GVecModelList;
	std::vector<std::string> GFileList;

	void init() {
		GFlagOpen = 0;
		GVecModelList.clear();
		GFileList.clear();
	}

	int readGeoFile(const std::string& gfilename) {
		gmsh::initialize();
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
			std::cerr << "gmshOpen::ierr" << ierr << std::endl;
			return ierr;
		}
		return 0;
	}

	void close() {
		if (GFlagOpen > 0) {
			gmsh::finalize();
		}
		init();
	}

	int getRgnDim(int id) {
		return gmshModelGetDimension(&(id));
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
					else if (pstring::icompare(parm[i], gmshParameters[3])) {	//RUN
						openInterface();
					}
					else if (pstring::icompare(parm[i], gmshParameters[4])) {	//CLEAR
						close();
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
		gmsh::model::getPhysicalGroups(p);
		
		for (ind j = 0; j < GFlagOpen; ++j) {
			gmsh::model::setCurrent(GVecModelList[j]);
			std::cout << "GMSH Model: " << GVecModelList[j] << ", Physical_Groups:\n";
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
		gmsh::vectorpair p;
		gmsh::model::getPhysicalGroups(p);

		std::cout << GFlagOpen << " MODELS:\n";
		for (ind j = 0; j < GFlagOpen; ++j) {
			gmsh::model::setCurrent(GVecModelList[j]);
			std::cout << "M(" << j << ")=" << GVecModelList[j] << ":\n";

			for (ind i = 0; i < p.size(); ++i) {
				regions::region r;
				r.dimension.exists = true;
				r.dimension.value = std::to_string(p[i].first);
				r.identifier = std::to_string(p[i].second);
				gmsh::model::getPhysicalName(p[i].first, p[i].second, r.name);

				std::cout << "RGN ADD: Name:" << r.name;
				std::cout << ", DIM:" << r.dimension.value;
				std::cout << ", ID:" << r.identifier;

				std::cout << "\n";
				GRegister_Regions.push_back(r);
			}

			std::cout << std::endl;
		}

		std::cout << (p.size()) << " GMSH Regions Added." << std::endl;
	}

	void openInterface() {
		std::string arg;
		ind files = GFileList.size();
		if (files > 0) {
			for (ind i = 0; i < files; ++i) {
				arg += GFileList[i];
				arg += " ";
			}
			pfile::run(gmshfilepath, arg);
			std::cout << "Opening GMSH interface: " << arg << "\n";
		}
		else {
			std::cerr << "No GMSH files loaded.\n";
			std::cout << "Opening GMSH:\n";
			pfile::run(gmshfilepath, "");
		}
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


#include "compile.h"
#include "variable.h"
#include "region.h"
#include "gobject.h"
#include "proxStrings.h"
#include "proxFiles.h"
#include "generate.h"

#include <sstream>
#include <memory>
#include <iostream> //TEST

//AutoGen Global Group entities
std::string groupCOND;
std::string groupCONV;
std::string groupRAD;
std::string groupGEN;
std::string groupFLUX;
std::string groupTEMP;

std::string groupALL;

namespace compile {

	void validate(const std::vector<std::string>& parm) {
		defaults(parm[1]);
	}

	void defaults(const std::string& filename) {

		openGlobalGroups();
		compileFromRegions();
		closeGlobalGroups();

		//Default Calls
		int fsp = gobject::defaultFunctionSpace();
		gobject::defaultJacobian();
		gobject::defaultIntegration();

		int fpos = gobject::defaultFormulation(fsp);
		
		gobject::defaultResolution(fpos);
		int ppos = gobject::defaultPostProcessing(fpos);
		gobject::defaultPostOperation(ppos);

		writeASCII(filename);
		std::cout << "completed generating .pro FILE:" << filename << "\n";//TEST
	}

	void writeASCII(const std::string& filename) {
		//Clear File if exist
		pfile::clear(filename);

		//Write GObjects to ASCII file
		pfile::write(filename, generate::globals());

		pfile::write(filename, generate::group());
		pfile::write(filename, generate::function());
		pfile::write(filename, generate::constraint());

		pfile::write(filename, generate::functionspace());
		pfile::write(filename, generate::jacobian());
		pfile::write(filename, generate::integration());

		pfile::write(filename, generate::formulation());
		pfile::write(filename, generate::resolution());
		pfile::write(filename, generate::postprocessing());
		pfile::write(filename, generate::postoperation());

	}

	void compileFromRegions() {

		for (ind i = 0; i < GRegister_Regions.size(); ++i) {
			std::ostringstream def;

			//Group Definition
			def << GRegister_Regions[i].name << " = ";
			def << "Region[" << GRegister_Regions[i].identifier << "]";
			GArr_Groups.push_back(def.str());

			//Function Defintions
			if (GRegister_Regions[i].conduction.exists) {		//Conduction Function
				std::ostringstream func;
				func << gobject::sVarConduction << "[";
				func << GRegister_Regions[i].name;
				func << "] = ";
				func << GRegister_Regions[i].conduction.value;
				GArr_Functions.push_back(func.str());
				//Add region to conduction group
				groupCOND += GRegister_Regions[i].name + ",";
				gobject::GFlagConduction = true;
			}

			if (GRegister_Regions[i].convection.exists) {		//Convection Function
				std::ostringstream func;
				func << gobject::sVarConvection << "[";
				func << GRegister_Regions[i].name;
				func << "] = ";
				func << GRegister_Regions[i].convection.value;
				GArr_Functions.push_back(func.str());
				//Add region to convection group
				groupCONV += GRegister_Regions[i].name + ",";
				gobject::GFlagConvection = true;
			}

			if (GRegister_Regions[i].radiation.exists) {		//Radiation Function
				std::ostringstream func;
				func << gobject::sVarRadiation << "[";
				func << GRegister_Regions[i].name;
				func << "] = ";
				func << GRegister_Regions[i].radiation.value;
				GArr_Functions.push_back(func.str());
				//Add region to radiation group
				groupRAD += GRegister_Regions[i].name + ",";
				gobject::GFlagRadiation = true;
			}

			if (GRegister_Regions[i].generation.exists) {		//Generation Function
				std::ostringstream func;
				func << gobject::sVarGeneration << "[";
				func << GRegister_Regions[i].name;
				func << "] = ";
				func << GRegister_Regions[i].generation.value;
				GArr_Functions.push_back(func.str());
				//Add region to generation group
				groupGEN += GRegister_Regions[i].name + ",";
				gobject::GFlagGeneration = true;
			}


			//Constraint Definitions
			if (GRegister_Regions[i].bcType1.exists) {			//Dirichlet BoundaryCondition
				gobject::Constraint c;
				c.Name = gobject::sVarTempConstraint;
				c.Type = "Assign";

				gobject::cCase cs;
				cs.Region = GRegister_Regions[i].name;
				cs.Value = GRegister_Regions[i].bcType1.value;
				c.Cases.push_back(cs);

				gobject::addConstraint(c);
				//Add region to temp group
				groupTEMP += GRegister_Regions[i].name + ",";
				gobject::GFlagTemperature = true;
			}

			if (GRegister_Regions[i].bcType2.exists) {			//Neumann BoundaryCondition
				std::ostringstream func;
				func << gobject::sVarHeatFlux << "[";
				func << GRegister_Regions[i].name << "] = ";
				func << GRegister_Regions[i].bcType2.value;
				GArr_Functions.push_back(func.str());
				//Add region to flux group
				groupFLUX += GRegister_Regions[i].name + ",";
				gobject::GFlagHeatFlux = true;
			}


		}

	}

	void openGlobalGroups() {
		groupCOND = gobject::sGroupConduction + " = Region[{";
		groupCONV = gobject::sGroupConvection + " = Region[{";
		groupRAD = gobject::sGroupRadiation + " = Region[{";
		groupGEN = gobject::sGroupGeneration + " = Region[{";
		groupFLUX = gobject::sGroupHeatFlux + " = Region[{";
		groupTEMP = gobject::sGroupTemperature + " = Region[{";

		groupALL = gobject::TDomain + " = Region[{";
	}

	void closeGlobalGroups() {

		if (gobject::GFlagConduction) {
			groupCOND.pop_back();
			groupCOND += "}]";

			GArr_Groups.push_back(groupCOND);
			groupALL += gobject::sGroupConduction + ",";
		}
		if (gobject::GFlagConvection) {
			groupCONV.pop_back();
			groupCONV += "}]";

			GArr_Groups.push_back(groupCONV);
			groupALL += gobject::sGroupConvection + ",";
		}
		if (gobject::GFlagRadiation) {
			groupRAD.pop_back();
			groupRAD += "}]";

			GArr_Groups.push_back(groupRAD);
			groupALL += gobject::sGroupRadiation + ",";
		}
		if (gobject::GFlagGeneration) {
			groupGEN.pop_back();
			groupGEN += "}]";

			GArr_Groups.push_back(groupGEN);
			groupALL += gobject::sGroupGeneration + ",";
		}
		if (gobject::GFlagHeatFlux) {
			groupFLUX.pop_back();
			groupFLUX += "}]";

			GArr_Groups.push_back(groupFLUX);
			groupALL += gobject::sGroupHeatFlux + ",";
		}
		if (gobject::GFlagTemperature) {
			groupTEMP.pop_back();
			groupTEMP += "}]";

			GArr_Groups.push_back(groupTEMP);
			groupALL += gobject::sGroupTemperature + ",";
		}

		groupALL.pop_back();
		groupALL += "}]";
		GArr_Groups.push_back(groupALL);
	}

}

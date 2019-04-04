#include "compile.h"
#include "variable.h"

#include "gobjects/gobject.h"
#include "io/proxStrings.h"
#include "io/proxFiles.h"
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
std::string groupDISC;
std::string groupNL_COND;

std::string groupALL;

namespace compile {

	bool validate(const std::vector<std::string>& parm) {
		if (parm.size() > 1) {
			//Ensure Extension is correct
			std::string fname = parm[1];
			if (pstring::checkExtension(fname, "pro")) {
				defaults(fname);
				return true;
			}
			else {
				fname += ".pro";
				defaults(fname);
				return true;
			}
		}
		else {
			std::cerr << "COMPILE error: Not enough parameters specified.\n";
			return false;
		}
	}

	void createNL_Variables(int type) {
		std::vector <std::string> pass;
		if (type == 0) {
			pass.push_back("VAR");
		}
		else {
			pass.push_back("IVAR");
		}
		pass.push_back("#PLACEHOLDER=#VALUE");
		pass.push_back("MENU=" + gobject::sVarNL_submenu);

		if (variables::inRegister(gobject::sVarNL_eps) < 0) {
			pass[1] = gobject::sVarNL_eps + "=" + gobject::varNL_eps.sval;
			variables::validate(pass, -1);
		}
		if (variables::inRegister(gobject::sVarNL_rel) < 0) {
			pass[1] = gobject::sVarNL_rel + "=" + gobject::varNL_rel.sval;
			variables::validate(pass, -1);
		}
		if (variables::inRegister(gobject::sVarNL_maxloop) < 0) {
			pass[1] = gobject::sVarNL_maxloop + "=" + std::to_string(gobject::varNL_maxloop);
			variables::validate(pass, -1);
		}
	}

	void defaults(const std::string& filename) {

		//Register System flags
		regionPreCompile();

		//Open groups for additive info
		openGlobalGroups();

		//Default General Calls
		int fsp = gobject::defaultFunctionSpace();
		gobject::defaultJacobian();
		gobject::defaultIntegration();

		int fpos = gobject::defaultFormulation(fsp);
		
		gobject::defaultResolution(fpos);
		int ppos = gobject::defaultPostProcessing(fpos);
		gobject::defaultPostOperation(ppos);

		//Conditional Calls
		if (gobject::GFlagNL_Conduction) {
			createNL_Variables();
		}

		//Specific Region Calls
		compileFromRegions();

		//Close open groups
		closeGlobalGroups();

		writeASCII(filename);
		std::cout << "FILE:" << filename << " generated succesfully.\n";
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

			//Group Definition
			std::ostringstream def;
			def << GRegister_Regions[i].name << " = ";
			def << "Region[" << GRegister_Regions[i].identifier << "]";
			GArr_Groups.push_back(def.str());

			//Function Defintions
			if (GRegister_Regions[i].conduction.exists) {		//Conduction Function
				rgnConduction(GRegister_Regions[i]);
			}

			if (GRegister_Regions[i].convection.exists) {		//Convection Function
				rgnConvection(GRegister_Regions[i]);
			}

			if (GRegister_Regions[i].radiation.exists) {		//Radiation Function
				rgnRadiation(GRegister_Regions[i]);
			}

			if (GRegister_Regions[i].generation.exists) {		//Generation Function
				rgnGeneration(GRegister_Regions[i]);
			}

			//Constraint Definitions
			if (GRegister_Regions[i].temperature.exists) {		//Dirichlet Boundary Condition
				rgnTemperature(GRegister_Regions[i]);
			}

			if (GRegister_Regions[i].heatflux.exists) {			//Neumann Boundary Condition
				rgnHeatflux(GRegister_Regions[i]);
			}

			if (GRegister_Regions[i].temp_disc.exists) {		//Temperature Discontinuity
				rgnTempDisc(GRegister_Regions[i]);
			}

		}

	}

	void regionPreCompile() {
		for (ind i = 0; i < GRegister_Regions.size(); ++i) {

			//Set GFlags for gobject generation
			if (!gobject::GFlagConduction) {
				if (GRegister_Regions[i].conduction.exists) {
					gobject::GFlagConduction = true;
				}
			}
			if (!gobject::GFlagConvection) {
				if (GRegister_Regions[i].convection.exists) {
					gobject::GFlagConvection = true;
				}
			}
			if (!gobject::GFlagRadiation) {
				if (GRegister_Regions[i].radiation.exists) {
					gobject::GFlagRadiation = true;
				}
			}
			if (!gobject::GFlagGeneration) {
				if (GRegister_Regions[i].generation.exists) {
					gobject::GFlagGeneration = true;
				}
			}
			if (!gobject::GFlagTemperature) {
				if (GRegister_Regions[i].temperature.exists) {
					gobject::GFlagTemperature = true;
				}
			}
			if (!gobject::GFlagHeatFlux) {
				if (GRegister_Regions[i].heatflux.exists) {
					gobject::GFlagHeatFlux = true;
				}
			}
			if (!gobject::GFlagDiscontinuous) {
				if (GRegister_Regions[i].temp_disc.exists) {
					gobject::GFlagDiscontinuous = true;
				}
			}
			if (!gobject::GFlagNL_Conduction) {
				if (GRegister_Regions[i].conduction.exists) {
					int in = variables::inRegister(GRegister_Regions[i].conduction.value);
					if (in >= 0) {
						if (GRegister_Variables[in]->type == -1) {
							gobject::GFlagNL_Conduction = true;
						}
					}
				}
			}

		}
	}

	//Individual Entity Compilation Methods
	void rgnConduction(regions::region& rgn) {
		std::string val = rgn.conduction.value;
		int in = variables::inRegister(val);
		if (in >= 0) {//If Value is VAR
			std::ostringstream func;
			if (GRegister_Variables[in]->type == -1) {// Pair Interpolation Type
				func << gobject::sVarNL_Conduction << "[";
				func << rgn.name;
				func << "] = InterpolationLinear[$1]";
				func << "{List[" << val << "]}";
				GArr_Functions.push_back(func.str());


				//Add region to NL conduction group
				groupNL_COND += rgn.name + ",";
			}
			else {//Linear Type
				func << gobject::sVarConduction << "[";
				func << rgn.name;
				func << "] = ";
				func << val;
				GArr_Functions.push_back(func.str());
				//Add region to conduction group
				groupCOND += rgn.name + ",";
			}
		}
		else if (pstring::isNumber(val)) {//If Value is Number
			std::ostringstream func;
			func << gobject::sVarConduction << "[";
			func << rgn.name;
			func << "] = ";
			func << val;
			GArr_Functions.push_back(func.str());
			//Add region to conduction group
			groupCOND += rgn.name + ",";
		}
		else {
			std::cerr << "COMPILE ERROR: COND VAL:" << val << ", RGN:" << rgn.name << " conduction value not valid.\n";
		}
	}

	void rgnConvection(regions::region& rgn) {
		std::ostringstream func;
		func << gobject::sVarConvection << "[";
		func << rgn.name;
		func << "] = ";
		func << rgn.convection.value;
		GArr_Functions.push_back(func.str());
		
		if (rgn.tconv.exists) {
			func.str("");
			func << gobject::sVarConvTInf << "[";
			func << rgn.name;
			func << "] = ";
			func << rgn.tconv.value;
			GArr_Functions.push_back(func.str());
		}
		else {
			std::cerr << "COMPILE ERROR: CONV RGN:" << rgn.name << " missing TCONV value.\n";
		}

		//Add region to convection group
		groupCONV += rgn.name + ",";
	}

	void rgnRadiation(regions::region& rgn) {
		std::ostringstream func;
		func << gobject::sVarRadiation << "[";
		func << rgn.name;
		func << "] = ";
		func << rgn.radiation.value;
		GArr_Functions.push_back(func.str());

		if (rgn.trad.exists) {
			func.str("");
			func << gobject::sVarRadTInf << "[";
			func << rgn.name;
			func << "] = ";
			func << rgn.trad.value;
			GArr_Functions.push_back(func.str());
		}
		else {
			std::cerr << "COMPILE ERROR: RAD RGN:" << rgn.name << " missing TRAD value.\n";
		}

		//Add region to radiation group
		groupRAD += rgn.name + ",";
	}

	void rgnGeneration(regions::region& rgn) {
		std::ostringstream func;
		func << gobject::sVarGeneration << "[";
		func << rgn.name;
		func << "] = ";
		func << rgn.generation.value;
		GArr_Functions.push_back(func.str());
		//Add region to generation group
		groupGEN += rgn.name + ",";
	}

	void rgnTemperature(regions::region& rgn) {
		//Default to constraint addition

		//Add BC Type 1 COnstraint
		gobject::Constraint c;
		c.Name = gobject::sVarTempConstraint;
		c.Type = "Assign";

		gobject::cCase cs;
		cs.Region = rgn.name;
		cs.Value = rgn.temperature.value;
		c.Cases.push_back(cs);

		gobject::addConstraint(c);
		
		//Add FunctionSpace Constraint
		gobject::fsConstraint fsc;
		fsc.NameOfCoef = gobject::defBasisFunction;
		fsc.EntityType = "NodesOf";
		fsc.NameOfConstraint = c.Name;

		gobject::addToFunctionSpace(fsc);

		//Add region to temp group
		groupTEMP += rgn.name + ",";
	}

	void rgnHeatflux(regions::region& rgn) {
		std::ostringstream func;
		func << gobject::sVarHeatFlux << "[";
		func << rgn.name << "] = ";
		func << rgn.heatflux.value;
		GArr_Functions.push_back(func.str());
		//Add region to flux group
		groupFLUX += rgn.name + ",";
	}

	void rgnTempDisc(regions::region& rgn) {
		//S1: Add BC Type 1 Constraint Discontinuity
		gobject::Constraint c;
		c.Name = gobject::sVarTempDiscontinuity;
		c.Type = "Assign";

		gobject::cCase cs;
		cs.Region = rgn.name;
		cs.Value = rgn.temp_disc.value;
		c.Cases.push_back(cs);

		gobject::addConstraint(c);

		//S2: Add FunctionSpace, BasisFunction & Subspace
		gobject::FunctionSpace fs;
		fs.Name = gobject::defFunctionSpace;
		fs.Type = "Form0";

		gobject::fsBasisFunction dbf;
		dbf.Name = gobject::defBFName + "dc";
		dbf.NameOfCoef = gobject::charTdisc;
		dbf.Function = "BF_Node";
		dbf.Support = gobject::sGroupDiscontinuous;
		dbf.Entity = "NodesOf[" + gobject::sGroupDiscontinuous + "]";
		fs.BasisFunctions.push_back(dbf);

		//S3: Divide Domain into Two Spaces; Continuous & Discontinuous
		gobject::fsSubspace fsCon;
		fsCon.Name = gobject::sSpaceTCont;
		fsCon.NameOfBasisFunction = gobject::defBFName;
		fs.Subspaces.push_back(fsCon);

		gobject::fsSubspace fsDiscon;
		fsDiscon.Name = gobject::sSpaceTDisc;
		fsDiscon.NameOfBasisFunction = dbf.Name;
		fs.Subspaces.push_back(fsDiscon);

		gobject::fsConstraint fc;
		fc.NameOfCoef = dbf.NameOfCoef;
		fc.EntityType = "NodesOf";
		fc.NameOfConstraint = c.Name;
		fs.Constraints.push_back(fc);

		gobject::addFunctionSpace(fs);

		//S4: Add Formulation
		gobject::Formulation fm;
		fm.Name = gobject::defNameFormulation;
		fm.Type = gobject::defFormulationType;

		gobject::formQuantity fqc;
		fqc.Name = gobject::charTcont;
		fqc.Type = "Local";
		fqc.NameOfSpace = gobject::defFunctionSpace + "[";
		fqc.NameOfSpace += gobject::sSpaceTCont + "]";
		fm.Quantities.push_back(fqc);

		gobject::formQuantity fqd;
		fqd.Name = gobject::charTdisc;
		fqd.Type = "Local";
		fqd.NameOfSpace = gobject::defFunctionSpace + "[";
		fqd.NameOfSpace += gobject::sSpaceTDisc + "]";
		fm.Quantities.push_back(fqd);

		gobject::addFormulation(fm);

		//S5: Add PostProcessing
		gobject::PostProcessing pp;
		pp.Name = gobject::defNamePostProcess;
		pp.NameOfFormulation = gobject::defNameFormulation;
		
		gobject::postQuantity pqc;
		pqc.Name = gobject::charTcont;
		pqc.Term = "{" + gobject::charTcont + "}";
		pqc.Domain = gobject::TDomain;
		pqc.Jacobian = gobject::TJacobianVol;
		pp.Quantities.push_back(pqc);

		gobject::postQuantity pqd;
		pqd.Name = gobject::charTdisc;
		pqd.Term = "{" + gobject::charTdisc + "}";
		pqd.Domain = gobject::TDomain;
		pqd.Jacobian = gobject::TJacobianVol;
		pp.Quantities.push_back(pqd);

		gobject::addPostProcessing(pp);
		
		//S6: Add PostOperations
		gobject::PostOperation po;
		po.Name = gobject::defNamePostOperation;
		po.NameOfPostProcessing = gobject::defNamePostProcess;
		
		gobject::postOp poc;
		poc.OperationType = "Print";
		poc.OperationArgs.push_back(gobject::charTcont);
		poc.OperationArgs.push_back("OnElementsOf " + gobject::TDomain);
		poc.OperationArgs.push_back("File \"" + gobject::charTcontfile + "\"");
		po.Operations.push_back(poc);

		gobject::postOp pod;
		pod.OperationType = "Print";
		pod.OperationArgs.push_back(gobject::charTdisc);
		pod.OperationArgs.push_back("OnElementsOf " + gobject::sGroupDiscontinuous);
		pod.OperationArgs.push_back("File \"" + gobject::charTdiscfile + "\"");
		po.Operations.push_back(pod);

		gobject::addPostOperation(po);

		//Add region to Discon group
		groupDISC += rgn.name + ",";
	}

	//Region Group definitions
	void openGlobalGroups() {
		//Establish System Flags
		if(gobject::GFlagConduction)
			groupCOND = gobject::sGroupConduction + " = Region[{";
		if (gobject::GFlagConvection)
			groupCONV = gobject::sGroupConvection + " = Region[{";
		if (gobject::GFlagRadiation)
			groupRAD = gobject::sGroupRadiation + " = Region[{";
		if (gobject::GFlagGeneration)
			groupGEN = gobject::sGroupGeneration + " = Region[{";
		if (gobject::GFlagHeatFlux)
			groupFLUX = gobject::sGroupHeatFlux + " = Region[{";
		if (gobject::GFlagTemperature)
			groupTEMP = gobject::sGroupTemperature + " = Region[{";
		if (gobject::GFlagDiscontinuous)
			groupDISC = gobject::sGroupDiscontinuous + " = Region[{";
		if (gobject::GFlagNL_Conduction)
			groupNL_COND = gobject::sGroupNL_Conduction + " = Region[{";

		groupALL = gobject::TDomain + " = Region[{";
	}

	void closeGlobalGroups() {
		GArr_Groups.push_back("");

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
		if (gobject::GFlagDiscontinuous) {
			groupDISC.pop_back();
			groupDISC += "}]";

			GArr_Groups.push_back(groupDISC);
			groupALL += gobject::sGroupDiscontinuous + ",";
		}
		if (gobject::GFlagNL_Conduction) {
			groupNL_COND.pop_back();
			groupNL_COND += "}]";

			GArr_Groups.push_back(groupNL_COND);
			groupALL += gobject::sGroupNL_Conduction + ",";
		}

		groupALL.pop_back();
		groupALL += "}]";
		GArr_Groups.push_back(groupALL);
	}

}//end namespace compile

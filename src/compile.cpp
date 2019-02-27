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

std::string groupALL;

namespace compile {

	void validate(const std::vector<std::string>& parm) {
		std::string fname = parm[1];
		std::string fext = fname.substr(fname.length() - 4, 3);
		//Ensure Extension is correct
		if (pstring::icompare(fext, "pro")) {
			defaults(fname);
		}
		else {
			fname += ".pro";
			defaults(fname);
		}
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
		std::cout << "GENERATED FILE:" << filename << "\n";//TEST
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
			if (GRegister_Regions[i].bcType1.exists) {			//Dirichlet BoundaryCondition
				rgnBCType1(GRegister_Regions[i]);
			}

			if (GRegister_Regions[i].bcType2.exists) {			//Neumann BoundaryCondition
				rgnBCType2(GRegister_Regions[i]);
			}

			//Temperature Discontinuity
			if (GRegister_Regions[i].temp_disc.exists) {		
				rgnTempDisc(GRegister_Regions[i]);
			}

		}

	}

	void rgnConduction(regions::region& rgn) {
		std::ostringstream func;
		func << gobject::sVarConduction << "[";
		func << rgn.name;
		func << "] = ";
		func << rgn.conduction.value;
		GArr_Functions.push_back(func.str());
		//Add region to conduction group
		groupCOND += rgn.name + ",";
		gobject::GFlagConduction = true;
	}

	void rgnConvection(regions::region& rgn) {
		std::ostringstream func;
		func << gobject::sVarConvection << "[";
		func << rgn.name;
		func << "] = ";
		func << rgn.convection.value;
		GArr_Functions.push_back(func.str());
		//Add region to convection group
		groupCONV += rgn.name + ",";
		gobject::GFlagConvection = true;
	}

	void rgnRadiation(regions::region& rgn) {
		std::ostringstream func;
		func << gobject::sVarRadiation << "[";
		func << rgn.name;
		func << "] = ";
		func << rgn.radiation.value;
		GArr_Functions.push_back(func.str());
		//Add region to radiation group
		groupRAD += rgn.name + ",";
		gobject::GFlagRadiation = true;
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
		gobject::GFlagGeneration = true;
	}

	void rgnBCType1(regions::region& rgn) {
		//Add BC Type 1 COnstraint
		gobject::Constraint c;
		c.Name = gobject::sVarTempConstraint;
		c.Type = "Assign";

		gobject::cCase cs;
		cs.Region = rgn.name;
		cs.Value = rgn.bcType1.value;
		c.Cases.push_back(cs);

		gobject::addConstraint(c);
		//Add region to temp group
		groupTEMP += rgn.name + ",";
		gobject::GFlagTemperature = true;
	}

	void rgnBCType2(regions::region& rgn) {
		std::ostringstream func;
		func << gobject::sVarHeatFlux << "[";
		func << rgn.name << "] = ";
		func << rgn.bcType2.value;
		GArr_Functions.push_back(func.str());
		//Add region to flux group
		groupFLUX += rgn.name + ",";
		gobject::GFlagHeatFlux = true;
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

		gobject::fsBasisFunction dbf;
		dbf.Name = gobject::sBasisFunctionDisc;
		dbf.NameOfCoef = gobject::charTdisc;
		dbf.Function = "BF_Node";
		dbf.Support = gobject::sGroupDiscontinuous;
		dbf.Entity = gobject::sGroupDiscontinuous;
		fs.BasisFunctions.push_back(dbf);

		//S3: Divide Domain into Two Spaces; Continuous & Discontinuous
		gobject::fsSubspace fsCon;
		fsCon.Name = gobject::sSpaceTCont;
		fsCon.NameOfBasisFunction = gobject::defBasisFunction;
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
		
		gobject::formQuantity fqc;
		fqc.Name = gobject::charTcont;
		fqc.Type = "Local";
		fqc.NameOfSpace = gobject::TDomain + "[";
		fqc.NameOfSpace += gobject::sSpaceTCont + "]";
		fm.Quantities.push_back(fqc);

		gobject::formQuantity fqd;
		fqd.Name = gobject::charTdisc;
		fqd.Type = "Local";
		fqd.NameOfSpace = gobject::TDomain + "[";
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
		poc.OperationArgs.push_back("File " + gobject::charTcontfile);
		po.Operations.push_back(poc);

		gobject::postOp pod;
		pod.OperationType = "Print";
		pod.OperationArgs.push_back(gobject::charTdisc);
		pod.OperationArgs.push_back("OnElementsOf " + gobject::sGroupDiscontinuous);
		pod.OperationArgs.push_back("File " + gobject::charTdiscfile);
		po.Operations.push_back(pod);

		gobject::addPostOperation(po);

		//Add region to Discon group
		groupDISC += rgn.name + ",";
		gobject::GFlagDiscontinuous = true;
	}

	void openGlobalGroups() {
		groupCOND = gobject::sGroupConduction + " = Region[{";
		groupCONV = gobject::sGroupConvection + " = Region[{";
		groupRAD = gobject::sGroupRadiation + " = Region[{";
		groupGEN = gobject::sGroupGeneration + " = Region[{";
		groupFLUX = gobject::sGroupHeatFlux + " = Region[{";
		groupTEMP = gobject::sGroupTemperature + " = Region[{";
		groupDISC = gobject::sGroupDiscontinuous + " = Region[{";

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
		if (gobject::GFlagDiscontinuous) {
			groupDISC.pop_back();
			groupDISC += "}]";

			GArr_Groups.push_back(groupDISC);
			groupALL += gobject::sGroupDiscontinuous + ",";

		}

		groupALL.pop_back();
		groupALL += "}]";
		GArr_Groups.push_back(groupALL);
	}

}

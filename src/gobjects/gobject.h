#pragma once
#include <string>
#include <vector>

#include "Constraint.h"
#include "FunctionSpace.h"
#include "Jacobian.h"
#include "Integration.h"
#include "Formulation.h"
#include "Resolution.h"
#include "PostProcessing.h"
#include "PostOperation.h"

#include "../io/proxStrings.h"

namespace gobject{

	struct edouble {
		double value;
		std::string sval;
	};
	
	//Global Variables
	extern std::string sVarConduction;
	extern std::string sGroupConduction;
	extern std::string sVarNL_Conduction;
	extern std::string sGroupNL_Conduction;

	extern std::string sVarConvection;
	extern std::string sVarConvTInf;
	extern std::string sGroupConvection;

	extern std::string sVarRadiation;
	extern std::string sVarRadTInf;
	extern std::string sGroupRadiation;

	extern std::string sVarGeneration;
	extern std::string sGroupGeneration;

	extern std::string sVarHeatFlux;
	extern std::string sGroupHeatFlux;

	extern std::string sVarTempConstraint;
	extern std::string sGroupTemperature;

	extern std::string sVarTempDiscontinuity;
	extern std::string sGroupDiscontinuous;
	extern std::string sSpaceTCont;
	extern std::string sSpaceTDisc;
	extern std::string sBasisFunctionDisc;
	extern std::string charTdisc;
	extern std::string charTcont;
	extern std::string charTdiscfile;
	extern std::string charTcontfile;

	extern std::string sVarNL_InitialRes;
	extern std::string sVarNL_Res;
	extern std::string sVarNL_Iter;
	extern std::string sVarNL_eps;
	extern std::string sVarNL_rel;
	extern std::string sVarNL_maxloop;
	extern std::string sVarNL_submenu;

	extern edouble varNL_eps;
	extern edouble varNL_rel;
	extern int varNL_maxloop;

	//Default Process Object Function Names
	extern std::string charT;
	extern std::string charQ;
	extern std::string charQgen;

	extern std::string charTfile;
	extern std::string charQfile;

	extern std::string defNamePostOperation;
	extern std::string defNamePostProcess;
	extern std::string defNameResolution;
	extern std::string defNameResSystem;
	extern std::string defNameResNLSystem;
	extern std::string defNameFormulation;
	extern std::string defFormulationType;
	extern std::string defFormEQType;
	extern std::string defFunctionSpace;
	extern std::string defBFName;
	extern std::string defBasisFunction;

	extern std::string TIntegration;
	extern std::string TJacobianVol;
	extern std::string TJacobianSur;
	extern std::string TDomain;

	//GetDP Flags
	extern bool GFlagConduction;
	extern bool GFlagConvection;
	extern bool GFlagRadiation;
	extern bool GFlagGeneration;
	extern bool GFlagHeatFlux;
	extern bool GFlagTemperature;
	extern bool GFlagDiscontinuous;
	extern bool GFlag3Dim;
	extern bool GFlagNL_Conduction;

	extern short int GFlagSysOrder;
	extern short int GFlagBFunctions;

	//Function Declarations
	void initGFlags();
	void clearGlobalArrays();

}//end namespace gobject

//GetDP Object GLobal Array Definitions
extern std::vector<std::string> GArr_Groups;
extern std::vector<std::string> GArr_Functions;

extern std::vector<gobject::Constraint> GArr_Constraints;
extern std::vector<gobject::FunctionSpace> GArr_FunctionSpaces;
extern std::vector<gobject::Jacobian> GArr_Jacobians;
extern std::vector<gobject::Integration> GArr_Integrations;
extern std::vector<gobject::Formulation> GArr_Formulations;
extern std::vector<gobject::Resolution> GArr_Resolutions;
extern std::vector<gobject::PostProcessing> GArr_PostProcesses;
extern std::vector<gobject::PostOperation> GArr_PostOperations;

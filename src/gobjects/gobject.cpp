#include "gobject.h"

#include <sstream>

//Global getDP_object(gObject) Array:
std::vector<std::string> GArr_Groups;
std::vector<std::string> GArr_Functions;
std::vector<gobject::Constraint> GArr_Constraints;
std::vector<gobject::FunctionSpace> GArr_FunctionSpaces;
std::vector<gobject::Jacobian> GArr_Jacobians;
std::vector<gobject::Integration> GArr_Integrations;
std::vector<gobject::Formulation> GArr_Formulations; 
std::vector<gobject::Resolution> GArr_Resolutions;
std::vector<gobject::PostProcessing> GArr_PostProcesses;
std::vector<gobject::PostOperation> GArr_PostOperations;

namespace gobject {

	//GetDP Constant Term definitions

	//Constant Quantity Definitions
	std::string charT;
	std::string charQ;
	std::string charQgen;
	std::string charQnl;

	//Conduction
	std::string sVarConduction;
	std::string sGroupConduction;
	std::string sVarNL_Conduction;
	std::string sGroupNL_Conduction;

	//Convection
	std::string sVarConvection;
	std::string sVarConvTInf;
	std::string sGroupConvection;

	//Radiation
	std::string sVarRadiation;
	std::string sVarRadTInf;
	std::string sGroupRadiation;

	//Generation
	std::string sVarGeneration;
	std::string sGroupGeneration;

	//HeatFlux BC
	std::string sVarHeatFlux;
	std::string sGroupHeatFlux;

	//TEmperature BC
	std::string sVarTempConstraint;
	std::string sGroupTemperature;

	//Temperature Discontinuity
	std::string sVarTempDiscontinuity;
	std::string sGroupDiscontinuous;
	std::string sVolDiscontinuous;
	std::string sSurfDiscontinuous;
	std::string sDomainDiscontinuous;

	std::string sSpaceTCont;
	std::string sSpaceTDisc;
	std::string sBasisFunctionDisc;

	std::string charTdisc;
	std::string charTcont;

	std::string charTdiscfile;
	std::string charTcontfile;

	//NonLinear Iteration
	std::string sVarNL_InitialResidual;
	std::string sVarNL_Residual;
	std::string sVarNL_Iteration;

	std::string sVarNL_eps;
	std::string sVarNL_rel;
	std::string sVarNL_maxloop;

	std::string sVarNL_submenu;

	//Output File Names
	std::string charTfile;
	std::string charQfile;
	std::string charQgenfile;

	//GetDP Default Process Object Names
	std::string defNamePostOperation;
	std::string defNamePostProcess;
	std::string defNameResolution;
	std::string defNameResSystem;
	std::string defNameResNLSystem;
	std::string defNameFormulation;
	std::string defFormulationType;
	std::string defFormEQType;
	std::string defFunctionSpace;
	std::string defBFName;
	std::string defBasisFunction;

	std::string TIntegration;
	std::string TJacobianVol;
	std::string TJacobianSur;
	std::string TDomain;

	//Default Gaussian Integration Points
	std::string integraType = "Gauss";
	int elementPoint = 1;
	int elementLine = 3;
	int elementTri = 4;
	int elementQuad = 4;
	int elementTetra = 4;
	int elementHexa = 6;
	int elementPrism = 6;

	//GetDP Analysis_Flags
	bool GFlagConduction;
	bool GFlagConvection;
	bool GFlagRadiation;
	bool GFlagGeneration;
	bool GFlagHeatFlux;
	bool GFlagTemperature;
	bool GFlagDiscontinuous;
	bool GFlagNL_Conduction;
	short int GFlagSysOrder;
	short int GFlagBFunctions;

	std::string varNL_eps;
	std::string varNL_rel;
	std::string varNL_maxloop;

	void initGFlags() {

		setDefaults();

		//Heat Transfer Mechanisms
		GFlagConduction = false;
		GFlagConvection = false;
		GFlagRadiation = false;
		GFlagGeneration = false;
		GFlagHeatFlux = false;
		GFlagTemperature = false;
		GFlagDiscontinuous = false;
		GFlagNL_Conduction = false;

		//Geometry Mechanisms
		GFlagSysOrder = 1;
		GFlagBFunctions = 1;

	}

	void setDefaults() {
		//GetDP Constant Term definitions

		//Constant Quantity Definitions
		charT = "T";
		charQ = "q";
		charQgen = "Qgen";
		charQnl = "qNL";

		//Conduction
		sVarConduction = "condK";
		sGroupConduction = "Cond_Regions";
		sVarNL_Conduction = "NL_condK";
		sGroupNL_Conduction = "NL_Cond_Regions";

		//Convection
		sVarConvection = "convH";
		sVarConvTInf = "TinfConv";
		sGroupConvection = "Conv_Regions";

		//Radiation
		sVarRadiation = "radE";
		sVarRadTInf = "TinfRad";
		sGroupRadiation = "Rad_Regions";

		//Generation
		sVarGeneration = "qGen";
		sGroupGeneration = "qGen_Regions";

		//HeatFlux BC
		sVarHeatFlux = "Flux";
		sGroupHeatFlux = "Flux_Regions";

		//TEmperature BC
		sVarTempConstraint = "setT_BC";
		sGroupTemperature = "Temp_Regions";

		//Temperature Discontinuity
		sVarTempDiscontinuity = "setT_disc";
		sGroupDiscontinuous = "Disc_Domains";
		sVolDiscontinuous = "Disc_Vol";
		sSurfDiscontinuous = "Disc_Surf";
		sDomainDiscontinuous = "Disc_Dom";

		sSpaceTCont = "Tcont";
		sSpaceTDisc = "Tdisc";
		sBasisFunctionDisc = charT + "_disc";
		charTdisc = charT + "dc";
		charTcont = charT + "cn";

		//NonLinear Iteration
		sVarNL_InitialResidual = "res0";
		sVarNL_Residual = "res";
		sVarNL_Iteration = "i";

		sVarNL_eps = "NL_eps";
		sVarNL_rel = "NL_rel";
		sVarNL_maxloop = "NL_loop";

		sVarNL_submenu = "NL_Iteration";

		//Output File Names
		charTfile = charT + "_map.pos";
		charQfile = charQ + "_map.pos";
		charQgenfile = charQgen + "_map.pos";
		charTdiscfile = charTdisc + "_map.pos";
		charTcontfile = charTcont + "_map.pos";

		//GetDP Default Process Object Names
		defNamePostOperation = "thermal_PostOperation";
		defNamePostProcess = "thermal_PostProcess";
		defNameResolution = "thermal_Resolution";
		defNameResSystem = "thermal_System";
		defNameResNLSystem = "thermal_System_NL";
		defNameFormulation = "thermal_Formulation";
		defFormulationType = "FemEquation"; //only type supported
		defFormEQType = "Galerkin";
		defFunctionSpace = "H_gradT_funcSpace";
		defBFName = "sN";
		defBasisFunction = charT + "node";

		TIntegration = "GaussIntegration";
		TJacobianVol = "VolumeJacobian";
		TJacobianSur = "SurfaceJacobian";
		TDomain = "Domain_H_gradT";

		//NonLinear Iteration Terms
		varNL_eps = "1e-8";
		varNL_rel = "1e-8";
		varNL_maxloop = "50";

	}

	void clearGlobalArrays() {
		GArr_Groups.clear();
		GArr_Functions.clear();
		GArr_Constraints.clear();
		GArr_FunctionSpaces.clear();
		GArr_Jacobians.clear();
		GArr_Integrations.clear();
		GArr_Formulations.clear();
		GArr_Resolutions.clear();
		GArr_PostProcesses.clear();
		GArr_PostOperations.clear();
	}

}//end namespace gobject


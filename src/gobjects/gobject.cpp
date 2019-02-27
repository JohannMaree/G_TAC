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

	//Conduction
	std::string sVarConduction = "conK";
	std::string sGroupConduction = "Cond_Elements";

	//Convection
	std::string sVarConvection = "conH";
	std::string sVarConvTInf = "TinfConv";
	std::string sGroupConvection = "Conv_Elements";

	//Radiation
	std::string sVarRadiation = "radE";
	std::string sVarRadTInf = "TinfRad";
	std::string sGroupRadiation = "Rad_Elements";

	//Generation
	std::string sVarGeneration = "qGen";
	std::string sGroupGeneration = "qGen_Elements";

	//HeatFlux BC
	std::string sVarHeatFlux = "Flux";
	std::string sGroupHeatFlux = "Flux_Elements";

	//TEmperature BC
	std::string sVarTempConstraint = "Type1BC";
	std::string sGroupTemperature = "Temp_Elements";

	//Temperature Discontinuity
	std::string sVarTempDiscontinuity = "T_Disc";
	std::string sGroupDiscontinuous = "Disc_Elements";

	std::string sSpaceTCont = "T_Continuous";
	std::string sSpaceTDisc = "T_Discontinous";
	std::string sBasisFunctionDisc = charT + "_disc";

	std::string charTdisc = charT + "dc";
	std::string charTcont = charT + "cn";

	std::string charTdiscfile = charTdisc + "_map.pos";
	std::string charTcontfile = charTcont + "_map.pos";

	//Constant Quantity Definitions
	std::string charT = "T";
	std::string charQ = "q";
	std::string charQgen = "Qgen";

	//Output File Names
	std::string charTfile = charT + "_map.pos";
	std::string charQfile = charQ + "_map.pos";


	//GetDP Default Process Object Names
	std::string defNamePostOperation = "def_HeatMap";
	std::string defNamePostProcess = "def_Thermals";
	std::string defNameResolution = "def_ThermalRes";
	std::string defNameReSystem = "def_System";
	std::string defNameFormulation = "def_ThermalForm";
	std::string defFormEQType = "Integral";
	std::string defFunctionSpace = "Hgrad_Tspace";
	std::string defBasisFunction = charT + "_Node";

	std::string TIntegration = "Integra";
	std::string TJacobianVol = "Volume";
	std::string TJacobianSur = "Surface";
	std::string TDomain = "Domain_Hgrad_T";

	//GetDP Analysis_Flags
	bool GFlagConduction;
	bool GFlagConvection;
	bool GFlagRadiation;
	bool GFlagGeneration;
	bool GFlagHeatFlux;
	bool GFlagTemperature;
	bool GFlagDiscontinuous;
	bool GFlag3Dim;
	short int GFlagSysOrder;
	short int GFlagBFunctions;

	void initGFlags() {
		//Heat Transfer Mechanisms
		GFlagConduction = false;
		GFlagConvection = false;
		GFlagRadiation = false;
		GFlagGeneration = false;
		GFlagHeatFlux = false;
		GFlagTemperature = false;
		GFlagDiscontinuous = false;

		//Geometry Mechanisms
		GFlag3Dim = false;
		GFlagSysOrder = 1;
		GFlagBFunctions = 1;

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

}


#include "Formulation.h"
#include "gobject.h"

namespace gobject {

	int defaultFormulation(int posFSpace){
		Formulation form;
		form.Name = defNameFormulation;
		form.Type = "FemEquation";
		
		formQuantity fq;
		fq.Name = charT;
		fq.Type = "Local";
		fq.NameOfSpace = GArr_FunctionSpaces[posFSpace].Name;
		form.Quantities.push_back(fq);

		if (GFlagConduction) {
			//Conduction EQ
			formEquation condEQ;
			condEQ.EQType = defFormEQType;
			condEQ.PDE = sVarConduction + "[] * Dof{d " + charT + "} , {d " + charT + "}";
			condEQ.DomainName = sGroupConduction;
			condEQ.JacobianName = TJacobianVol;
			condEQ.IntegrationName = TIntegration;
			form.Equations.push_back(condEQ);
		}
		
		if (GFlagConvection) {
			//Convection EQ
			formEquation convEQ;
			convEQ.EQType = defFormEQType;
			convEQ.PDE = sVarConvection + "[] * Dof{" + charT + "} , {" + charT + "}";
			convEQ.DomainName = sGroupConvection;
			convEQ.JacobianName = TJacobianSur;
			convEQ.IntegrationName = TIntegration;
			form.Equations.push_back(convEQ);

			convEQ.EQType = defFormEQType;
			convEQ.PDE = "-" + sVarConvection + "[] * " + sVarConvTInf + "[] , {" + charT + "}";
			convEQ.DomainName = sGroupConvection;
			convEQ.JacobianName = TJacobianSur;
			convEQ.IntegrationName = TIntegration;
			form.Equations.push_back(convEQ);
		}
		
		if (GFlagRadiation) {
			//Radiation EQ
			formEquation radEQ;
			radEQ.EQType = defFormEQType;
			radEQ.PDE = sVarRadiation + "[] * ({" + charT + "})^4 - (" + sVarRadTInf + "[])^4 , {" + charT + "}";
			radEQ.DomainName = sGroupRadiation;
			radEQ.JacobianName = TJacobianSur;
			radEQ.IntegrationName = TIntegration;
			form.Equations.push_back(radEQ);
		}

		if (GFlagGeneration) {
			//Generation EQ
			formEquation genEQ;
			genEQ.EQType = defFormEQType;
			genEQ.PDE = "-" + sVarGeneration + "[] , {" + charT + "}";
			genEQ.DomainName = sGroupGeneration;
			genEQ.JacobianName = TJacobianVol;
			genEQ.IntegrationName = TIntegration;
			form.Equations.push_back(genEQ);
		}

		if (GFlagHeatFlux) {
			//HeatFlux EQ
			formEquation hfEQ;
			hfEQ.EQType = defFormEQType;
			hfEQ.PDE = "-" + sVarHeatFlux + "[] , {" + charT + "}";
			hfEQ.DomainName = sGroupHeatFlux;
			hfEQ.JacobianName = TJacobianSur;
			hfEQ.IntegrationName = TIntegration;
			form.Equations.push_back(hfEQ);
		}
		
		GArr_Formulations.push_back(form);
		return static_cast<int>(GArr_Formulations.size() - 1);
	}

}
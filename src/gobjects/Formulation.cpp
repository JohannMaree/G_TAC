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
		
		return addFormulation(form);
	}

	int addFormulation(Formulation& f) {
		int in = inArr_Formulation(f.Name);
		if (in >= 0) {	//Add parameters to existing Formulation
			for (ind i = 0; i < f.Quantities.size(); ++i) {
				addToFormulation(f.Quantities[i],in);
			}
			for (ind i = 0; i < f.Equations.size(); ++i) {
				addToFormulation(f.Equations[i], in);
			}
			for (ind i = 0; i < f.Globals.size(); ++i) {
				addToFormulation(f.Globals[i], in);
			}
			return in;
		}
		else {			//Create new Formulation
			GArr_Formulations.emplace_back(f);
			return 0;
		}
	}

	int inArr_Formulation(std::string& compareName) {
		for (int i = 0; i < GArr_Formulations.size(); ++i) {
			if (pstring::icompare(GArr_Formulations[i].Name, compareName))
				return i;
		}
		return (-1);
	}

	void addToFormulation(formQuantity& fq, int fpos) {
		GArr_Formulations[fpos].Quantities.emplace_back(fq);
	}

	void addToFormulation(formEquation& fe, int fpos) {
		GArr_Formulations[fpos].Equations.emplace_back(fe);
	}

	void addToFormulation(formGlobal& fg, int fpos) {
		GArr_Formulations[fpos].Globals.emplace_back(fg);
	}

}
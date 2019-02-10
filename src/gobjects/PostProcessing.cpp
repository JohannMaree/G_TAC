#include "PostProcessing.h"
#include "gobject.h"

namespace gobject {

	int defaultPostProcessing(int posFormulation) {
		PostProcessing pp;
		pp.Name = defNamePostProcess;
		pp.NameOfFormulation = GArr_Formulations[posFormulation].Name;
		
		postQuantity pqT;
		pqT.Name = charT;
		pqT.Domain = TDomain;
		pqT.Term = "{" + charT + "}";
		pqT.Jacobian = TJacobianVol;
		pp.Quantities.push_back(pqT);

		postQuantity pqQ;
		pqQ.Name = charQ;
		pqQ.Domain = TDomain;
		pqQ.Term = "-{d " + charT + "}";
		pqQ.Jacobian = TJacobianVol;
		pp.Quantities.push_back(pqQ);

		if (GFlagGeneration) {
			postQuantity pqQgen;
			pqQgen.Name = charQgen;
			pqQgen.Domain = TDomain;
			pqQgen.Term = sVarGeneration + "[]";
			pqQgen.Jacobian = TJacobianVol;
			pp.Quantities.push_back(pqQgen);
		}

		GArr_PostProcesses.push_back(pp);
		return static_cast<int>(GArr_PostProcesses.size() - 1);
	}

}
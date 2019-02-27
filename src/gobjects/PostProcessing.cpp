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

		return addPostProcessing(pp);
	}

	int addPostProcessing(PostProcessing& pp) {
		int in = inArr_PostProcessing(pp.Name);
		if (in >= 0) {
			if (pstring::icompare(GArr_PostProcesses[in].NameOfFormulation, pp.NameOfFormulation)) {
				for (ind i = 0; i < pp.Quantities.size(); ++i) {
					addToPostProcessing(pp.Quantities[i], in);
				}
			}
			else {
				PostProcessing newPP = pp;
				newPP.Name += "_" + pp.NameOfFormulation;
				GArr_PostProcesses.push_back(newPP);
				in = static_cast<int>(GArr_PostProcesses.size() - 1);
			}
			return in;
		}
		else {
			GArr_PostProcesses.emplace_back(pp);
			return 0;
		}
	}

	int inArr_PostProcessing(std::string& compareName) {
		for (int i = 0; i < GArr_PostProcesses.size(); ++i) {
			if (pstring::icompare(GArr_PostProcesses[i].Name, compareName))
				return i;
		}
		return (-1);
	}

	void addToPostProcessing(postQuantity& pq, int ppos) {
		int in = inPostQuantities(pq.Name, ppos);
		if (in == -1) {
			GArr_PostProcesses[ppos].Quantities.emplace_back(pq);
		}
	}

	int inPostQuantities(std::string compareName, int ppos) {
		for (int i = 0; i < GArr_PostProcesses[ppos].Quantities.size(); ++i) {
			if (pstring::icompare(GArr_PostProcesses[ppos].Quantities[i].Name, compareName))
				return i;
		}
		return (-1);
	}

}
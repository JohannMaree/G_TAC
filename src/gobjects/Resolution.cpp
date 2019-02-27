#include "gobject.h"

namespace gobject {

	void defaultResolution(int posFormulation) {
		Resolution res;
		res.Name = defNameResolution;
		
		rSystemOps sop;
		sop.Name = defNameReSystem;
		sop.NameOfFormulation = GArr_Formulations[posFormulation].Name;
		sop.Operations.push_back("Generate[" + sop.Name + "]");
		sop.Operations.push_back("Solve[" + sop.Name + "]");
		sop.Operations.push_back("SaveSolution[" + sop.Name + "]");

		res.SystemOps.push_back(sop);
		addResolution(res);

	}

	int addResolution(Resolution& res) {
		int in = inArr_Resolutions(res.Name);
		if (in >= 0) {
			for (ind i = 0; i < res.SystemOps.size(); ++i) {
				addToResolution(res.SystemOps[i], in);
			}
			return in;
		}
		else {
			GArr_Resolutions.emplace_back(res);
			return 0;
		}
	}

	int inArr_Resolutions(std::string& compareName) {
		for (int i = 0; i < GArr_Resolutions.size(); ++i) {
			if (pstring::icompare(GArr_Resolutions[i].Name,compareName))
				return i;
		}
		return (-1);
	}

	void addToResolution(rSystemOps& so, int rpos) {
		GArr_Resolutions[rpos].SystemOps.emplace_back(so);
	}

}
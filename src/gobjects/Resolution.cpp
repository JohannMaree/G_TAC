#include "Resolution.h"
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
		GArr_Resolutions.push_back(res);

	}

}
#include "FunctionSpace.h"
#include "gobject.h"

namespace gobject {

	int defaultFunctionSpace() {
		FunctionSpace fs;
		fs.Name = defFSpace;
		fs.Type = "Form0";

		fsBasisFunction bf;
		bf.Name = "sN";
		bf.NameOfCoef = charT + "N";
		bf.Function = "BF_Node";
		bf.Support = TDomain;
		if (GFlagBFunctions == 1) {
			bf.Entity = "NodesOf[All]";
		}
		else {
			bf.Entity = "NodesOf[" + TDomain +"]";
		}
		fs.BasisFunctions.push_back(bf);

		fsConstraint cs;
		for (int i = 0; i < GArr_Constraints.size(); ++i) {
			cs.NameOfCoef = charT + "N";
			cs.EntityType = "NodesOf";
			cs.NameOfConstraint = GArr_Constraints[i].Name;
			fs.Constraints.push_back(cs);
		}

		GArr_FunctionSpaces.push_back(fs);
		return static_cast<int>(GArr_FunctionSpaces.size() - 1);
	}

	void addFunctionSpaceConstraint(fsConstraint* fsc, int fspos) {
		GArr_FunctionSpaces[fspos].Constraints.emplace_back(fsc);
	}

	void addFunctionSpaceBasisFunction(fsBasisFunction* fsb, int fspos) {
		GArr_FunctionSpaces[fspos].BasisFunctions.emplace_back(fsb);
	}

}
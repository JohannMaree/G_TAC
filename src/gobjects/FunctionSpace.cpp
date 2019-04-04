#include "gobject.h"

namespace gobject {

	int defaultFunctionSpace() {
		FunctionSpace fs;
		fs.Name = defFunctionSpace;
		fs.Type = "Form0";

		fsBasisFunction bf;
		bf.Name = defBFName;
		bf.NameOfCoef = defBasisFunction;
		bf.Function = "BF_Node";
		bf.Support = TDomain;
		if (GFlagBFunctions == 1) {
			bf.Entity = "NodesOf[All]";
		}
		else {
			bf.Entity = "NodesOf[" + TDomain +"]";
		}
		fs.BasisFunctions.push_back(bf);
		
		return addFunctionSpace(fs);
	}

	int addFunctionSpace(FunctionSpace& fs) {
		int in = inArr_FunctionSpace(fs.Name);
		if (in >= 0) {	//Add parameters to existing FunctionSpace
			if (pstring::icompare(GArr_FunctionSpaces[in].Type, fs.Type)) { //If same type of FS
				for (ind i = 0; i < fs.BasisFunctions.size(); ++i) {
					addToFunctionSpace(fs.BasisFunctions[i],in);
				}
				for (ind i = 0; i < fs.Constraints.size(); ++i) {
					addToFunctionSpace(fs.Constraints[i], in);
				}
				for (ind i = 0; i < fs.Subspaces.size(); ++i) {
					addToFunctionSpace(fs.Subspaces[i], in);
				}
				for (ind i = 0; i < fs.GlobalQuantities.size(); ++i) {
					addToFunctionSpace(fs.GlobalQuantities[i], in);
				}
			}
			else {	//Types Dont Match, Make new functionSpace
				FunctionSpace fsnew = fs;
				fsnew.Name += "_" + fsnew.Type;
				GArr_FunctionSpaces.push_back(fsnew);
				in = static_cast<int>(GArr_FunctionSpaces.size() - 1);
			}
			return in;
		}
		else {			//Create new FunctionSpace
			GArr_FunctionSpaces.emplace_back(fs);
			return 0;
		}
	}

	int inArr_FunctionSpace(std::string& compareName) {
		for (int i = 0; i < GArr_FunctionSpaces.size(); ++i) {
			if (pstring::icompare(GArr_FunctionSpaces[i].Name, compareName))
				return i;
		}
		return (-1);
	}


	void addToFunctionSpace(fsConstraint& fsc, int fspos) {
		GArr_FunctionSpaces[fspos].Constraints.emplace_back(fsc);
	}

	void addToFunctionSpace(fsBasisFunction& fsb, int fspos) {
		GArr_FunctionSpaces[fspos].BasisFunctions.emplace_back(fsb);
	}

	void addToFunctionSpace(fsSubspace& fss, int fspos) {
		GArr_FunctionSpaces[fspos].Subspaces.emplace_back(fss);
	}

	void addToFunctionSpace(fsGlobalQuantity& fsgq, int fspos) {
		GArr_FunctionSpaces[fspos].GlobalQuantities.emplace_back(fsgq);
	}

}
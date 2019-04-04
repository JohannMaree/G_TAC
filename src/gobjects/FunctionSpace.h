#pragma once
#include <string>
#include <vector>

namespace gobject {

	struct fsBasisFunction {
		std::string Name;
		std::string NameOfCoef;
		std::string Function;
		std::string Support;
		std::string Entity;
	};

	struct fsConstraint {
		std::string NameOfCoef;
		std::string EntityType;
		std::string NameOfConstraint;
	};

	struct fsSubspace {
		std::string Name;
		std::string NameOfBasisFunction;
	};

	struct fsGlobalQuantity {
		std::string Name;
		std::string Type;
		std::string NameOfCoef;
	};

	class FunctionSpace {
	public:
		std::string Name;
		std::string Type;
		std::vector<fsBasisFunction> BasisFunctions;
		std::vector<fsConstraint> Constraints;
		std::vector<fsSubspace> Subspaces;
		std::vector<fsGlobalQuantity> GlobalQuantities;
	};

	int defaultFunctionSpace();

	int addFunctionSpace(FunctionSpace& fs);
	int inArr_FunctionSpace(std::string& compareName);

	void addToFunctionSpace(fsConstraint& fsc, int fspos = 0);
	void addToFunctionSpace(fsBasisFunction& fsb, int fspos = 0);
	void addToFunctionSpace(fsSubspace& fss, int fspos = 0);
	void addToFunctionSpace(fsGlobalQuantity& fsgq, int fspos = 0);

}

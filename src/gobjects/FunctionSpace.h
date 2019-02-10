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

	class FunctionSpace {
	public:
		std::string Name;
		std::string Type;
		std::vector<fsBasisFunction> BasisFunctions;
		std::vector<fsConstraint> Constraints;
	};

	int defaultFunctionSpace();

}

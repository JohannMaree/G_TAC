#pragma once

#include <string>
#include <vector>

namespace gobject {

	struct cCase {
		std::string Region;
		std::string Value;
	};

	class Constraint {
	public:
		std::string Name;
		std::string Type;
		std::vector<cCase> Cases;
	};

	int addConstraint(Constraint& con);
	int inArr_Constraint(std::string& compareName);
	void addToConstraint(cCase& conCase, int cpos = 0);
}
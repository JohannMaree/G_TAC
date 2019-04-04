#pragma once
#include <string>
#include <vector>

namespace gobject {
	
	struct jCase {
		std::string Region;
		std::string Jacobian;
	};

	class Jacobian {
	public:
		std::string Name;
		std::vector<jCase> Cases;
	};

	void defaultJacobian();

	int addJacobian(Jacobian& jac);
	int inArr_Jacobian(std::string& compareName);

	void addToJacobian(jCase& jc, int jpos = 0);


}
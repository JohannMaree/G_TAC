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
}
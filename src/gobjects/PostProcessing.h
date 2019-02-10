#pragma once

#include <string>
#include <vector>

namespace gobject {

	struct postQuantity {
		std::string Name;
		std::string Term;
		std::string Domain;
		std::string Jacobian;
	};

	class PostProcessing {
	public:
		std::string Name;
		std::string NameOfFormulation;
		std::vector<postQuantity> Quantities;
	};

	int defaultPostProcessing(int posFormulation);

}
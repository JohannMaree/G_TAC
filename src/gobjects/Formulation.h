#pragma once

#include <string>
#include <vector>

namespace gobject {

	struct formQuantity {
		std::string Name;
		std::string Type;
		std::string NameOfSpace;
	};

	struct formEquation {
		std::string EQType;
		std::string PDE;
		std::string DomainName;
		std::string JacobianName;
		std::string IntegrationName;
	};

	class Formulation {
	public:
		std::string Name;
		std::string Type;
		std::vector<formQuantity> Quantities;
		std::vector<formEquation> Equations;
	};

	int defaultFormulation(int posFSpace);
	void addFormulationQuantity(formQuantity* fq, int fpos = 0);
	void addFormulationEquation(formEquation* fe, int fpos = 0);

}

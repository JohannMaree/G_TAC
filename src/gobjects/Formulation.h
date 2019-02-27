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

	struct formGlobal {
		std::string GEQType;
		std::string GEquation;
		std::string DomainName;
	};

	class Formulation {
	public:
		std::string Name;
		std::string Type;
		std::vector<formQuantity> Quantities;
		std::vector<formEquation> Equations;
		std::vector<formGlobal> Globals;
	};

	int defaultFormulation(int posFSpace);

	int addFormulation(Formulation& f);
	int inArr_Formulation(std::string& compareName);

	void addToFormulation(formQuantity& fq, int fpos = 0);
	void addToFormulation(formEquation& fe, int fpos = 0);
	void addToFormulation(formGlobal& fg, int fpos = 0);

}

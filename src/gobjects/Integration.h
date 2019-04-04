#pragma once
#include <string>
#include <Vector>

namespace gobject {

	struct geoCase {
		std::string GeoElement;
		short int NumberOfPoints;
	};
	
	struct iCase {
		std::string Type;
		std::vector<geoCase> geoCases;
	};

	class Integration {
	public:
		std::string Name;
		std::vector<iCase> iCases;
	};

	int defaultIntegration();

	int addIntegration(Integration& integra);
	int inArr_Integration(std::string& compareName);

	void addToIntegration(iCase& ic, int ipos = 0);
	int inGeoCases(iCase& iC, std::string& compare);

}
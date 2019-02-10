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

	void defaultIntegration();

}
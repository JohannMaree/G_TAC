#include "Integration.h"
#include "gobject.h"

namespace gobject {

	void defaultIntegration(){
		Integration ing;
		ing.Name = TIntegration;

		iCase ic;
		ic.Type = "Gauss";
		
		geoCase gc;
		if (GFlagSysOrder == 1) {
			//Default 2D Elements

			gc.GeoElement = "Point";
			gc.NumberOfPoints = 1;
			ic.geoCases.push_back(gc);
			
			gc.GeoElement = "Line";
			gc.NumberOfPoints = 3;
			ic.geoCases.push_back(gc);
			
			gc.GeoElement = "Triangle";
			gc.NumberOfPoints = 4;
			ic.geoCases.push_back(gc);

			gc.GeoElement = "Quadrangle";
			gc.NumberOfPoints = 4;
			ic.geoCases.push_back(gc);

			if (GFlag3Dim) {
				//Default 3D Elements

				gc.GeoElement = "Tetrahedron";
				gc.NumberOfPoints = 4;
				ic.geoCases.push_back(gc);

				gc.GeoElement = "Hexahedron";
				gc.NumberOfPoints = 6;
				ic.geoCases.push_back(gc);

				gc.GeoElement = "Prism";
				gc.NumberOfPoints = 6;
				ic.geoCases.push_back(gc);
			}
			
		}
		ing.iCases.push_back(ic);

		GArr_Integrations.push_back(ing);
	}

}

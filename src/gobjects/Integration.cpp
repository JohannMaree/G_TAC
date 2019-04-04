#include "gobject.h"

namespace gobject {

	int defaultIntegration(){
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

		return addIntegration(ing);
	}

	int addIntegration(Integration& integra) {
		int in = inArr_Integration(integra.Name);
		if (in >= 0) {	//Add parameters to existing Integration
			for (ind i = 0; i < integra.iCases.size(); ++i) {
				addToIntegration(integra.iCases[i], in);
			}
			return in;
		}
		else {			//Create new Integration
			GArr_Integrations.emplace_back(integra);
			return 0;
		}
	}

	int inArr_Integration(std::string& compareName) {
		for (int i = 0; i < GArr_Integrations.size(); ++i) {
			if (pstring::icompare(GArr_Integrations[i].Name, compareName))
				return i;
		}
		return (-1);
	}

	void addToIntegration(iCase& ic,int ipos) {
		int inCase = -1;
		for (int i = 0; i < GArr_Integrations[ipos].iCases.size(); ++i) {
			if (pstring::icompare(GArr_Integrations[ipos].iCases[i].Type, ic.Type))
				inCase = i;
		}

		if (inCase >= 0) {	//Type Exists; Add To Current iCase with same type
			for (ind j = 0; j < ic.geoCases.size(); ++j) {
				int ingeo = inGeoCases(GArr_Integrations[ipos].iCases[inCase], ic.geoCases[j].GeoElement);
				if (ingeo >= 0) {	//GeoElement Exists; Update GeoCase numberOfPoints if existing numberOfPoints is lower
					int nopGA = GArr_Integrations[ipos].iCases[inCase].geoCases[ingeo].NumberOfPoints;
					int nopic = ic.geoCases[j].NumberOfPoints;
					if (nopGA < nopic) {
						GArr_Integrations[ipos].iCases[inCase].geoCases[ingeo].NumberOfPoints = nopic;
					}
				}
				else {				//GeoElement Not Exist; Add new GeoCase to iCase
					GArr_Integrations[ipos].iCases[inCase].geoCases.emplace_back(ic.geoCases[j]);
				}
			}
		}
		else {				//Type Not Exists; Add new iCase
			GArr_Integrations[ipos].iCases.emplace_back(ic);
		}
	}

	int inGeoCases(iCase& iC, std::string& geoCompare) {
		for (int i = 0; i < iC.geoCases.size(); ++i) {
			if (pstring::icompare(iC.geoCases[i].GeoElement, geoCompare))
				return i;
		}
		return (-1);
	}

}

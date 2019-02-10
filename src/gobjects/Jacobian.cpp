#include "Jacobian.h"
#include "gobject.h"

namespace gobject {

	void defaultJacobian() {
		Jacobian jacVol,jacSur;
		jCase jc;
		
		//Default Volume Jacobian Transformation
		jacVol.Name = TJacobianVol;
		jc.Region = "All";
		jc.Jacobian = "Vol";
		jacVol.Cases.push_back(jc);
		GArr_Jacobians.push_back(jacVol);
		
		//Default Surface Jacobian Transformation
		jacSur.Name = TJacobianSur;
		jc.Region = "All";
		jc.Jacobian = "Sur";
		jacSur.Cases.push_back(jc);
		GArr_Jacobians.push_back(jacSur);

	}

}
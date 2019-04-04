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
		addJacobian(jacVol);
		
		//Default Surface Jacobian Transformation
		jacSur.Name = TJacobianSur;
		jc.Region = "All";
		jc.Jacobian = "Sur";
		jacSur.Cases.push_back(jc);
		addJacobian(jacSur);

	}

	int addJacobian(Jacobian& jac) {
		int in = inArr_Jacobian(jac.Name);
		if (in >= 0) {
			for (ind i = 0; i < jac.Cases.size(); ++i) {
				addToJacobian(jac.Cases[i], in);
			}
			return in;
		}
		else {
			GArr_Jacobians.emplace_back(jac);
			return 0;
		}
	}

	int inArr_Jacobian(std::string& compareName) {
		for (int i = 0; i < GArr_Jacobians.size(); ++i) {
			if (pstring::icompare(GArr_Jacobians[i].Name, compareName))
				return i;
		}
		return (-1);
	}

	void addToJacobian(jCase& jc, int jpos) {
		GArr_Jacobians[jpos].Cases.emplace_back(jc);
	}

}
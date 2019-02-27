#include "gobject.h"

namespace gobject {

	int addConstraint(Constraint& con) {
		int in = inArr_Constraint(con.Name);
		if (in >= 0) {	//Add cases to existing constraint
			for (ind i = 0; i < con.Cases.size(); ++i) {
				GArr_Constraints[in].Cases.push_back(con.Cases[i]);
			}
			return in;
		}
		else {			//Create new constraint with cases
			GArr_Constraints.emplace_back(con);
			return 0;
		}
	}

	int inArr_Constraint(std::string& compareName) {
		for (int i = 0; i < GArr_Constraints.size(); ++i) {
			if (pstring::icompare(GArr_Constraints[i].Name, compareName))
				return i;
		}
		return (-1);
	}

	void addToConstraint(cCase& conCase, int cpos) {
		GArr_Constraints[cpos].Cases.emplace_back(conCase);
	}

}
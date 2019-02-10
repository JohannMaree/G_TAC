#include "Constraint.h"
#include "proxStrings.h"
#include "gobject.h"

namespace gobject {

	void addConstraint(Constraint& con) {
		int in = inArr_Constraint(con.Name);
		if (in >= 0) {	//Add cases to existing constraint
			for (ind i = 0; i < con.Cases.size(); ++i) {
				GArr_Constraints[in].Cases.push_back(con.Cases[i]);
			}
		}
		else {			//Create new constraint with cases
			GArr_Constraints.emplace_back(con);
		}
	}

	int inArr_Constraint(std::string& compareName) {
		for (ind i = 0; i < GArr_Constraints.size(); ++i) {
			if (pstring::icompare(GArr_Constraints[i].Name, compareName))
				return static_cast<int>(i);
		}
		return (-1);
	}

}
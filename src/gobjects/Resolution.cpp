#include "gobject.h"

namespace gobject {

	void defaultResolution(int posFormulation) {
		Resolution res;
		res.Name = defNameResolution;
		
		if (GFlagNL_Conduction) {
			rSystemOps nlop;
			nlop.Name = defNameResNLSystem;
			nlop.NameOfFormulation = GArr_Formulations[posFormulation].Name;

			nlop.Operations.push_back("InitSolution[" + nlop.Name + "]");
			nlop.Operations.push_back("Generate[" + nlop.Name + "]");
			nlop.Operations.push_back("Solve[" + nlop.Name + "]");
			nlop.Operations.push_back("");

			nlop.Operations.push_back("Generate[" + nlop.Name + "]");
			nlop.Operations.push_back("GetResidual[" + nlop.Name + ", $" + sVarNL_InitialResidual + "]");
			nlop.Operations.push_back("Evaluate[$" + sVarNL_Residual + " = $" + sVarNL_InitialResidual + "]");
			nlop.Operations.push_back("Evaluate[$" + sVarNL_Iteration + " = 0]");
			nlop.Operations.push_back("");

			//Info print command for gmsh
			std::string printOps = "";
			printOps += "Print[{";
			printOps +=	"$" + sVarNL_Iteration + ", ";
			printOps += "$" + sVarNL_Residual + ", ";
			printOps += "$" + sVarNL_Residual + "/$" + sVarNL_InitialResidual + "}, ";
			printOps += "Format \"Residual %0.3g: abs %14.9e rel %14.9e\"";
			printOps += "]";
			nlop.Operations.push_back(printOps);
			nlop.Operations.push_back("");

			//Iteration Convergence Loop
			std::string loopOps = "";
			loopOps += "While[";
			loopOps += "($" + sVarNL_Residual + " > " + sVarNL_eps + ")";
			loopOps += "&&";
			loopOps += "($" + sVarNL_Residual + "/$" + sVarNL_InitialResidual + " > " + sVarNL_rel + ")";
			loopOps += "&&";
			loopOps += "($" + sVarNL_Residual + "/$" + sVarNL_InitialResidual + " <= 1)";
			loopOps += "&&";
			loopOps += "($" + sVarNL_Iteration + " < " + sVarNL_maxloop + ")";
			loopOps += "]{";
			nlop.Operations.push_back(loopOps);
			nlop.Operations.push_back("");

			nlop.Operations.push_back("\tSolve[" + nlop.Name + "]");
			nlop.Operations.push_back("\tGenerate[" + nlop.Name + "]");
			nlop.Operations.push_back("\tGetResidual[" + nlop.Name + ", $" + sVarNL_Residual + "]");
			nlop.Operations.push_back("\tEvaluate[$" + sVarNL_Iteration + " = $" + sVarNL_Iteration + " + 1]");
			nlop.Operations.push_back("\t" + printOps);
			nlop.Operations.push_back("");
			loopOps = "}";
			nlop.Operations.push_back(loopOps);

			nlop.Operations.push_back("SaveSolution[" + nlop.Name + "]");
			res.SystemOps.push_back(nlop);
		}
		else {
			rSystemOps sop;
			sop.Name = defNameResSystem;
			sop.NameOfFormulation = GArr_Formulations[posFormulation].Name;

			sop.Operations.push_back("Generate[" + sop.Name + "]");
			sop.Operations.push_back("Solve[" + sop.Name + "]");
			sop.Operations.push_back("SaveSolution[" + sop.Name + "]");

			res.SystemOps.push_back(sop);
		}
		
		addResolution(res);
	}

	int addResolution(Resolution& res) {
		int in = inArr_Resolutions(res.Name);
		if (in >= 0) {
			for (ind i = 0; i < res.SystemOps.size(); ++i) {
				addToResolution(res.SystemOps[i], in);
			}
			return in;
		}
		else {
			GArr_Resolutions.emplace_back(res);
			return 0;
		}
	}

	int inArr_Resolutions(std::string& compareName) {
		for (int i = 0; i < GArr_Resolutions.size(); ++i) {
			if (pstring::icompare(GArr_Resolutions[i].Name,compareName))
				return i;
		}
		return (-1);
	}

	void addToResolution(rSystemOps& so, int rpos) {
		GArr_Resolutions[rpos].SystemOps.emplace_back(so);
	}

}
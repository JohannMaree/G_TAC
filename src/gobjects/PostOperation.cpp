#include "gobject.h"

namespace gobject {

	void defaultPostOperation(int posPostProcess) {

		PostOperation pop;
		pop.Name = defNamePostOperation;
		pop.NameOfPostProcessing = GArr_PostProcesses[posPostProcess].Name;

		postOp opT;
		opT.OperationType = "Print";
		opT.OperationArgs.push_back(charT);
		opT.OperationArgs.push_back("OnElementsOf " + TDomain);
		opT.OperationArgs.push_back("File \"" + charTfile + "\"");
		pop.Operations.push_back(opT);

		postOp opQ;
		opQ.OperationType = "Print";
		opQ.OperationArgs.push_back(charQ);
		opQ.OperationArgs.push_back("OnElementsOf " + TDomain);
		opQ.OperationArgs.push_back("File \"" + charQfile + "\"");
		pop.Operations.push_back(opQ);

		addPostOperation(pop);
	}

	int addPostOperation(PostOperation& po) {
		int in = inArr_PostOperation(po.Name);
		if (in >= 0) {
			if (pstring::icompare(po.NameOfPostProcessing, GArr_PostOperations[in].NameOfPostProcessing)) {
				for (ind i = 0; i < po.Operations.size(); ++i) {
					addToPostOperation(po.Operations[i], in);
				}
			}
			else {
				PostOperation poNew = po;
				poNew.Name += "_" + po.NameOfPostProcessing;
				GArr_PostOperations.push_back(poNew);
				in = static_cast<int>(GArr_PostOperations.size() - 1);
			}
			return in;
		}
		else {
			GArr_PostOperations.emplace_back(po);
			return 0;
		}
	}

	int inArr_PostOperation(std::string& compareName) {
		for (int i = 0; i < GArr_PostOperations.size(); ++i) {
			if (pstring::icompare(GArr_PostOperations[i].Name, compareName))
				return i;
		}
		return (-1);
	}

	void addToPostOperation(postOp& pop, int ppos) {
		GArr_PostOperations[ppos].Operations.emplace_back(pop);
	}

}
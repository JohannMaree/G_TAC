#include "PostOperation.h"
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

		GArr_PostOperations.push_back(pop);
	}

}
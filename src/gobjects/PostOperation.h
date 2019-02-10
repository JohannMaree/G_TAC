#pragma once
#include <string>
#include <vector>

namespace gobject {

	struct postOp {
		std::string OperationType;
		std::vector<std::string> OperationArgs;
	};

	class PostOperation {
	public:
		std::string Name;
		std::string NameOfPostProcessing;
		std::vector<postOp> Operations;
	};

	void defaultPostOperation(int posPostProc = 0);

}
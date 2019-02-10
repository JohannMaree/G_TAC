#pragma once
#include <string>

namespace generate {

	std::string globals();

	std::string group();				//Object 1
	std::string function();				//Object 2
	std::string constraint();			//Object 3
	std::string functionspace();		//Object 4
	std::string jacobian();				//Object 5
	std::string integration();			//Object 6
	std::string formulation();			//Object 7
	std::string resolution();			//Object 8
	std::string postprocessing();		//Object 9
	std::string postoperation();		//Object 10

}

#pragma once
#include <string>
#include <vector>

namespace command {

	int process(const std::string& comm);
	void exit();
	int validate(const std::string& commType);
	std::string clean(const std::string& str);
	void initialise();
	int processArgV(int argc, char* argv[]);

}//end namespace command

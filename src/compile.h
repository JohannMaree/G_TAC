#pragma once
#include <string>
#include <vector>

namespace compile {

	void validate(const std::vector<std::string>& parm);
	void defaults(const std::string& filename);
	void writeASCII(const std::string& filename);

	void compileFromRegions();

	void openGlobalGroups();
	void closeGlobalGroups();

}

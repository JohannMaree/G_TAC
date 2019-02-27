#pragma once

#include <string>
#include <vector>

namespace gobject {

	struct rSystemOps {
		std::string Name;
		std::string NameOfFormulation;
		std::vector<std::string> Operations;
	};

	class Resolution {
	public:
		std::string Name;
		std::vector<rSystemOps> SystemOps;
	};

	void defaultResolution(int posFormulation);

	int addResolution(Resolution& res);
	int inArr_Resolutions(std::string& compareName);

	void addToResolution(rSystemOps& so, int rpos = 0);

}

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
}

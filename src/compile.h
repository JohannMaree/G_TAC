#pragma once
#include <string>
#include <vector>
#include "region.h"

namespace compile {

	void validate(const std::vector<std::string>& parm);
	void defaults(const std::string& filename);
	void writeASCII(const std::string& filename);

	void compileFromRegions();

	void rgnConduction(regions::region& rgn);
	void rgnConvection(regions::region& rgn);
	void rgnRadiation(regions::region& rgn);
	void rgnGeneration(regions::region& rgn);
	void rgnBCType1(regions::region& rgn);
	void rgnBCType2(regions::region& rgn);
	void rgnTempDisc(regions::region& rgn);

	void openGlobalGroups();
	void closeGlobalGroups();

}

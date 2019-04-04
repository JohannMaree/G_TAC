#pragma once
#include <string>
#include <vector>
#include "region.h"

namespace compile {

	bool validate(const std::vector<std::string>& parm);
	void createNL_Variables(int type = 1);
	void defaults(const std::string& filename);
	void writeASCII(const std::string& filename);

	void regionPreCompile();
	void compileFromRegions();

	void rgnConduction(regions::region& rgn);
	void rgnConvection(regions::region& rgn);
	void rgnRadiation(regions::region& rgn);
	void rgnGeneration(regions::region& rgn);
	void rgnTemperature(regions::region& rgn);
	void rgnHeatflux(regions::region& rgn);
	void rgnTempDisc(regions::region& rgn);

	void openGlobalGroups();
	void closeGlobalGroups();

}//end namespace compile

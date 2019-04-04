#include "command.h"
#include "io/proxCommands.h"
#include "io/proxFiles.h"
#include "io/proxGmsh.h"
#include "variable.h"
#include "region.h"
#include "compile.h"
#include "execute.h"
#include <iostream>	//TEST

namespace command {

	void switchcase(const int ctype, const std::vector<std::string>& comm) {
		switch (ctype)
		{
		case 2:		//HELP command
			execomm::help(comm);
			break;
		case 3:		//LOAD command
			if (execomm::load(comm))
				execomm::addLogEntry(comm);
			break;
		case 4:		//SAVE command
			execomm::save(comm);
			break;
		case 5:		//CLCM command
			execomm::clcm();
			break;
		case 6:		//LIST command
			execomm::list(comm);
			break;
		case 7:		//VAR command
			if (variables::validate(comm, 0))
				execomm::addLogEntry(comm);
			break;
		case 8:		//IVAR command
			if(variables::validate(comm,1))
				execomm::addLogEntry(comm);
			break;
		case 9:		//RGN command
			if(regions::validate(comm,1))
				execomm::addLogEntry(comm);
			break;
		case 10:	//GRGN command
			if(regions::validate(comm,2))
				execomm::addLogEntry(comm);
			break;
		case 11:	//SET command
			if (execomm::set(comm))
				execomm::addLogEntry(comm);
			break;
		case 12:	//COMPILE command
			if (compile::validate(comm))
				execomm::addLogEntry(comm);
			break;
		case 13:	//DEL command
			execomm::del(comm);
			break;
		case 14:	//GMSH command
			if(pgmsh::validate(comm))
				execomm::addLogEntry(comm);
			break;
		case 15:	//GETDP command
			if (pgmsh::runGetDP(comm))
				execomm::addLogEntry(comm);
			break;


		default:
			std::cerr << "command not recognised. use HELP for a list of available commands.\n";
			break;
		}
	}

}//end namespace command


#include "command.h"
#include "proxCommands.h"
#include "proxFiles.h"
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
			if(variables::validate(comm,1))
				
			break;
		case 8:		//IVAR command
			if(variables::validate(comm,2))

			break;
		case 9:		//RGN command
			if(regions::validate(comm,1))

			break;
		case 10:	//GRGN command
			if(regions::validate(comm,2))

			break;
		case 11:	//SET command
			execomm::set(comm);
			break;
		case 12:	//COMPILE command
			compile::validate(comm);
			break;


		default:
			std::cerr << "command not recognised. use HELP for a list of available commands.\n";
			break;
		}
	}
}




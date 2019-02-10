#pragma once
#include <string>
#include <vector>
#include <memory>

namespace variables {

	struct constant {
		bool exists = false;
		std::string value;
	};

	class variable {	//Type0
	public:
		std::string name;
		constant description;
		float value;
		short int type = 0;
		bool used = false;
	};

	class ivariable: public variable {//Type(1,2,3)
	public:
		//Type1
		constant menu;
		//Type2
		struct Bounds {
			constant max;
			constant min;
			constant step;
		} bounds;
		//Type3
		std::vector<std::string> choices;
		
	};

	const std::string iVarParmList[] = {
		"DESC",		//0
		"MENU",		//1
		"MIN",		//2
		"MAX",		//3
		"STEP",		//4
		"CHOICES",	//5
	};

	void validate(const std::vector<std::string>& parm, int varType);
	void addVar(const std::vector<std::string>& parm);
	void addIVar(const std::vector<std::string>& parm);
	std::string listVariables();
	std::string listIVariables();
	std::string listAllVariables();

}

extern std::vector<std::unique_ptr<variables::variable>> GRegister_Variables;






#pragma once
#include <string>
#include <vector>
#include <memory>

namespace variables {

	struct constant {
		bool exists = false;
		std::string value;
	};

	struct spair {
		std::string one;
		std::string two;
	};

	class variable {
	public:
		//Type0
		std::string name;
		constant description;
		double value;
		short int type = 0;
		int used = 0;
	};

	class ivariable: public variable {
	public:
		//Type1
		constant menu;
		constant visible;
		//Type2
		struct Bounds {
			constant max;
			constant min;
			constant step;
		} bounds;
		//Type3
		std::vector<std::string> choices;
		
	};

	class cvariable : public variable {
	public:
		//Type(-1)
		std::vector<spair> spairs;
	};

	const std::string varParmList[] = {
		"DESC",		//0
		"PAIRS",	//1

	};

	const std::string iVarParmList[] = {
		"DESC",		//0
		"MENU",		//1
		"MIN",		//2
		"MAX",		//3
		"STEP",		//4
		"CHOICES",	//5

	};

	bool validate(const std::vector<std::string>& parm, int varType);
	bool addVar(const std::vector<std::string>& parm);
	bool addIVar(const std::vector<std::string>& parm);
	void setProperties(const std::string& comm, variable* v);
	bool setVar(const std::vector<std::string>& parm);

	int inRegister(const std::string& vname);

	std::string listVariables();
	std::string listIVariables();
	std::string listAllVariables();

	void clearVariable(int pos = (-1));

}//end namespace variables

extern std::vector<std::unique_ptr<variables::variable>> GRegister_Variables;






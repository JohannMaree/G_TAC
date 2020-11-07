#include "variable.h"
#include "io/proxStrings.h"
#include "io/proxFiles.h"
#include <iostream> //TEST
#include <sstream>

std::vector<std::unique_ptr<variables::variable>> GRegister_Variables;

namespace variables {

	bool validate(const std::vector<std::string>& parm, int varType) {
		if (varType == 0) {			//addVar Command
			return addVar(parm);
		}
		else if (varType == 1) {	//addIVar COmmand
			return addIVar(parm);
		}
		else if (varType == -1) {	//Unspecified Type
			if (pstring::icompare(parm[0], "VAR")) {
				return addVar(parm);
			}
			else if (pstring::icompare(parm[0], "IVAR")) {
				return addIVar(parm);
			}
		}
		return false;
	}

	bool addVar(const std::vector<std::string>& parm) {
		variable x;
		std::vector<std::string> strs;
		strs = pstring::lex(parm[1],'=');
		x.name = strs[0];
		int in = inRegister(x.name);
		if (in == (-1)) {
			if (strs.size() > 1) {
				x.value = std::stof(strs[1]);
			}
			x.type = 0;
			ind psize = parm.size();
			if (psize > 2) {
				for (ind i = 2; i < psize; ++i) {
					setProperties(parm[i], &x);
				}
			}
			GRegister_Variables.push_back(std::make_unique<variable>(x));
			return true;
		}
		else {
			std::cerr << "Var:" << x.name << " already exists.\n";
			return false;
		}
	}

	bool addIVar(const std::vector<std::string>& parm) {
		ivariable x;
		std::vector<std::string> def;
		def = pstring::lex(parm[1], '=');
		x.name = def[0];
		int in = inRegister(x.name);
		if (in == (-1)) {
			if (def.size() > 1) {
				x.value = std::stof(def[1]);
			}
			x.type = 1;
			ind psize = parm.size();
			if (psize > 2) {
				for (ind i = 2; i < psize; ++i) {
					setProperties(parm[i], &x);
				}
			}
			GRegister_Variables.push_back(std::make_unique<ivariable>(x));
			return true;
		}
		else {
			std::cerr << "IVar:" << x.name << " already exists.\n";
			return false;
		}
	}

	void setProperties(const std::string& comm,variable* v) {
		std::vector<std::string> pstr = pstring::lex(comm, '=');
		
		//Var Properties
		if (v->type <= 0) {
			if (pstring::ifind(comm, varParmList[0])) {				//DESC
				v->description.value = pstr[1];
				v->description.exists = true;
			}
			else if (pstring::ifind(comm, varParmList[1])) {		//PAIRS
				v->type = -1;
				std::vector<std::string> cstr = pstring::lex(pstr[1], ';');
				for (ind i = 0; i < cstr.size(); ++i) {
					std::vector<std::string> tmp = pstring::lex(cstr[i], ',');
					if (!tmp.empty()) {
						spair tp;
						tp.one = tmp[0];
						tp.two = tmp[1];
						v->spairs.emplace_back(tp);
					}
				}
			}	
			else if (pstring::ifind(comm, varParmList[2])) {		//TENSOR
				v->type = -2;
				std::vector<std::string> cstr = pstring::lex(pstr[1], ';');
				for (ind i = 0; i < cstr.size(); ++i) {
					if (!cstr.empty()) {
						v->tensorRow.emplace_back(cstr[i]);
					}
				}
			}
		}
		//IVar Properties
		if (v->type > 0) {
			ivariable* iv = static_cast<ivariable*>(v);
			if (pstring::ifind(comm, iVarParmList[0])) {			//DESC
				v->description.value = pstr[1];
				v->description.exists = true;
			}
			else if (pstring::ifind(comm, iVarParmList[1])) {		//MENU
				iv->menu.value = pstr[1];
				iv->menu.exists = true;
			}
			else if (pstring::ifind(comm, iVarParmList[2])) {		//MIN
				iv->type = 2;
				iv->bounds.min.value = pstr[1];
				iv->bounds.min.exists = true;
			}
			else if (pstring::ifind(comm, iVarParmList[3])) {		//MAX
				iv->type = 2;
				iv->bounds.max.value = pstr[1];
				iv->bounds.max.exists = true;
			}
			else if (pstring::ifind(comm, iVarParmList[4])) {		//STEP
				iv->type = 2;
				iv->bounds.step.value = pstr[1];
				iv->bounds.step.exists = true;
			}
			else if (pstring::ifind(comm, iVarParmList[5])) {		//CHOICES
				iv->type = 3;
				std::vector<std::string> cstr = pstring::lex(pstr[1], ',');
				iv->choices = cstr;
			}
		}
	}

	bool setVar(const std::vector<std::string>& parm) {
		std::vector<std::string> pstr = pstring::lex(parm[1], '=');
		int in = inRegister(pstr[0]);
		size_t pars = parm.size();
		if (in >= 0) {
			if (pstr[0] != "") {
				try {
					GRegister_Variables[in]->value = std::stof(pstr[1]);
				}
				catch (std::invalid_argument i) {
					std::cerr << "ERROR:" << parm[1] << " invalid value specified.\n";
				}
			}
			if (pars > 2) {
				for (ind i = 2; i < pars; ++i) {
					setProperties(parm[i], GRegister_Variables[in].get());
				}
			}
			return true;
		}
		else {
			std::cerr << "Variable:" << parm[1] << " not found.\n";
			return false;
		}
	}

	int inRegister(const std::string& vname) {
		for (int i = 0; i < GRegister_Variables.size(); ++i) {
			if (pstring::icompare(GRegister_Variables[i]->name, vname))
				return i;
		}
		return (-1);
	}

	std::string listVariables() {
		ind s = GRegister_Variables.size();
		std::ostringstream ret;
		if (s > 0) {
			//LIST All VAR-type variables
			ret << "VAR: \t\tTYPE:\t\tVALUE:\t\t\n";
			for (ind i = 0; i < s; ++i) {
				if (GRegister_Variables[i]->type == 0) {			//VAR
					variable* v = GRegister_Variables[i].get();
					ret << v->name << "\t\t";
					ret << "Type" << v->type << "\t\t";
					ret << v->value << "\t\t";
					if (v->description.exists) {
						ret << "Desc:" << v->description.value << ", ";
					}
					ret << "\n";
				}
				else if (GRegister_Variables[i]->type == -1) {		//Pair VAR
					variable* v = GRegister_Variables[i].get();
					ret << v->name << "\t\t";
					ret << "Type" << v->type << "\t\t";
					if (v->description.exists) {
						ret << "Desc:" << v->description.value << ", ";
					}
					ret << "Pairs:[";
					for (ind k = 0; k < v->spairs.size(); ++k) {
						ret << v->spairs[k].one << ", " << v->spairs[k].two << "; ";
					}
					ret << "]\n";
				}
				else if (GRegister_Variables[i]->type == -2) {		//Tensor VAR
					variable* v = GRegister_Variables[i].get();
					ret << v->name << "\t\t";
					ret << "Type" << v->type << "\t\t";
					if (v->description.exists) {
						ret << "Desc:" << v->description.value << ", ";
					}
					ret << "Tensor:[";
					for (ind k = 0; k < v->tensorRow.size(); ++k) {
						ret << v->tensorRow[k] << "; ";
					}
					ret << "]\n";
				}
			}
			ret << std::endl;
		}
		else {
			ret << "0 Variables.\n";
		}
		return ret.str();
	}

	std::string listIVariables() {
		ind s = GRegister_Variables.size();
		std::ostringstream ret;
		if (s > 0) {
			ret << "IVAR: \t\tTYPE:\t\tVALUE:\t\t\n";
			for (ind i = 0; i < s; ++i) {
				
				if (GRegister_Variables[i]->type == 1) {		//Basic IVAR
					ivariable* v = static_cast<ivariable*>(GRegister_Variables[i].get());
					ret << v->name << "\t\t";
					ret << "Type" << v->type << "\t\t";
					ret << v->value << "\t\t";
					if (v->description.exists) {
						ret << "Desc:" << v->description.value << ", ";
					}
					if (v->menu.exists) {
						ret << "Menu:" << v->menu.value << ", ";
					}
					ret << "\n";
				}
				else if (GRegister_Variables[i]->type == 2) {		//Bounded IVAR
					ivariable* v = static_cast<ivariable*>(GRegister_Variables[i].get());
					ret << v->name << "\t\t";
					ret << "Type" << v->type << "\t\t";
					ret << v->value << "\t\t";
					if (v->description.exists) {
						ret << "Desc:" << v->description.value << ", ";
					}
					if (v->menu.exists) {
						ret << "Menu:" << v->menu.value << ", ";
					}
					ret << "Bounds: ";
					if (v->bounds.max.exists) {
						ret << "MAX:" << v->bounds.max.value << ", ";
					}
					if (v->bounds.min.exists) {
						ret << "MIN:" << v->bounds.min.value << ", ";
					}
					if (v->bounds.step.exists) {
						ret << "STEP:" << v->bounds.step.value << ", ";
					}
					ret << "\n";
				}
				else if (GRegister_Variables[i]->type == 3) {		//Choice IVAR
					ivariable* v = static_cast<ivariable*>(GRegister_Variables[i].get());
					ret << v->name << "\t\t";
					ret << "Type" << v->type << "\t\t";
					ret << v->value << "\t\t";
					if (v->description.exists) {
						ret << "Desc:" << v->description.value << ", ";
					}
					if (v->menu.exists) {
						ret << "Menu:" << v->menu.value << ", ";
					}
					ret << "Choices: ";
					for (ind k = 0; k < v->choices.size(); ++k) {
						ret << v->choices[k] << ", ";
					}
					ret << "\n";
				}
			}
			ret << std::endl;
		}
		else {
			ret << "0 I_Variables.\n";
		}
		return ret.str();
	}

	std::string listAllVariables() {
		std::string v = listVariables();
		std::string iv = listIVariables();
		std::string s;
		if (v.at(0) == '0') {
			if (iv.at(0) == '0') {
				s = "0 Variables/I_Variables.\n";
			}
			else {
				s = v + iv;
			}
		}
		else {
			s = v + iv;
		}
		return s;
	}

	void clearVariable(int pos) {
		if (pos >= 0) {
			GRegister_Variables.erase(GRegister_Variables.begin() + pos);
		}
		else {
			GRegister_Variables.clear();
		}
	}

}//end namespace variables
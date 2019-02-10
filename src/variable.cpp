#include "variable.h"
#include "proxStrings.h"
#include "proxFiles.h"
#include <iostream> //TEST
#include <sstream>

std::vector<std::unique_ptr<variables::variable>> GRegister_Variables;

namespace variables {

	void validate(const std::vector<std::string>& parm, int varType) {
		if (varType == 1) {			//addVar Command
			addVar(parm);
		}
		else if (varType == 2) {	//addIVar COmmand
			addIVar(parm);
		}
	}

	void addVar(const std::vector<std::string>& parm) {
		variable x;
		std::vector<std::string> strs;
		strs = pstring::lex(parm[1],'=');
		x.name = strs[0];
		x.value = std::stof(strs[1]);
		x.type = 0;
		ind psize = parm.size();
		if (psize > 2) {
			for (ind i = 2; i < psize; ++i) {
				std::vector<std::string> pstr = pstring::lex(parm[i], '=');
				if (pstring::ifind(parm[i], iVarParmList[0])) {				//DESC
					x.description.value = pstr[1];
					x.description.exists = true;
				}
			}
		}
		GRegister_Variables.push_back(std::make_unique<variable>(x));
	}

	void addIVar(const std::vector<std::string>& parm) {
		ivariable x;
		std::vector<std::string> def;
		def = pstring::lex(parm[1], '=');
		x.name = def[0];
		x.value = std::stof(def[1]);
		x.type = 1;
		ind psize = parm.size();
		if (psize > 2) {
			for (ind i = 2; i < psize; ++i) {
				std::vector<std::string> pstr = pstring::lex(parm[i], '=');
				//Sub_COmmand cases
				if (pstring::ifind(parm[i], iVarParmList[0])) {				//DESC
					x.description.value = pstr[1];
					x.description.exists = true;
				}
				else if (pstring::ifind(parm[i], iVarParmList[1])) {		//MENU
					x.menu.value = pstr[1];
					x.menu.exists = true;
				}
				else if (pstring::ifind(parm[i], iVarParmList[2])) {		//MIN
					x.type = 2;
					x.bounds.min.value = pstr[1];
					x.bounds.min.exists = true;
				}
				else if (pstring::ifind(parm[i], iVarParmList[3])) {		//MAX
					x.type = 2;
					x.bounds.max.value = pstr[1];
					x.bounds.max.exists = true;
				}
				else if (pstring::ifind(parm[i], iVarParmList[4])) {		//STEP
					x.type = 2;
					x.bounds.step.value = pstr[1];
					x.bounds.step.exists = true;
				}
				else if (pstring::ifind(parm[i], iVarParmList[5])) {		//CHOICES
					x.type = 3;			
					std::vector<std::string> cstr = pstring::lex(pstr[1], ',');
					x.choices = cstr;
				}
			}
		}
		GRegister_Variables.push_back(std::make_unique<ivariable>(x));
	}

	std::string listVariables() {
		ind s = GRegister_Variables.size();
		std::ostringstream ret;
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
				ret << "Used:" << v->used;
				ret << "\n";
			}
		}
		ret << std::endl;
		return ret.str();
	}

	std::string listIVariables() {
		ind s = GRegister_Variables.size();
		std::ostringstream ret;
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
				ret << "Used:" << v->used << ", ";
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
				ret << "Used:" << v->used << ", ";
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
					ret << "STEP:" << v->bounds.step.value;
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
				ret << "Used:" << v->used << ", ";
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
		return ret.str();
	}

	std::string listAllVariables() {
		ind s = GRegister_Variables.size();
		std::ostringstream ret;
		//LIST All created variables
		ret << "VAR/IVAR:\tTYPE:\t\tVALUE:\n";
		for (ind i = 0; i < s; ++i) {
			if (GRegister_Variables[i]->type == 0) {			//VAR
				variable* v = GRegister_Variables[i].get();
				ret << v->name << "\t\t";
				ret << "Type" << v->type << "\t\t";
				ret << v->value << "\t\t";
				if (v->description.exists) {
					ret << "Desc:" << v->description.value << ", ";
				}
				ret << "Used:" << v->used;
				ret << "\n";
			}
			else if (GRegister_Variables[i]->type == 1) {		//Basic IVAR
				ivariable* v = static_cast<ivariable*>(GRegister_Variables[i].get());
				ret << v->name << "\t\t";
				ret << "Type" << v->type << "\t\t";
				ret << v->value << "\t\t";
				if (v->description.exists) {
					ret << "Desc:" << v->description.value << ", ";
				}
				ret << "Used:" << v->used << ", ";
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
				ret << "Used:" << v->used << ", ";
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
					ret << "STEP:" << v->bounds.step.value;
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
				ret << "Used:" << v->used << ", ";
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
		return ret.str();
	}

}
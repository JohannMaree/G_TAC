#pragma once
#include <string>
#include <vector>

typedef std::size_t ind;

namespace pstring {

	std::vector<std::string> lex(const std::string& str, char delim = ' ');
	bool icompare(const std::string& str, const std::string& ctxt);
	bool ccompare(const char& a, const char& b);
	bool ifind(const std::string& search, const std::string& term);
	bool find(const std::string& search, const std::string& term);
	void removePreWhitespace(std::string* str, const std::string& ws = " \t");
	void removePostWhitespace(std::string* str, const std::string& ws = " \t");
	void condenseWhitespace(std::string* str, const std::string& ws = " \t", char delim = ' ');
	bool checkExtension(const std::string& filename, const std::string& ext);
	bool isNumber(const std::string& str);

}//end namespace pstring

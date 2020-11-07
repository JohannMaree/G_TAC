#include "proxStrings.h"
#include <cctype>

#include <iostream>		//TEST	

namespace pstring {

	std::vector<std::string> lex(const std::string& str, char delim) {
		std::vector<std::string> retv;
		if (str.empty()) {
			return retv;
		}

		ind cm = str.find("//");
		std::string sub;
		if (cm != str.npos) {
			sub = str.substr(0, cm - 1);
		}
		else {
			sub = str;
		}

		ind ct = sub.find(delim);
		if (ct != std::string::npos) {							//If more than 1 token:
			std::string token;
			ind len = sub.size();
			retv.push_back(sub.substr(0, ct));					//Put Command Type in slot[0] of vector ret
			ind pl = ct + 1;
			for (ind i = pl; i < len; ++i) {					//Put Command Parameters in slots[1 to n] of vector ret
				if (sub.at(i) == delim) {
					token = sub.substr(pl, i - pl);
					retv.push_back(token);
					pl = i + 1;
				}
			}
			retv.push_back(sub.substr(pl, len - 1));
		}
		else {													//If only 1 token:
			retv.push_back(sub);
		}
		return retv;
	}

	/* Case insensitive String comparison */
	bool icompare(const std::string& str, const std::string& ctxt) {
		if (str.size() == ctxt.size()) {
			return std::equal(ctxt.begin(), ctxt.end(), str.begin(), ccompare);
		}
		else {
			return false;
		}
	}

	/* Case insensitive Char comparison */
	bool ccompare(const char& a, const char& b) {
		if (a == b) {
			return true;
		}
		else if (std::tolower(a) == std::tolower(b)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool ifind(const std::string& search, const std::string& term) {
		bool loop = true, inloop = true;
		ind pSearch = 0;
		ind pCount = 1;
		while (loop) {
			if (ccompare(search[pSearch], term[0])) {
				while (inloop) {
					if (ccompare(search[pSearch + pCount], term[pCount])) {
						++pCount;
					}
					else {
						if (pCount == term.size()) {
							return true;
						}
						else {
							pCount = 1;
							inloop = false;
						}
					}
				}
				inloop = true;
			}
			else if (pSearch == search.size()) {
				loop = false;
			}
			++pSearch;
		}
		return loop;
	}

	bool find(const std::string& search, const std::string& term) {
		if (search.find(term) != std::string::npos) {
			return true;
		}
		return false;
	}

	void removePreWhitespace(std::string* str, const std::string& ws) {
		str->erase(0, str->find_first_not_of(ws));
	}

	void removePostWhitespace(std::string* str, const std::string& ws) {
		str->erase(str->find_last_not_of(ws) + 1);
	}

	void condenseWhitespace(std::string* str, const std::string& ws, char delim) {
		ind s = (str)->find_first_of(ws);
		while (s != std::string::npos) {
			ind e = (str)->find_first_not_of(ws, s);
			ind r = e - s;
			str->replace(s,r,1,delim);
			r = s + 1;
			s = (str)->find_first_of(ws, r);
		}
	}

	bool checkExtension(const std::string& filename, const std::string& ext) {
		std::string fext = filename.substr(filename.find_last_of('.') + 1);
		return icompare(fext,ext);
	}

	bool isNumber(const std::string& str) {
		if (str.empty()) {
			return false;
		}
		else {
			return (str.find_first_not_of("0123456789+/-.") == std::string::npos);
		}
	}

	bool isWholeNumber(const std::string& str) {
		if (str.empty()) {
			return false;
		}
		else {
			return (str.find_first_not_of("0123456789") == std::string::npos);
		}
	}

}//end namespace pstring
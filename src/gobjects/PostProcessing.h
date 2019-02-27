#pragma once

#include <string>
#include <vector>

namespace gobject {

	struct postQuantity {
		std::string Name;
		std::string Term;
		std::string Domain;
		std::string Jacobian;
	};

	class PostProcessing {
	public:
		std::string Name;
		std::string NameOfFormulation;
		std::vector<postQuantity> Quantities;
	};

	int defaultPostProcessing(int posFormulation);

	int addPostProcessing(PostProcessing& pp);
	int inArr_PostProcessing(std::string& compareName);

	void addToPostProcessing(postQuantity& pq, int ppos = 0);
	int inPostQuantities(std::string compareName, int ppos = 0);

}
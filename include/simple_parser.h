#pragma once

#include "polynom.h"
#include <unordered_map>
#include <set>
#include <string>

class PolynomTranslator {
public:
	// Container for Polynoms
	std::unordered_map<std::string, Polynom> Polynoms;

	/*
	There are three modes:
	1) Entering and saving polynom
	2) Performing a mathematical operation on saved polynomials and returning answer
	3) 2 + saving result as new polynom
	*/

	std::string execute(std::string input);

	// Parse string into the polynom
	Polynom polynomParser(std::string input);

	// Checks name for validity, also return 1, if Polynom with this name already exists
	bool nameCheck(std::string name);
};
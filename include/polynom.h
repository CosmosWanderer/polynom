#pragma once

#include <iostream>
#include <string>
#include "list.h"
#include "monom.h"

class Polynom{
private:
	List<Monom> Monoms;
	int size = 0;

public:
	Polynom();
	Polynom(double coef);
	Polynom(const Monom& m);

	/* --- Some functionality --- */
	Polynom addMonom(const Monom& m);
	Polynom addInTheEnd(const Monom& m);
	void cleanZeroedMonoms();

	/* --- Operations --- */
	Polynom operator+(const Polynom& p) const;
	Polynom operator-(const Polynom& p) const;
	Polynom operator*(const Polynom& p) const;

	// Transform Monom into polynom and use fucntions above
	Polynom operator+(const Monom& m) const;
	Polynom operator-(const Monom& m) const;
	Polynom operator*(const Monom& m) const;

	Polynom operator+(const double nm) const;
	Polynom operator-(const double nm) const;
	Polynom operator*(const double nm) const;
	Polynom operator/(const double nm) const;

	/* --- Other --- */
	std::string getValue() const; 
};
#pragma once

#include <iostream>
#include <string>
#include "list.h"
//#include "polynom.h"

class Polynom;

class Monom {
private:
	// monom = koef * x^i * y*j * z*k
	static constexpr int powMask = 1023;
	double coef = 0; // Coefficient
	int powers = 0; // (2)none - (10)i - (10)j - (10)k -- just a way to store powers 

public:
	Monom(double c = 0, int p = 0);
	Monom(double c, int px, int py, int pz);

	/* --- Getters --- */
	int getPowers() const;
	double getCoef() const;
	int getXPower() const;
	int getYPower() const;
	int getZPower() const;

	/* --- Setters --- */
	void setPowers(int p);
	void setPowers(int px, int py, int pz);
	void setCoef(double coef);
	void setXPower(int px);
	void setYPower(int py);
	void setZPower(int pz);

	/* --- Operations --- */
	Monom operator+(const Monom& m) const;
	Monom operator-(const Monom& m) const;
	Monom operator*(const Monom& m) const;
	Monom operator*(double mult) const;
	Monom operator/(const Monom& m) const;
	Monom operator/(double div) const;
	bool operator==(const Monom& m) const;
	bool operator!=(const Monom& m) const;

	/* --- Polynom related --- */
	// Transform monom into polynome, and use polynom operators
	Polynom operator+(const Polynom& p) const;
	Polynom operator-(const Polynom& p) const;
	Polynom operator*(const Polynom& p) const;

	/* --- Other --- */
	std::string getValue() const;
};

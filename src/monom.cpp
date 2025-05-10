#include "monom.h"
#include <iostream>
#include <string>
#include "list.h"
#include "polynom.h"


Monom::Monom(double c, int p) : coef(c), powers(p) {};
Monom::Monom(double c, int px, int py, int pz) : coef(c) {
	if (px > 1000 || py > 1000 || pz > 1000) throw std::runtime_error("Powers are to high");
	powers = (px << 20) | (py << 10) | pz;
}

/* --- Getters --- */
int Monom::getPowers() const {
	return powers;
}
double Monom::getCoef() const {
	return coef;
}

// Using mask to get the exact bytes we need to return
int Monom::getXPower() const {
	return (powers >> 20) & powMask;
}
int Monom::getYPower() const {
	return (powers >> 10) & powMask;
}
int Monom::getZPower() const {
	return powers & powMask;
}

/* --- Setters --- */
void Monom::setPowers(int p) {
	powers = p;
}
void Monom::setPowers(int px, int py, int pz) {
	if (px > 1000 || py > 1000 || pz > 1000) throw std::runtime_error("Powers are to high");

	powers = (px << 20) | (py << 10) | pz;
}
void Monom::setCoef(double c) {
	coef = c;
}
void Monom::setXPower(int px) {
	int py = getYPower();
	int pz = getZPower();
	setPowers(px, py, pz);
}
void Monom::setYPower(int py) {
	int px = getXPower();
	int pz = getZPower();
	setPowers(px, py, pz);
}
void Monom::setZPower(int pz) {
	int py = getYPower();
	int px = getXPower();
	setPowers(px, py, pz);
}

/* --- Operations --- */
Monom Monom::operator+(const Monom& m) const {
	if (powers != m.getPowers()) {
		throw std::runtime_error("You cannot add polynoms with unequal powers");
	}

	return Monom(getCoef() + m.getCoef(), powers);
}
Monom Monom::operator-(const Monom& m) const {
	if (powers != m.getPowers()) throw std::runtime_error("You cannot subtract polynoms with unequal powers");

	return Monom(coef - m.getCoef(), powers);
}
Monom Monom::operator*(const Monom& m) const {
	double resCoef = coef * m.getCoef();
	int resPX = getXPower() + m.getXPower();
	int resPY = getYPower() + m.getYPower();
	int resPZ = getZPower() + m.getZPower();

	return Monom(resCoef, resPX, resPY, resPZ);
}
Monom Monom::operator*(double mult) const {
	Monom res = *this;
	res.setCoef(res.getCoef() * mult);
	return res;
}
Monom Monom::operator/(const Monom& m) const {
	if (m.getCoef() == 0) throw std::runtime_error("Division by zero");

	double resCoef = coef / m.getCoef();
	int resPX = getXPower() - m.getXPower();
	int resPY = getYPower() - m.getYPower();
	int resPZ = getZPower() - m.getZPower();

	return Monom(resCoef, resPX, resPY, resPZ);
}
Monom Monom::operator/(double div) const {
	if (div == 0) throw std::runtime_error("Division by zero");

	Monom res = *this;
	res.setCoef(res.getCoef() / div);
	return res;
}
bool Monom::operator==(const Monom& m) const {
	return ((coef == m.getCoef()) && (powers == m.getPowers()));
}
bool Monom::operator!=(const Monom& m) const {
	return !(*this == m);
}

/* --- Polynom related --- */
Polynom Monom::operator+(const Polynom& p) const {
	Polynom p1(*this);
	return p1 + p;
}
Polynom Monom::operator-(const Polynom& p) const {
	Polynom p1(*this);
	return p1 - p;
}
Polynom Monom::operator*(const Polynom& p) const {
	Polynom p1(*this);
	return p1 * p;
}

/* --- Other --- */
std::string Monom::getValue() const {
	std::string S = std::to_string(getCoef());
	int pntr = S.size() - 1;

	while (pntr != 1 && S[pntr] == '0' && S[pntr - 1] == '0') {
		S.pop_back();
		pntr--;
	}

	if (getCoef() < 0) S = "(" + S + ")";

	S += " * ";

	S += "x^" + std::to_string(getXPower());
	S += "y^" + std::to_string(getYPower());
	S += "z^" + std::to_string(getZPower());
	return S;
}


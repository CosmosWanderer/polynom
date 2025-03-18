#include "polynom.h"
#include <iostream>
#include <string>
#include "list.h"
#include "monom.h"


Polynom::Polynom() {}
Polynom::Polynom(const Monom& m) {
	addMonom(m);
}
Polynom::Polynom(double coef) {
	Monom m(coef, 0, 0, 0);
	addMonom(m);
}

/* --- Some functionality --- */
Polynom Polynom::addMonom(const Monom& m) {
	// If zero, then dont do anything
	if (m.getCoef() == 0) return *this;

	// If there are already monom like ths in polynome
	int powers = m.getPowers();
	for (auto It = Monoms.begin(); It != Monoms.end(); It++) {
		if (It->getPowers() == powers) {
			It->setCoef(It->getCoef() + m.getCoef());
			return *this;
		}

		// If powers of monoms became bigger than powers of new one
		if (It->getPowers() > powers) {
			Monoms.insert_before(m, It);
			size++;
			return *this;
		}
	}

	// If all powers of monoms are lower, then add it to the end;
	Monoms.insert_back(m);
	size++;

	cleanZeroedMonoms();
	return *this;
}
Polynom Polynom::addInTheEnd(const Monom& m) {
	Monoms.insert_back(m);
	size++;
	return *this;
}
void Polynom::cleanZeroedMonoms() {
	auto It = Monoms.begin();
	while (It != Monoms.end()) {
		if (It->getCoef() == 0) It = Monoms.delete_node(It);
		else It++;
	}
}



/* --- Operations --- */
Polynom Polynom::operator+(const Polynom& p) const {
	Polynom res;

	auto It1 = Monoms.begin();
	auto It2 = p.Monoms.begin();

	// Walking through polynoms
	while (It1 != Monoms.end() && It2 != p.Monoms.end()) {
		if (It1->getPowers() == It2->getPowers()) {
			// Checking if not zero
			if (It1->getCoef() + It2->getCoef() != 0) {
				Monom m(It1->getCoef() + It2->getCoef(), It1->getPowers());
				res.addInTheEnd(m);
			}
			It1++;
			It2++;
		}
		else if (It1->getPowers() > It2->getPowers()) {
			Monom m(It2->getCoef(), It2->getPowers());
			res.addInTheEnd(m);
			It2++;
		}
		else {
			Monom m(It1->getCoef(), It1->getPowers());
			res.addInTheEnd(m);
			It1++;
		}
	}

	// Adding whats left
	if (It1 != Monoms.end()) {
		Monom m(It1->getCoef(), It1->getPowers());
		res.addInTheEnd(m);
		It1++;
	}

	if (It2 != Monoms.end()) {
		Monom m(It2->getCoef(), It2->getPowers());
		res.addInTheEnd(m);
		It2++;
	}

	res.cleanZeroedMonoms();

	return res;
}

Polynom Polynom::operator-(const Polynom& p) const {
	Polynom res;

	auto It1 = Monoms.begin();
	auto It2 = p.Monoms.begin();

	// Walking through polynoms
	while (It1 != Monoms.end() && It2 != p.Monoms.end()) {
		if (It1->getPowers() == It2->getPowers()) {
			// Checking if not zero
			if (It1->getCoef() - It2->getCoef() != 0) {
				Monom m(It1->getCoef() - It2->getCoef(), It1->getPowers());
				res.addInTheEnd(m);
			}
			It1++;
			It2++;
		}
		else if (It1->getPowers() > It2->getPowers()) {
			Monom m(-(It2->getCoef()), It2->getPowers());
			res.addInTheEnd(m);
			It2++;
		}
		else {
			Monom m(It1->getCoef(), It1->getPowers());
			res.addInTheEnd(m);
			It1++;
		}
	}
	
	// Adding(subtracting) whats left
	if (It1 != Monoms.end()) {
		Monom m(It1->getCoef(), It1->getPowers());
		res.addInTheEnd(m);
		It1++;
	}

	if (It2 != Monoms.end()) {
		Monom m(-(It2->getCoef()), It2->getPowers());
		res.addInTheEnd(m);
		It2++;
	}

	res.cleanZeroedMonoms();

	return res;
}

Polynom Polynom::operator*(const Polynom& p) const {
	Polynom res;
	
	for (auto It1 = Monoms.begin(); It1 != Monoms.end(); It1++) {
		for (auto It2 = p.Monoms.begin(); It2 != p.Monoms.end(); It2++) {
			Monom product = *It1 * *It2;

			auto ItRes = res.Monoms.begin();
			while (ItRes != res.Monoms.end() && ItRes->getPowers() < product.getPowers()) {
				ItRes++;
			}

			if (ItRes != res.Monoms.end() && ItRes->getPowers() == product.getPowers()) {
				ItRes->setCoef(ItRes->getCoef() + product.getCoef());
			}
			else {
				res.Monoms.insert_before(product, ItRes);
				res.size++;
			}
		}
	}

	res.cleanZeroedMonoms();
	return res;
}

Polynom Polynom::operator+(const Monom& m) const {
	Polynom p(m);
	return *this + p;
}

Polynom Polynom::operator-(const Monom& m) const {
	Polynom p(m);
	return *this - p;
}

Polynom Polynom::operator*(const Monom& m) const {
	// Complexity O(n)
	Polynom res = *this;
	for (auto It = res.Monoms.begin(); It != res.Monoms.end(); It++) {
		*It = *It * m;
	}
	return res;
}

Polynom Polynom::operator+(const double nm) const {
	Polynom p(nm);
	return *this + p;
}

Polynom Polynom::operator-(const double nm) const {
	Polynom p(nm);
	return *this - p;
}

Polynom Polynom::operator*(const double nm) const {
	Polynom p(nm);
	return *this * p;
}

Polynom Polynom::operator/(const double nm) const {
	if (nm == 0) throw std::runtime_error("Division by zero");

	Polynom p(1 / nm);
	return *this * p;
}

/* --- Other --- */
std::string Polynom::getValue() const {
	std::string S;
	if (size == 0) return S;

	auto It1 = Monoms.begin();
	S += It1->getValue();
	It1++;
	while (It1 != Monoms.end()) {
		S += " + " + It1->getValue();
		It1++;
	}

	return S;
};
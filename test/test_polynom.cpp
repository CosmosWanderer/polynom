#include <gtest.h>
#include "polynom.h"

TEST(Polynom, CanCreatePolynom1) {
	EXPECT_NO_THROW(Polynom p);
}

TEST(Polynom, CanCreatePolynom2) {
	Monom m(1, 2, 3, 4);

	EXPECT_NO_THROW(Polynom p(m));
}

TEST(Polynom, CanCreatePolynom3) {
	double c = 10;

	EXPECT_NO_THROW(Polynom p(c));
}

TEST(Polynom, CreatedPolynomHasRightValues1) {
	Polynom p;

	EXPECT_EQ(p.getValue(), "");
}

TEST(Polynom, CreatedPolynomHasRightValues2) {
	Monom m(1, 2, 3, 4);
	Polynom p(m);

	EXPECT_EQ(p.getValue(), "1.0*X^2*Y^3*Z^4");
}

TEST(Polynom, CreatedPolynomHasRightValues3) {
	double c = 10;
	Polynom p(c);

	EXPECT_EQ(p.getValue(), "10.0*X^0*Y^0*Z^0");
}

TEST(Polynom, CanAddPolynomes) {
	Monom m1(1, 2, 3, 4);
	Monom m2(4, 3, 2, 1);

	Polynom p1(m1);
	Polynom p2(m2);

	EXPECT_NO_THROW(p1 + p2);
}

TEST(Polynom, CanSubtractPolynomes) {
	Monom m1(1, 2, 3, 4);
	Monom m2(4, 3, 2, 1);

	Polynom p1(m1);
	Polynom p2(m2);

	EXPECT_NO_THROW(p1 - p2);
}

TEST(Polynom, CanMultiplyPolynomes) {
	Monom m1(1, 2, 3, 4);
	Monom m2(4, 3, 2, 1);

	Polynom p1(m1);
	Polynom p2(m2);

	EXPECT_NO_THROW(m1 * m2);
}

TEST(Polynom, PolynomAdditionWorksRight1) {
	Monom m1(1, 2, 3, 4);
	Monom m2(4, 2, 3, 4);

	Polynom p1(m1);
	Polynom p2(m2);

	EXPECT_EQ((p1 + p2).getValue(), "5.0*X^2*Y^3*Z^4");
}

TEST(Polynom, PolynomAdditionWorksRight2) {
	Monom m1(1, 2, 3, 4);
	Monom m2(1, 3, 2, 4);

	Polynom p1(m1);
	Polynom p2(m2);

	EXPECT_EQ((p1 + p2).getValue(), "1.0*X^2*Y^3*Z^4 + 1.0*X^3*Y^2*Z^4");
}

TEST(Polynom, PolynomSubtractionWorksRight) {
	Monom m1(5, 2, 3, 4);
	Monom m2(4, 2, 3, 4);

	Polynom p1(m1);
	Polynom p2(m2);

	EXPECT_EQ((p1 - p2).getValue(), "1.0*X^2*Y^3*Z^4");
}

TEST(Polynom, PolynomMultiplicationWorksRight) {
	Monom m1(5, 2, 3, 4);
	Monom m2(4, 2, 3, 4);

	Polynom p1(m1);
	Polynom p2(m2);

	EXPECT_EQ((p1 * p2).getValue(), "20.0*X^4*Y^6*Z^8");
}
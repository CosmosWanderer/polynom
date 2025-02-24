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

TEST(Polynom, PolynomMultiplicationWorksRight1) {
	Monom m1(5, 2, 3, 4);
	Monom m2(4, 2, 3, 4);

	Polynom p1(m1);
	Polynom p2(m2);

	EXPECT_EQ((p1 * p2).getValue(), "20.0*X^4*Y^6*Z^8");
}

TEST(Polynom, PolynomMultiplicationWorksRight2) {
	Monom m1(5, 1, 2, 3);
	Monom m2(5, 2, 3, 4);

	Polynom p1(m1);
	p1 = p1 + m2;
	
	Monom m3(5, 3, 4, 5);
	Monom m4(5, 4, 5, 6);

	Polynom p2(m3);
	p2 = p2 + m4;

	EXPECT_EQ((p1 * p2).getValue(), "25.0*X^4*Y^6*Z^8 + 50.0*X^5*Y^7*Z^9 + 25.0*X^6*Y^8*Z^10");
}

TEST(Polynom, CanAddConstant) {
	Monom m(1, 2, 3, 4);
	Polynom p(m);

	EXPECT_NO_THROW(p + 10.0);
}

TEST(Polynom, CanSubtractConstant) {
	Monom m(1, 2, 3, 4);
	Polynom p(m);

	EXPECT_NO_THROW(p - 10.0);
}

TEST(Polynom, CanMultiplicateByConstant) {
	Monom m(1, 2, 3, 4);
	Polynom p(m);

	EXPECT_NO_THROW(p * 10);
}

TEST(Polynom, CanDivideByConstant) {
	Monom m(1, 2, 3, 4);
	Polynom p(m);

	EXPECT_NO_THROW(p / 10);
}

TEST(Polynom, CantDivideByZero) {
	Monom m(1, 2, 3, 4);
	Polynom p(m);

	EXPECT_ANY_THROW(p / 0);
}

TEST(Polynom, ConstantAdditionWorksRight) {
	Monom m(1, 2, 3, 4);
	Polynom p(m);

	EXPECT_EQ((p + 10.0).getValue(), "10.0*X^0*Y^0*Z^0 + 1.0*X^2*Y^3*Z^4");
}

TEST(Polynom, ConstantSubtractionWorksRight) {
	Monom m(1, 2, 3, 4);
	Polynom p(m);

	EXPECT_EQ((p - 10.0).getValue(), "(-10.0)*X^0*Y^0*Z^0 + 1.0*X^2*Y^3*Z^4");
}

TEST(Polynom, ConstantMultiplicationWorksRight) {
	Monom m(1, 2, 3, 4);
	Polynom p(m);

	EXPECT_EQ((p * 10.0).getValue(), "10.0*X^2*Y^3*Z^4");
}

TEST(Polynom, ConstantDivisionWorksRight) {
	Monom m(5, 2, 3, 4);
	Polynom p(m);

	EXPECT_EQ((p / 2.0).getValue(), "2.50*X^2*Y^3*Z^4");
}

TEST(Polynom, CanAddMonom) {
	Monom m1(1, 2, 3, 4);
	Polynom p(m1);
	Monom m2(1, 2, 3, 4);

	EXPECT_NO_THROW(p + m2);
}

TEST(Polynom, CanSubtractMonom) {
	Monom m1(1, 2, 3, 4);
	Polynom p(m1);
	Monom m2(1, 2, 3, 4);

	EXPECT_NO_THROW(p - m2);
}

TEST(Polynom, CanMultiplicateByMonom) {
	Monom m1(1, 2, 3, 4);
	Polynom p(m1);
	Monom m2(1, 2, 3, 4);


	EXPECT_NO_THROW(p * m2);
}

TEST(Polynom, MonomAdditionWorksRight1) {
	Monom m1(1, 2, 3, 4);
	Polynom p(m1);
	Monom m2(1, 2, 3, 4);

	EXPECT_EQ((p + m2).getValue(), "2.0*X^2*Y^3*Z^4");
}

TEST(Polynom, MonomAdditionWorksRight2) {
	Monom m1(1, 2, 3, 4);
	Polynom p(m1);
	Monom m2(2, 3, 4, 5);

	EXPECT_EQ((p + m2).getValue(), "1.0*X^2*Y^3*Z^4 + 2.0*X^3*Y^4*Z^5");
}

TEST(Polynom, MonomSubtractionWorksRight1) {
	Monom m1(2, 2, 3, 4);
	Polynom p(m1);
	Monom m2(1, 2, 3, 4);

	EXPECT_EQ((p - m2).getValue(), "1.0*X^2*Y^3*Z^4");
}

TEST(Polynom, MonomSubtractionWorksRight2) {
	Monom m1(1, 2, 3, 4);
	Polynom p(m1);
	Monom m2(2, 3, 4, 5);

	EXPECT_EQ((p - m2).getValue(), "1.0*X^2*Y^3*Z^4 + (-2.0)*X^3*Y^4*Z^5");
}

TEST(Polynom, MonomMultiplicationWorksRight) {
	Monom m1(1, 2, 3, 4);
	Monom m2(2, 3, 4, 5);
	Polynom p(m1);
	p = p + m2;

	Monom m3(2, 2, 2, 2);
	EXPECT_EQ((p * m3).getValue(), "2.0*X^4*Y^5*Z^6 + 4.0*X^5*Y^6*Z^7");
}
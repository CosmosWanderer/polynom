#include <gtest.h>
#include "monom.h"
#include "polynom.h"

TEST(Monom, CanCreateMonom1) {
	EXPECT_NO_THROW(Monom m);
}

TEST(Monom, CanCreateMonom2) {
	EXPECT_NO_THROW(Monom m(1, 2, 3, 4));
}

TEST(Monom, CreatedMonomHasRightValues1) {
	Monom m;

	EXPECT_EQ(m.getPowers(), 0);
	EXPECT_EQ(m.getCoef(), 0.0);
}

TEST(Monom, CreatedMonomHasRightValues2) {
	Monom m(1, 2, 3, 4);

	EXPECT_EQ(m.getCoef(), 1);
	EXPECT_EQ(m.getXPower(), 2.0);
	EXPECT_EQ(m.getYPower(), 3);
	EXPECT_EQ(m.getZPower(), 4);
}

TEST(Monom, CanAddMonoms) {
	Monom m1(1, 2, 3, 4);
	Monom m2(1, 2, 3, 4);

	EXPECT_NO_THROW(m1 + m2);
}

TEST(Monom, CanSubtractMonoms) {
	Monom m1(1, 2, 3, 4);
	Monom m2(1, 2, 3, 4);

	EXPECT_NO_THROW(m1 - m2);
}

TEST(Monom, CanMultiplyMonoms) {
	Monom m1(1, 2, 3, 4);
	Monom m2(1, 2, 3, 4);

	EXPECT_NO_THROW(m1 * m2);
}

TEST(Monom, CanDivideMonoms) {
	Monom m1(1, 2, 3, 4);
	Monom m2(1, 2, 3, 4);

	EXPECT_NO_THROW(m1 / m2);
}

TEST(Monom, AdditionWorksRight) {
	Monom m1(2, 2, 3, 4);
	Monom m2(1, 2, 3, 4);

	Monom m3 = m1 + m2;

	EXPECT_EQ(m3.getCoef(), 3.0);
	EXPECT_EQ(m3.getXPower(), 2);
	EXPECT_EQ(m3.getYPower(), 3);
	EXPECT_EQ(m3.getZPower(), 4);
}

TEST(Monom, SubtractionWorksRight) {
	Monom m1(2, 2, 3, 4);
	Monom m2(1, 2, 3, 4);

	Monom m3 = m1 - m2;

	EXPECT_EQ(m3.getCoef(), 1.0);
	EXPECT_EQ(m3.getXPower(), 2);
	EXPECT_EQ(m3.getYPower(), 3);
	EXPECT_EQ(m3.getZPower(), 4);
}

TEST(Monom, MultiplicationWorksRight) {
	Monom m1(2, 2, 3, 4);
	Monom m2(1, 2, 3, 4);

	Monom m3 = m1 * m2;

	EXPECT_EQ(m3.getCoef(), 2.0);
	EXPECT_EQ(m3.getXPower(), 4);
	EXPECT_EQ(m3.getYPower(), 6);
	EXPECT_EQ(m3.getZPower(), 8);
}

TEST(Monom, DivisionWorksRight) {
	Monom m1(6, 3, 4, 5);
	Monom m2(3, 2, 3, 4);

	Monom m3 = m1 / m2;

	EXPECT_EQ(m3.getCoef(), 2.0);
	EXPECT_EQ(m3.getXPower(), 1);
	EXPECT_EQ(m3.getYPower(), 1);
	EXPECT_EQ(m3.getZPower(), 1);
}

TEST(Monom, CantDivideByNullMonom) {
	Monom m1(6, 3, 4, 5);
	Monom m2;

	EXPECT_ANY_THROW(m1 / m2);
}

TEST(Monom, equalMonomsAreEqual) {
	Monom m1(1, 2, 3, 4);
	Monom m2(1, 2, 3, 4);

	EXPECT_TRUE(m1 == m2);
}

TEST(Monom, notEqualMonomsAreNotEqual1) {
	Monom m1(1, 2, 3, 4);
	Monom m2(2, 2, 3, 4);

	EXPECT_FALSE(m1 == m2);
}

TEST(Monom, notEqualMonomsAreNotEqual2) {
	Monom m1(1, 2, 3, 4);
	Monom m2(1, 2, 2, 4);

	EXPECT_FALSE(m1 == m2);
}

TEST(Monom, canMultiplyByConstant) {
	Monom m(1, 2, 3, 4);
	double c = 10;

	EXPECT_NO_THROW(m * c);
}

TEST(Monom, canDivideByConstant) {
	Monom m(1, 2, 3, 4);
	double c = 10;

	EXPECT_NO_THROW(m / c);
}

TEST(Monom, multiplicationByConstantWorksRight) {
	Monom m1(1, 2, 3, 4);
	double c = 10;
	
	Monom m2 = m1 * c;

	EXPECT_EQ(m2.getCoef(), 10.0);
	EXPECT_EQ(m2.getXPower(), 2);
	EXPECT_EQ(m2.getYPower(), 3);
	EXPECT_EQ(m2.getZPower(), 4);
}

TEST(Monom, divisionByConstantWorksRight) {
	Monom m1(10, 2, 3, 4);
	double c = 10;

	Monom m2 = m1 / c;

	EXPECT_EQ(m2.getCoef(), 1.0);
	EXPECT_EQ(m2.getXPower(), 2);
	EXPECT_EQ(m2.getYPower(), 3);
	EXPECT_EQ(m2.getZPower(), 4);
}

TEST(Monom, cantDivideByZero) {
	Monom m1(10, 2, 3, 4);

	EXPECT_ANY_THROW(m1 / 0);
}
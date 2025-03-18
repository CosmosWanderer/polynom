#include <gtest.h>
#include "monom.h"
#include "polynom.h"
#include "simple_parser.h"

TEST(Parser, rightInput1) {
	std::string input = "29.1x^1y^2z^3";
	PolynomTranslator PT;
	Polynom p = PT.polynomParser(input);
	std::string output = p.getValue();

	std::string rightOutput = "29.10 * x^1y^2z^3";
	EXPECT_EQ(rightOutput, output);
}

TEST(Parser, rightInput2) {
	std::string input = "xyz";
	PolynomTranslator PT;
	Polynom p = PT.polynomParser(input);
	std::string output = p.getValue();

	std::string rightOutput = "1.0 * x^1y^1z^1";
	EXPECT_EQ(rightOutput, output);
}

TEST(Parser, rightInput3) {
	std::string input = "xz";
	PolynomTranslator PT;
	Polynom p = PT.polynomParser(input);
	std::string output = p.getValue();

	std::string rightOutput = "1.0 * x^1y^0z^1";
	EXPECT_EQ(rightOutput, output);
}

TEST(Parser, rightInput4) {
	std::string input = "0.1xyzxyzxyz";
	PolynomTranslator PT;
	Polynom p = PT.polynomParser(input);
	std::string output = p.getValue();

	std::string rightOutput = "0.10 * x^3y^3z^3";
	EXPECT_EQ(rightOutput, output);
}

TEST(Parser, rightInput5) {
	std::string input = "x";
	PolynomTranslator PT;
	Polynom p = PT.polynomParser(input);
	std::string output = p.getValue();

	std::string rightOutput = "1.0 * x^1y^0z^0";
	EXPECT_EQ(rightOutput, output);
}

TEST(Parser, rightInput6) {
	std::string input = "x + x + x + y + y - y - y + z + 2.0zx";
	PolynomTranslator PT;
	Polynom p = PT.polynomParser(input);
	std::string output = p.getValue();

	std::string rightOutput = "1.0 * x^0y^0z^1 + 3.0 * x^1y^0z^0 + 2.0 * x^1y^0z^1";
	EXPECT_EQ(rightOutput, output);
}

TEST(Parser, rightInput7) {
	std::string input = "zyx - xyz";
	PolynomTranslator PT;
	Polynom p = PT.polynomParser(input);
	std::string output = p.getValue();

	std::string rightOutput = "0.0 * x^1y^1z^1";
	EXPECT_EQ(rightOutput, output);
}

TEST(Parser, rightInput8) {
	std::string input = "-2.0";
	PolynomTranslator PT;
	Polynom p = PT.polynomParser(input);
	std::string output = p.getValue();

	std::string rightOutput = "(-2.0) * x^0y^0z^0";
	EXPECT_EQ(rightOutput, output);
}

TEST(Parser, rightInput9) {
	std::string input = "0.1 + x - xy^7 - z^8y - 111.1";
	PolynomTranslator PT;
	Polynom p = PT.polynomParser(input);
	std::string output = p.getValue();

	std::string rightOutput = "(-111.0) * x^0y^0z^0 + (-1.0) * x^0y^1z^8 + 1.0 * x^1y^0z^0 + (-1.0) * x^1y^7z^0";
	EXPECT_EQ(rightOutput, output);
}

TEST(Parser, rightInput10) {
	std::string input = "x^3y^3z^3x^4y^4z^4";
	PolynomTranslator PT;
	Polynom p = PT.polynomParser(input);
	std::string output = p.getValue();

	std::string rightOutput = "1.0 * x^7y^7z^7";
	EXPECT_EQ(rightOutput, output);
}

TEST(Parser, wrongInput1) {
	std::string input = "x^600y^1x^600";
	PolynomTranslator PT;

	EXPECT_ANY_THROW(PT.polynomParser(input));
}

TEST(Parser, wrongInput2) {
	std::string input = "xx";
	PolynomTranslator PT;

	EXPECT_ANY_THROW(PT.polynomParser(input));
}

TEST(Parser, wrongInput3) {
	std::string input = " ";
	PolynomTranslator PT;

	EXPECT_ANY_THROW(PT.polynomParser(input));
}

TEST(Parser, wrongInput4) {
	std::string input = "x^";
	PolynomTranslator PT;

	EXPECT_ANY_THROW(PT.polynomParser(input));
}

TEST(Parser, wrongInput5) {
	std::string input = "x^y";
	PolynomTranslator PT;

	EXPECT_ANY_THROW(PT.polynomParser(input));
}

TEST(Parser, wrongInput6) {
	std::string input = "z6";
	PolynomTranslator PT;

	EXPECT_ANY_THROW(PT.polynomParser(input));
}

TEST(Parser, wrongInput7) {
	std::string input = "1";
	PolynomTranslator PT;

	EXPECT_ANY_THROW(PT.polynomParser(input));
}

TEST(Parser, wrongInput8) {
	std::string input = "1.0 * x";
	PolynomTranslator PT;

	EXPECT_ANY_THROW(PT.polynomParser(input));
}

TEST(Parser, wrongInput9) {
	std::string input = "x1.0";
	PolynomTranslator PT;

	EXPECT_ANY_THROW(PT.polynomParser(input));
}

TEST(Parser, wrongInput10) {
	std::string input = "y^1.0";
	PolynomTranslator PT;

	EXPECT_ANY_THROW(PT.polynomParser(input));
}

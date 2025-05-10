#include "simple_parser.h"
#include "polynom.h"

std::string PolynomTranslator::execute(std::string input) {

	/*
	First input decides, which mode to choose

	If input 1, then we expect:
	1) Polynom
	2) Name for this polynom
	Then, we save this polynom in unordered map, and return value of this polynom

	If input 2, then we expect:
	1) Name of polynom 1
	2) Name of polynom 2
	3) Operation (+, -, *, /) (there r some problems with parsing division)
	Then, we return value of resulting polynom

	If input 3, then we expect
	1) Name of polynom 1
	2) Name of polynom 2
	3) Operation (+, -, *, /) (there r some problems with parsing division)
	4) Name for resulting polynom
	Then, we return value of resulting polynom, and also save it in unordered map
	*/

	if (input != "1" && input != "2" && input != "3") throw std::string("Incorrect mode name");
	
	if (input == "1") {
		/*
		In mode 1, we expect:
		1) Polynom
		2) Name for this polynom
		Then, we save this polynom in unordered map, and return value of this polynom
		*/

		// Entering polynom
		std::cout << "Enter polynom:" << std::endl;

		std::string polynom;
		std::getline(std::cin, polynom);
		Polynom P;
		try {
			P = polynomParser(polynom);
		}
		catch (std::string err) {
			throw std::string(err);
		}
		// Entering name
		std::cout << "Enter name: " << std::endl;

		std::string name;
		std::getline(std::cin, name);
		bool alreadyExists;
		try {
			alreadyExists = nameCheck(name);
		}
		catch (std::string err) {
			throw std::string(err);
		}

		// Adding/changing polynom in unordered map
		Polynoms[name] = P;

		return P.getValue();
	}
	if (input == "2") {
		/*
		In mode 2 we expect:
		1) Name of polynom 1
		2) Name of polynom 2
		3) Operation (+, -, *) (there r some problems with parsing division)
		Then, we return value of resulting polynom
		*/

		// Entering names, checking for existance
		std::cout << "Enter name 1: ";

		std::string name1;
		std::getline(std::cin, name1);
		bool alreadyExists;
		try {
			alreadyExists = nameCheck(name1);
		}
		catch (std::string err) {
			throw std::string(err);
		}
		if (!alreadyExists) throw std::string("There are no such polynom saved");

		std::cout << "Enter name 2: ";

		std::string name2;
		std::getline(std::cin, name2);
		try {
			alreadyExists = nameCheck(name2);
		}
		catch (std::string err) {
			throw std::string(err);
		}
		if (!alreadyExists) throw std::string("There are no such polynom saved");
		
		// Getting operation
		std::cout << "Enter operation (+, -, *): ";

		std::string operation;
		std::getline(std::cin, operation);
		if (operation == "+") return (Polynoms[name1] + Polynoms[name2]).getValue();
		if (operation == "-") return (Polynoms[name1] - Polynoms[name2]).getValue();
		if (operation == "*") return (Polynoms[name1] * Polynoms[name2]).getValue();

		throw std::string("Incorrect operation");
	}
	if (input == "3") {
		/*
		In mode 3 we expect
		1) Name of polynom 1
		2) Name of polynom 2
		3) Operation (+, -, *, /) (there r some problems with parsing division)
		4) Name for resulting polynom
		Then, we return value of resulting polynom, and also save it in unordered map
		*/

		// Entering names, checking for existance
		std::cout << "Enter name 1: ";

		std::string name1;
		std::getline(std::cin, name1);
		bool alreadyExists;
		try {
			alreadyExists = nameCheck(name1);
		}
		catch (std::string err) {
			throw std::string(err);
		}
		if (!alreadyExists) std::string("There are no such polynom saved");

		std::cout << "Enter name 2: ";

		std::string name2;
		std::getline(std::cin, name2);
		try {
			alreadyExists = nameCheck(name2);
		}
		catch (std::string err) {
			throw std::string(err);
		}
		if (!alreadyExists) throw std::string("There are no such polynom saved");

		Polynom resPolynom;

		// Getting operation
		std::cout << "Enter operation (+, -, *): ";

		std::string operation;
		std::getline(std::cin, operation);
		if (operation == "+") resPolynom = Polynoms[name1] + Polynoms[name2];
		else if (operation == "-") resPolynom = Polynoms[name1] - Polynoms[name2];
		else if (operation == "*") resPolynom = Polynoms[name1] * Polynoms[name2];
		else throw std::string("Incorrect operation");

		// Entering name
		std::cout << "Enter name for the result: ";

		std::string name;
		std::getline(std::cin, name);
		try {
			alreadyExists = nameCheck(name);
		}
		catch (std::string err) {
			throw std::string(err);
		}

		// Adding/changing polynom in unordered map
		Polynoms[name] = resPolynom;

		return resPolynom.getValue();
	}
};

Polynom PolynomTranslator::polynomParser(std::string input) {

	std::set<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	input += " ";

	/*
	Monoms must look like this:
	"coef * x^iy^jz^k"
	Example:
	5.0 * x^3y^8z^1
	Space after power of z means the end of current monon

	All parts are divided by "+" and "-" signs
	*/
	/*
	Possible states
	(-1) - States 0 and 1 combined, used for first monom (Starting state)
	0 - waiting for "+" or "-" sign
	1 - waiting for coefficient
	2 - entering part before the dot, waiting for the dot
	3 - entering part after the dot, waiting for space
	4 - waiting for "*" symbol
	5 - waiting for x
	6 - waiting for ^
	7 - entering power of x, waiting for y
	8 - waiting for ^
	9 - entering power of y, waiting for z
	10 - waiting for ^
	11 - entering power of z, waiting for space
	Then, return to state 0

	*/
	/*
	int status = -1;
	Polynom result;

	double curCoef = 1.0;
	int curXPower = 0;
	int curYPower = 0;
	int curZPower = 0;
	std::string curToken = "";

	for (char c : input) {
		switch (status) {
		case -1: // States 0 and 1 combined, used for first monom (Starting state)
			if (c == ' ') {
				status = 1;
				break;
			}
			if (c == '+') {
				status = 1;
				curCoef = 1.0;
				break;
			}
			if (c == '-') {
				status = 1;
				curCoef = -1.0;
				break;
			}
			if (numbers.count(c)) {
				status = 2;
				curToken += c;
				break;
			}
			throw std::string("Case -1 error");
			break;

		case 0:	// Waiting for "+" or "-" sign
			if (c == ' ') {
				status = 0;
				break;
			}
			if (c == '+') {
				status = 1;
				curCoef = 1.0;
				break;
			}
			if (c == '-') {
				status = 1;
				curCoef = -1.0;
				break;
			}
			throw std::string("Case 0 error");
			break;


		case 1: // waiting for coefficient
			if (c == ' ') {
				status = 1;
				break;
			}
			if (numbers.count(c)) {
				status = 2;
				curToken += c;
				break;
			}
			throw std::string("Case 1 error");
			break;

		case 2: // entering part before the dot, waiting for the dot
			if (numbers.count(c)) {
				status = 2;
				curToken += c;
				break;
			}
			if (c == '.') {
				status = 3;
				curToken += c;
				break;
			}
			throw std::string("Case 2 error");
			break;

		case 3: // entering part after the dot, waiting for space
			if (numbers.count(c)) {
				status = 3;
				curToken += c;
				break;
			}
			if (c == ' ') {
				status = 4;
				curCoef *= std::stod(curToken);
				curToken = "";
				break;
			}
			throw std::string("Case 3 error");
			break;

		case 4: // waiting for "*" symbol
			if (c == ' ') {
				status = 4;
				break;
			}
			if (c == '*') {
				status = 5;
				break;
			}
			throw std::string("Case 4 error");
			break;

		case 5: // waiting for x
			if (c == ' ') {
				status = 5;
				break;
			}
			if (c == 'x') {
				status = 6;
				break;
			}
			throw std::string("Case 5 error");
			break;

		case 6: // waiting for ^
			if (c == '^') {
				status = 7;
				break;
			}
			throw std::string("Case 6 error");
			break;

		case 7: // entering power of x, waiting for y
			if (numbers.count(c)) {
				status = 7;
				curToken += c;
				break;
			}
			if (c == 'y' && curToken.length()) {
				status = 8;
				curXPower = stoi(curToken);
				curToken = "";
				break;
			}
			throw std::string("Case 7 error");
			break;

		case 8: // waiting for ^
			if (c == '^') {
				status = 9;
				break;
			}
			throw std::string("Case 8 error");
			break;

		case 9: // entering power of y, waiting for z
			if (numbers.count(c)) {
				status = 9;
				curToken += c;
				break;
			}
			if (c == 'z' && curToken.length()) {
				status = 10;
				curYPower = stoi(curToken);
				curToken = "";
				break;
			}
			throw std::string("Case 9 error");
			break;

		case 10: // waiting for ^
			if (c == '^') {
				status = 11;
				break;
			}
			throw std::string("Case 10 error");
			break;

		case 11: // entering power of z, waiting for space
			if (numbers.count(c)) {
				status = 11;
				curToken += c;
				break;
			}
			if (c == ' ' && curToken.length()) {
				status = 0;
				curZPower = stoi(curToken);

				Monom curMonom(curCoef, curXPower, curYPower, curZPower);
				result.addMonom(curMonom);
				curCoef = 1.0;

				curXPower = 0;
				curYPower = 0;
				curZPower = 0;
				curToken = "";
				break;
			}
			throw std::string("Case 11 error");
			break;
		}
	}

	if (status != 0) {
		throw std::string("Unexpected end of input");
	}
	*/





	// New parser
	/*
	Monoms are separated by spaces, '+' and '-' marks
	-1: Start of the input, waiting for monom, + or -
	0: End of the input/ waiting for new monom (+ or -)
	1: Waiting for monom parts
	2: Entering numbers before '.'
	3: Waiting for the dot
	*/



	int status = -1;
	Polynom result;

	double curCoef = 1.0;
	int curXPower = 0;
	int curYPower = 0;
	int curZPower = 0;
	std::string curToken = "";

	for (char c : input) {
		switch (status) {
		case -1:
			if (c == ' ') {
				break;
			}
			if (c == '+') {
				status = 1;
				break;
			}
			if (c == '-') {
				status = 1;
				curCoef *= -1;
				break;
			}
			// Monom parts
			if (c == '0') {
				curToken += c;
				status = 3;
				break;
			}
			if (numbers.count(c)) {
				curToken += c;
				status = 2;
				break;
			}
			if (c == 'x') {
				status = 5;
				break;
			}
			if (c == 'y') {
				status = 8;
				break;
			}
			if (c == 'z') {
				status = 11;
				break;
			}
			throw std::string("Case -1 error");
		case 0:
			if (c == ' ') {
				break;
			}
			if (c == '+') {
				status = 1;
				break;
			}
			if (c == '-') {
				status = 1;
				curCoef *= -1;
				break;
			}
			throw std::string("Case 0 error");
		case 1:
			if (c == ' ') {
				break;
			}
			if (c == '0') {
				curToken += c;
				status = 3;
				break;
			}
			if (numbers.count(c)) {
				curToken += c;
				status = 2;
				break;
			}
			if (c == 'x') {
				status = 5;
				break;
			}
			if (c == 'y') {
				status = 8;
				break;
			}
			if (c == 'z') {
				status = 11;
				break;
			}
			throw std::string("Case 1 error");
		case 2:
			if (numbers.count(c)) {
				curToken += c;
				status = 2;
				break;
			}
			if (c == '.') {
				curToken += c;
				status = 4;
				break;
			}
			throw std::string("Case 2 error");
		case 3:
			if (c == '.') {
				curToken += c;
				status = 4;
				break;
			}
			throw std::string("Case 3 error");
		case 4:
			if (numbers.count(c)) {
				curToken += c;
				status = 4;
				break;
			}
			// Other monom parts
			if (c == 'x') {
				curCoef *= std::stod(curToken);
				curToken = "";
				status = 5;
				break;
			}
			if (c == 'y') {
				curCoef *= std::stod(curToken);
				curToken = "";
				status = 8;
				break;
			}
			if (c == 'z') {
				curCoef *= std::stod(curToken);
				curToken = "";
				status = 11;
				break;
			}
			// End of monom
			if (c == ' ') {
				curCoef *= std::stod(curToken);
				Monom curMonom(curCoef, curXPower, curYPower, curZPower);
				result.addMonom(curMonom);
				
				curCoef = 1.0;
				curXPower = 0;
				curYPower = 0;
				curZPower = 0;
				curToken = "";

				status = 0;
				break;
			}
			throw std::string("Case 4 error");
		
		// Powers
		case 5:
			if (c == '^') {
				status = 6;
				break;
			}
			// Other monom parts
			if (c == 'y') {
				curXPower += 1;
				status = 8;
				break;
			}
			if (c == 'z') {
				curXPower += 1;
				status = 11;
				break;
			}
			// End of monom
			if (c == ' ') {
				curXPower += 1;
				Monom curMonom(curCoef, curXPower, curYPower, curZPower);
				result.addMonom(curMonom);

				curCoef = 1.0;
				curXPower = 0;
				curYPower = 0;
				curZPower = 0;
				curToken = "";

				status = 0;
				break;
			}
			throw std::string("Case 5 error");
		case 6:
			if (c == '0') {
				status = 14;
				break;
			}
			if (numbers.count(c)) {
				curToken += c;
				status = 7;
				break;
			}
			throw std::string("Case 6 error");
		case 7:
			if (numbers.count(c)) {
				curToken += c;
				status = 7;
				break;
			}
			// Other monom parts
			if (c == 'y') {
				curXPower += stoi(curToken);
				curToken = "";
				status = 8;
				break;
			}
			if (c == 'z') {
				curXPower += stoi(curToken);
				curToken = "";
				status = 11;
				break;
			}
			// End of monom
			if (c == ' ') {
				curXPower += stoi(curToken);
				Monom curMonom(curCoef, curXPower, curYPower, curZPower);
				result.addMonom(curMonom);

				curCoef = 1.0;
				curXPower = 0;
				curYPower = 0;
				curZPower = 0;
				curToken = "";

				status = 0;
				break;
			}
			throw std::string("Case 7 error");

		case 8:
			if (c == '^') {
				status = 9;
				break;
			}
			// Other monom parts
			if (c == 'x') {
				curYPower += 1;
				status = 5;
				break;
			}
			if (c == 'z') {
				curYPower += 1;
				status = 11;
				break;
			}
			// End of monom
			if (c == ' ') {
				curYPower += 1;
				Monom curMonom(curCoef, curXPower, curYPower, curZPower);
				result.addMonom(curMonom);

				curCoef = 1.0;
				curXPower = 0;
				curYPower = 0;
				curZPower = 0;
				curToken = "";

				status = 0;
				break;
			}
			throw std::string("Case 8 error");
		case 9:
			if (c == '0') {
				status = 14;
				break;
			}
			if (numbers.count(c)) {
				curToken += c;
				status = 10;
				break;
			}
			throw std::string("Case 9 error");
		case 10:
			if (numbers.count(c)) {
				curToken += c;
				status = 10;
				break;
			}
			// Other monom parts
			if (c == 'x') {
				curYPower += stoi(curToken);
				curToken = "";
				status = 5;
				break;
			}
			if (c == 'z') {
				curYPower += stoi(curToken);
				curToken = "";
				status = 11;
				break;
			}
			// End of monom
			if (c == ' ') {
				curYPower += stoi(curToken);
				Monom curMonom(curCoef, curXPower, curYPower, curZPower);
				result.addMonom(curMonom);

				curCoef = 1.0;
				curXPower = 0;
				curYPower = 0;
				curZPower = 0;
				curToken = "";

				status = 0;
				break;
			}
			throw std::string("Case 10 error");

		case 11:
			if (c == '^') {
				status = 12;
				break;
			}
			// Other monom parts
			if (c == 'x') {
				curZPower += 1;
				status = 5;
				break;
			}
			if (c == 'y') {
				curZPower += 1;
				status = 8;
				break;
			}
			// End of monom
			if (c == ' ') {
				curZPower += 1;
				Monom curMonom(curCoef, curXPower, curYPower, curZPower);
				result.addMonom(curMonom);

				curCoef = 1.0;
				curXPower = 0;
				curYPower = 0;
				curZPower = 0;
				curToken = "";

				status = 0;
				break;
			}
			throw std::string("Case 11 error");
		case 12:
			if (c == '0') {
				status = 14;
				break;
			}
			if (numbers.count(c)) {
				curToken += c;
				status = 13;
				break;
			}
			throw std::string("Case 12 error");
		case 13:
			if (numbers.count(c)) {
				curToken += c;
				status = 13;
				break;
			}
			// Other monom parts
			if (c == 'x') {
				curZPower += stoi(curToken);
				curToken = "";
				status = 5;
				break;
			}
			if (c == 'y') {
				curZPower += stoi(curToken);
				curToken = "";
				status = 8;
				break;
			}
			// End of monom
			if (c == ' ') {
				curZPower += stoi(curToken);
				Monom curMonom(curCoef, curXPower, curYPower, curZPower);
				result.addMonom(curMonom);

				curCoef = 1.0;
				curXPower = 0;
				curYPower = 0;
				curZPower = 0;
				curToken = "";

				status = 0;
				break;
			}
			throw std::string("Case 13 error");
		
		case 14:
			if (c == 'x') {
				curToken = "";
				status = 5;
				break;
			}
			if (c == 'y') {
				curToken = "";
				status = 8;
				break;
			}
			if (c == 'z') {
				curToken = "";
				status = 11;
				break;
			}
			// End of monom
			if (c == ' ') {
				Monom curMonom(curCoef, curXPower, curYPower, curZPower);
				result.addMonom(curMonom);

				curCoef = 1.0;
				curXPower = 0;
				curYPower = 0;
				curZPower = 0;
				curToken = "";

				status = 0;
				break;
			}
			throw std::string("Case 14 error");
		}
	}
	
	//std::cout << status << std::endl;
	if (status != 0) throw std::string("Unexpected end of input");

	return result;
};

bool PolynomTranslator::nameCheck(std::string name) {
	std::set<char> characters = { 'a', 'A', 'b', 'B',
	'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G',
	'h', 'H', 'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L',
	'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q',
	'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v', 'V',
	'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z' };

	if (name.empty()) throw std::string("Naming is incorrect");

	for (char c : name) {
		if (characters.count(c) == 0) throw std::string("Naming is incorrect");
	}

	if (Polynoms.count(name) == 0) return 0;
	return 1;
}
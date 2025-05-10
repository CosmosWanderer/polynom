#include "polynom.h"
#include "simple_parser.h"

int main() {

	PolynomTranslator T;
	std::string input;
	std::string output;

	std::cout << "Information about modes:" << std::endl << "1) Adding new polynom"
		<< std::endl << "2) Choosing 2 polynomes and performing an operation" <<
		std::endl << "3) Choosing 2 polynomes, performing an operation and saving the result" << std::endl << std::endl;


	while (true) {
		std::cout << "Enter mode (1, 2, 3): ";
		std::getline(std::cin, input);
		try {
			output = T.execute(input);
			std::cout << output << std::endl;
		}
		catch (std::string err) {
			std::cout << err << std::endl;
		}
		std::cout << std::endl;
	}

	return 0;
}
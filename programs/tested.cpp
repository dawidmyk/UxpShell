#include <iostream>

int main() {
	std::cout << "Jestem nowym procesem" << std::endl;
	std::cout << "Wpisz coś" << std::endl;
	std::string posit;
	std::cin >> posit;
	
	std::cout << "Oto co napisałeś: " << posit << std::endl;
	return 0;
}

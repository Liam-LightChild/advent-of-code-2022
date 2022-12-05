#include <stdexcept>
#include <iostream>
#include <fstream>
#include <array>

constexpr int getPriority(char c) {
	if(c >= 'a' && c <= 'z') return (int)(c - 'a') + 1;
	if(c >= 'A' && c <= 'Z') return (int)(c - 'A') + 27;
	throw std::runtime_error(std::string("invalid character: " + std::string(&c, 1) + " (" + std::to_string((int)c) + ")"));
}

int main() {
	std::ifstream input("day3.txt");
	std::string line;
	auto sum = 0;

	while(!input.eof()) {
		std::getline(input, line);
		auto compartmentSize = line.length() / 2;

		std::array<std::string, 2> compartments {
				line.substr(0, compartmentSize),
				line.substr(compartmentSize)
		};

		for (const auto &item: compartments[0]) {
			if(compartments[1].find(item) != std::string::npos) {
				sum += getPriority(item);
				goto end;
			}
		}

		for (const auto &item: compartments[1]) {
			if(compartments[0].find(item) != std::string::npos) {
				sum += getPriority(item);
				goto end;
			}
		}

		end:;
	}

	std::cout << "Priority sum: " << sum << std::endl;
}

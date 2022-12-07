#include <fstream>
#include <array>
#include <algorithm>
#include <iostream>

int main() {
	std::ifstream input("day6.txt");
	std::array<char, 4> chars {};
	input.read(chars.data(), chars.size());

	while(!input.eof()) {
		if(std::all_of(chars.begin(), chars.end(), [&chars](auto c) {
			return std::count(chars.begin(), chars.end(), c) == 1;
		})) {
			std::cout << input.tellg() << std::endl;
			break;
		} else {
			std::copy(chars.begin() + 1, chars.end(), chars.begin());
			input.read(&chars[3], 1);
		}
	}
}

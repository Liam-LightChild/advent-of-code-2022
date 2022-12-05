#include <stdexcept>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <algorithm>

constexpr int getPriority(char c) {
	if(c >= 'a' && c <= 'z') return (int)(c - 'a') + 1;
	if(c >= 'A' && c <= 'Z') return (int)(c - 'A') + 27;
	throw std::runtime_error(std::string("invalid character: " + std::string(&c, 1) + " (" + std::to_string((int)c) + ")"));
}

int main() {
	std::ifstream input("day3.txt");
	std::array<std::string, 3> lines;
	auto sum = 0;

	while(!input.eof()) {
		for (auto &line: lines)
			std::getline(input, line);

		std::unordered_map<char, int> occurrences;

		for (const auto &line: lines) {
			std::vector<char> chars(line.length());

			std::copy(line.begin(), line.end(), chars.begin());
			std::sort(chars.begin(), chars.end());
			auto end = std::unique(chars.begin(), chars.end());

			std::for_each(chars.begin(), end, [&](auto item) {
				occurrences[item]++;
			});
		}

		for (const auto &item: occurrences) {
			if(item.second >= 3)
				sum += getPriority(item.first);
		}
	}

	std::cout << "Priority sum: " << sum << std::endl;
}

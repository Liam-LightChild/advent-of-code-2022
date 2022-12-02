#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>

int readCalories(std::ifstream &is) {
	std::string s;
	int v = 0;

	do {
		std::getline(is, s);

		if(!s.empty()) {
			v += std::stoi(s);
		}
	} while(!s.empty());

	return v;
}

int main(int argc, char** argv) {
	std::string pathName = "day1.txt";
	if(argc >= 2) pathName = argv[1];

	std::ifstream in(pathName.c_str());
	std::vector<int> ary;

	do {
		ary.emplace_back(readCalories(in));
	} while(!in.eof());

	// This could be replaced with a sort(begin(), end()) and a reverse() call,
	// but this is probably faster. :D
	std::sort(ary.rbegin(), ary.rend());

	auto sum = std::accumulate(ary.begin(), ary.begin() + 3, 0);

	std::cout << sum << std::endl;

	return 0;
}

#include <iostream>
#include <vector>
#include <fstream>

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
	int biggestValue = 0;

	do {
		biggestValue = std::max(biggestValue, readCalories(in));
	} while(!in.eof());

	std::cout << biggestValue << std::endl;

	return 0;
}

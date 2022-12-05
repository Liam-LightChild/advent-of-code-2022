#include <fstream>
#include <iostream>

struct range {
private:
	int start, end;

public:
	explicit range(const std::string& r) {
		auto sep = r.find('-');
		if(sep == std::string::npos) throw std::runtime_error("invalid input format (expected <int>-<int>,<int>-<int>)");

		start = std::stoi(r.substr(0, sep));
		end = std::stoi(r.substr(sep+1));
	}

	[[nodiscard]] inline bool contains(range other) const {
		return other.start >= start && other.end <= end;
	}

	[[nodiscard]] inline bool overlaps(range other) const {
		return contains(other) || (other.start >= start && other.start <= end) || (other.end >= start && other.end <= end);
	}
};

int main() {
	std::ifstream input("day4.txt");
	std::string line;

	int count = 0, overlapping = 0;

	while(!input.eof()) {
		std::getline(input, line);
		if(line.empty()) continue;

		auto sepPos = line.find(',');
		if(sepPos == std::string::npos) throw std::runtime_error("invalid input format (expected <int>-<int>,<int>-<int>)");

		auto firstElf = range(line.substr(0, sepPos));
		auto secondElf = range(line.substr(sepPos+1));

		if(firstElf.contains(secondElf) || secondElf.contains(firstElf))
			count++;

		if(firstElf.overlaps(secondElf) || secondElf.overlaps(firstElf))
			overlapping++;
	}

	std::cout << "Completely overlapping work: " << count << std::endl;
	std::cout << "Partially overlapping work: " << overlapping << std::endl;
}
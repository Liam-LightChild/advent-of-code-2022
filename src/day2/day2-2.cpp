#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>

enum rock_paper_scissors {
	rock = 0,
	paper = 1,
	scissors = 2
};

enum game_state {
	win = +1,
	lose = -1,
	draw = 0
};

constexpr rock_paper_scissors parseRPS(char c) {
	switch (c) {
		case 'A':
			return rock;
		case 'B':
			return paper;
		case 'C':
			return scissors;
		default:
			throw std::runtime_error("invalid input");
	}
}

constexpr game_state parseState(char c) {
	switch (c) {
		case 'X':
			return lose;
		case 'Y':
			return draw;
		case 'Z':
			return win;
		default:
			throw std::runtime_error("invalid input");
	}
}

constexpr int bounded(int v) {
	while(v < 0) v += 3;
	v %= 3;
	return v;
}

struct game {
private:
	rock_paper_scissors opponent;
	game_state desiredState;

public:
	explicit game(std::string str) : opponent(parseRPS(str[0])), desiredState(parseState(str[2])) {}

	[[nodiscard]] rock_paper_scissors getOpponent() const {
		return opponent;
	}

	[[nodiscard]] game_state getDesiredState() const {
		return desiredState;
	}

	[[nodiscard]] int getScore() const {
		switch(desiredState) {
			case win:
				return 6 + (int)bounded(opponent + (int)desiredState) + 1;
			case lose:
				return (int)bounded(opponent + (int)desiredState) + 1;
			case draw:
				return 3 + (int)opponent + 1;
		}
	}
};

int main() {
	std::ifstream input("day2.txt");
	std::string line;

	int sum = 0;

	while(!input.eof()) {
		std::getline(input, line);
		if(line.empty()) continue;

		const game g(line);
		sum += g.getScore();
	}

	std::cout << "score: " << sum << std::endl;
}


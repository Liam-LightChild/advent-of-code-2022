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
	win,
	lose,
	draw
};

constexpr rock_paper_scissors parseRPS(char c) {
	switch (c) {
		case 'A':
		case 'X':
			return rock;
		case 'B':
		case 'Y':
			return paper;
		case 'C':
		case 'Z':
			return scissors;
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
	rock_paper_scissors opponent, self;

public:
	explicit game(std::string str) : opponent(parseRPS(str[0])), self(parseRPS(str[2])) {}

	[[nodiscard]] rock_paper_scissors getOpponent() const {
		return opponent;
	}

	[[nodiscard]] rock_paper_scissors getSelf() const {
		return self;
	}

	[[nodiscard]] game_state getState() const {
		if(opponent == self) return draw;
		if(opponent == bounded(self + 1)) return lose;
		if(opponent == bounded(self - 1)) return win;
		throw std::runtime_error("unhandled state");
	}

	[[nodiscard]] int getScore() const {
		switch(getState()) {
			case win:
				return 6 + (int)getSelf() + 1;
			case lose:
				return (int)getSelf() + 1;
			case draw:
				return 3 + (int)getSelf() + 1;
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

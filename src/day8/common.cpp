
#include <fstream>
#include <vector>
#include "common.h"

map readMap(std::ifstream &in) {
    std::vector<std::string> lines;
    std::string line;

    while(!in.eof()) {
        std::getline(in, line);
        if(!line.empty()) lines.emplace_back(line);
    }

    map m(static_cast<int>(lines[0].length()), static_cast<int>(lines.size()));

    for (int j = 0; j < lines.size(); ++j) {
        for (int i = 0; i < lines[j].size(); ++i) {
            m[{i, j}] = std::stoi(std::string(&lines[j][i], 1));
        }
    }

    return m;
}
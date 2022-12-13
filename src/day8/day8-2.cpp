#include <iostream>
#include <vector>
#include <fstream>
#include "common.h"

struct visible_map {
    int width;
    int height;
    uint32_t *pixels;

    explicit visible_map(const map &m) : width(m.width), height(m.height), pixels(new uint32_t[width * height]) {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                auto v = m[{i, j}];
                auto a = travel(i, j, 0, -1, m, v);
                auto b = travel(i, j, -1, 0, m, v);
                auto c = travel(i, j, 0, +1, m, v);
                auto d = travel(i, j, +1, 0, m, v);
                auto e = a * b * c * d;
                std::cout << i << ',' << j << ": "
                          << a << " * "
                          << b << " * "
                          << c << " * "
                          << d << " = "
                          << e << std::endl;
                pixels[j * width + i] = e;
            }
        }
    }

    const uint32_t &operator[](const xy &v) const {
        return pixels[v.y * width + v.x];
    };

    [[nodiscard]] int findBest() const {
        int max = 0, value;

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                if((value = operator[]({i, j})) > max) max = value;
            }
        }

        return max;
    }

private:
    static int travel(int x, int y, int dx, int dy, const map &m, int value) {
        int distance = 0;
        do {
           x += dx;
           y += dy;
           if(x < 0 || y < 0 || x >= m.width || y >= m.height) return distance;

           distance += abs(dx) + abs(dy);
           if(m[{x, y}] >= value) return distance;
        } while(true);
    }
};

int main() {
    std::ifstream in("day8.txt");

    std::cout << visible_map(readMap(in)).findBest() << std::endl;
}

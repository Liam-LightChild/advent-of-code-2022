#include <iostream>
#include <vector>
#include <fstream>
#include "common.h"

struct visible_map {
    int width;
    int height;
    bool *pixels;

    explicit visible_map(const map &m) : width(m.width), height(m.height), pixels(new bool[width * height]) {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                auto v = m[{i, j}];
                pixels[j * width + i] =
                        travel(i, j, +1, 0, m, v) ||
                        travel(i, j, -1, 0, m, v) ||
                        travel(i, j, 0, +1, m, v) ||
                        travel(i, j, 0, -1, m, v);
            }
        }
    }

    ~visible_map() {
        delete[] pixels;
    }

    const bool &operator[](const xy &v) const {
        return pixels[v.y * width + v.x];
    };

    [[nodiscard]] int findBest() const {
        int count = 0;

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                count += operator[]({i, j});
            }
        }

        return count;
    }

private:
    static bool travel(int x, int y, int dx, int dy, const map &m, int value) {
        do {
           x += dx;
           y += dy;
           if(x < 0 || y < 0 || x >= m.width || y >= m.height) return true;

           if(m[{x, y}] >= value) return false;
        } while(true);
    }
};

int main() {
    std::ifstream in("day8.txt");

    std::cout << visible_map(readMap(in)).findBest() << std::endl;
}

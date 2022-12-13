
#ifndef AOC2022_COMMON_H
#define AOC2022_COMMON_H

struct xy {
    int x, y;
};

struct map {
    int width;
    int height;
    uint8_t *pixels;

    map(int w, int h) : width(w), height(h), pixels(new uint8_t[w * h]) {}

    uint8_t &operator[](const xy &v) const {
        return pixels[v.y * width + v.x];
    };
};

map readMap(std::ifstream &in);

#endif //AOC2022_COMMON_H

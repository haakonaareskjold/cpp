#include <iostream>

struct Point {
    int x;
    int y;

     Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

int main (int argv, char** argc) {
    for (int i= 1; i < argv; i++) {
    std::cout << argc[i] << '\n';
    }
}
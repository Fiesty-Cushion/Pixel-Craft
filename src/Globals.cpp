#include "Globals.h"

#include "Color.hpp"
#include "Image.hpp"
#include "Vector2.hpp"

raylib::Vector2 mousePos;
raylib::Image image;
raylib::Color colors[MAX_COLORS_COUNT];
int colorSelected;

long fact(int n) {
    if (n == 0)
        return 1;
    long product = 1;

    for (int i = 1; i <= n; i++) {
        product *= i;
    }

    return product;
}

long nCr(int n, int r) {
    return fact(n) / (fact(r) * fact(n - r));
}

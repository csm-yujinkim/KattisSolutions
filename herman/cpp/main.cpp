#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    size_t r, r_squared;
    std::cin >> r;
    r_squared = r * r;
    std::cout << std::fixed << std::setprecision(6);
    auto const normal_circle_area = M_PI * r_squared;
    auto const taxicab_circle_area = (double)(2 * r_squared);
    std::cout << normal_circle_area << '\n' << taxicab_circle_area;
    return 0;
}

#include <iostream>
#include <algorithm>
#include <string>

static std::string expand(size_t n, const std::string &from) {
    if (n == 1uL) {
        return std::string(from);
    }
    else {
        std::string expanded;
        expanded.reserve(n * from.size());
        for (char const c : from) {
            for (size_t i = 0uL; i < n; ++i) {
                expanded.push_back(c);
            }
        }
        return expanded;
    }
}

int main() {
    size_t r, c, column_expand, row_expand;
    std::cin >> r >> c >> column_expand >> row_expand;
    std::cin.ignore(); // \n dangling
    for (size_t i = 0uL; i < r; ++i) {
        std::string in_line;
        std::getline(std::cin, in_line);
        std::string expanded_row = expand(row_expand, in_line);
        for (size_t j = 0uL; j < column_expand; ++j) {
            std::cout << expanded_row << '\n';
        }
    }
    return 0;
}

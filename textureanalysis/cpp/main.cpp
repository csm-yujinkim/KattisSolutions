#include <iostream>
#include <cassert>

int main() {
    size_t case_number = 0uL;
    std::string row;
    while (std::getline(std::cin, row) && row[0] != 'E') {
        // row exists and is not "END" (exact instance where first letter is 'E')
        if (row.size() == 1uL) {
            std::cout << ++case_number << " EVEN\n";
            continue;
        }
        bool good = true;
        size_t l = 0uL;
        // Find the pattern length (l)
        // the index of the second black ('*') letter is l.
        for (size_t i = 1uL; i < row.size(); ++i) {
            if (row[i] == '*') {
                l = i;
                break;
            }
        }
        for (size_t i = 0uL; i < row.size(); ++i) {
            if (i % l == 0uL) {
                if (row[i] == '.') {
                    good = false;
                    break;
                }
            }
            else {
                if (row[i] == '*') {
                    good = false;
                    break;
                }
            }
        }
        std::cout << ++case_number
            << (good ? " EVEN\n" : " NOT EVEN\n");
    }
    return 0;
}

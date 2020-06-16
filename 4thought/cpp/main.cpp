#include <iostream>
#include <unordered_map>

static std::unordered_map<int, char const *> outputs{
        {-60, "4 - 4 * 4 * 4"},
        {-16, "4 - 4 - 4 * 4"}, // 2 sols
        {-15, "4 / 4 - 4 * 4"},
        {-8,  "4 - 4 - 4 - 4"}, // 3 sols
        {-7,  "4 / 4 - 4 - 4"},
        {-4,  "4 / 4 / 4 - 4"},
        {-1,  "4 - 4 - 4 / 4"}, // 2 sols
        {0,   "4 - 4 + 4 - 4"}, // 11 sols
        {1,   "4 + 4 / 4 - 4"}, // 6 sols
        {2,   "4 / 4 + 4 / 4"},
        {4,   "4 + 4 / 4 / 4"}, // 3 sols all involving (4 / 4 / 4 = 0)
        {7,   "4 + 4 - 4 / 4"}, // 2 sols
        {8,   "4 + 4 + 4 - 4"}, // 8 sols
        {9,   "4 / 4 + 4 + 4"}, // 3 sols
        {15,  "4 * 4 - 4 / 4"},
        {16,  "4 + 4 + 4 + 4"}, // 8 sols
        {17,  "4 * 4 + 4 / 4"}, // 2 sols
        {24,  "4 + 4 + 4 * 4"}, // 3 sols
        {32,  "4 * 4 + 4 * 4"},
        {60,  "4 * 4 * 4 - 4"},
        {68,  "4 * 4 * 4 + 4"}, // 2 sols
        {256, "4 * 4 * 4 * 4"}
};

int main() {
    size_t n;
    std::cin >> n;
    while (n--) {
        int x;
        std::cin >> x;
        if (outputs.count(x)) {
            std::cout << outputs.at(x) << " = " << x << '\n';
        } else {
            std::cout << "no solution\n";
        }
    }
    return 0;
}

#include <unordered_map>
#include <algorithm>
#include <iostream>

int main() {
    size_t n_cases;
    std::cin >> n_cases;
    for (size_t c = 1; c <= n_cases; ++c) {
        size_t n_people;
        std::cin >> n_people;
        std::unordered_map<size_t, size_t> pairs;   // id -> counts
        for (size_t i = 0; i < n_people; ++i) {
            size_t pair_id;
            std::cin >> pair_id;
            ++pairs[pair_id];
        }
        for (auto const &it : pairs) {
            if (it.second == 1) {
                std::cout << "Case #" << c << ": " << it.first << '\n';
                break;
            }
        }
    }
    return 0;
}

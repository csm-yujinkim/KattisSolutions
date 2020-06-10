#include <iostream>
#include <algorithm>
#include <vector>

static void print_names(std::vector<std::string> const &names, std::vector<size_t> const &indices) {
    for (size_t i : indices) {
        std::cout << names[i] << ' ';
    }
    std::cout << '\n';
}

static void print_subsets(std::vector<std::string> const &names, std::vector<size_t> const &indices) {
    if (indices.empty()) {
        for (size_t i = 0uL; i < names.size(); ++i) {
            std::vector<size_t> singleton{i};
            print_subsets(names, singleton);
        }
    }
    else {
        size_t const max = *std::max_element(indices.cbegin(), indices.cend());
        std::vector<size_t> new_indices;
        for (size_t i = max + 1uL; i < names.size(); ++i) {
            new_indices.push_back(i);
        }
        print_names(names, indices);
        if (!new_indices.empty()) {
            for (size_t i : new_indices) {
                auto old_copy = indices;
                old_copy.push_back(i);
                print_subsets(names, old_copy);
            }
        }
    }
}

int main() {
    std::vector<std::string> names {
        "Victor",
        "Jacob",
        "Plasma",
        "Spencer",
        "Martha",
        "Zoe",
        "Joe"
    };
    std::vector<size_t> initial_indices {};
    print_subsets(names, initial_indices);
    return 0;
}

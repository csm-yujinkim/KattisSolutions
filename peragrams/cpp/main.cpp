#define NDEBUG

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <cassert>
#include <vector>

namespace algorithm {
    class frequency_t {
    public:
        // Calculates peragrams
        [[nodiscard]] static size_t peragrams(std::string const &word) {
            frequency_t temporary(word);
            return temporary.peragrams();
        }
    private:
        size_t size_m;
        std::set<size_t> counts;
        std::map<size_t, std::set<char>> freqs;
        // Construct the data structure
        explicit frequency_t(std::string const &word) : size_m(word.size()) {
            assert(!word.empty());
            std::map<char, size_t> bag;
            for (char const c : word) {
                ++bag[c];
            }
            for (auto const &[c, n] : bag) {
                counts.insert(n);
                freqs[n].insert(c);
            }
        }

        // Pop the least
        char pop() {
            size_t const lowest_count = *counts.begin();
            assert(lowest_count);
            size_t const lower_count = lowest_count - 1uL;
            std::set<char> &set = freqs.at(lowest_count);
            char const removal = *set.begin();
            set.erase(*set.begin());
            --size_m;
            if (set.empty()) {
                counts.erase(lowest_count);
            }
            if (lower_count) {
                counts.insert(lower_count);
                freqs[lower_count].insert(removal);
            }
            return removal;
        }

        // Is this a peragram now?
        [[nodiscard]] bool peragram() const {
            assert(size_m);
            if (size_m == 1uL) {
                return true;
            }
            size_t remainder = 0uL;
            for (auto const &[count, characters] : freqs) {
                remainder += (count % 2uL) * characters.size();
            }
            return (size_m % 2) == remainder;
        }

        // Destructively count peragrams
        size_t peragrams() {
            size_t count = 0uL;
            while (!peragram()) {
                pop();
                ++count;
            }
            return count;
        }
    };
}

int main() {
    std::string line;
    std::getline(std::cin, line);
    std::cout << algorithm::frequency_t::peragrams(line) << std::endl;
    return 0;
}
#include <iostream>
#include <map>
#include <limits>
#include <algorithm>
#include <vector>

namespace rules {
    typedef std::map<int, std::vector<int>> freq_map;

    static void seatings(freq_map &summary, std::vector<int> const &input) {
        size_t const n = input.size();
        for (size_t i = 0uL; i < n; ++i) {
            auto &freq = summary[input[i]];
            freq.push_back(i);
        }
    }

    static int find_min(std::vector<int> const &xs) {
        return *std::min_element(xs.cbegin(), xs.cend());
    }

    static int awkward(int len_xs, freq_map const &seatings) {
        size_t const n = seatings.size();
        std::vector<int> min_seatings;
        min_seatings.reserve(n);
        for (auto const &[_, indices] : seatings) {
            size_t const p = indices.size();
            switch (p) {
                case 0uL:
                    throw std::exception();
                case 1uL:
                    min_seatings.push_back(len_xs);
                    break;
                default: {
                    // Find the minimum pairwise backward difference
                    size_t const pm1 = p - 1uL;
                    int min_pairwise_bdiff = std::numeric_limits<int>::max();
                    for (size_t i = 0uL; i < pm1; ++i) {
                        int const left = indices[i];
                        int const right = indices[i + 1uL];
                        int const bdiff = right - left;
                        if (bdiff < min_pairwise_bdiff) {
                            min_pairwise_bdiff = bdiff;
                        }
                    }
                    min_seatings.push_back(min_pairwise_bdiff);
                }
            }
        }
        return find_min(min_seatings);
    }
}

static int pipeline(std::vector<int> const &xs) {
    rules::freq_map freq;
    rules::seatings(freq, xs);
    int const x = rules::awkward(static_cast<int>(xs.size()), freq);
    return x;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<int> xs;
    xs.reserve(n);
    while (n--) {
        int x;
        std::cin >> x;
        xs.push_back(x);
    }
    int const r = pipeline(xs);
    std::cout << r << '\n';
    return 0;
}

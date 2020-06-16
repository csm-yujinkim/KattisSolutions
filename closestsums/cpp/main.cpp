#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

typedef int i32;

/// If x is found in xs, then return its index.
/// Otherwise, return the binary of the index of the
/// least item that is larger than x.
/// OR, when such an item does not exist, return ~xs.size().
static ssize_t approx_binary_search(i32 x, std::vector<i32> const &xs) {
    ssize_t high = xs.size();
    ssize_t low = 0L;

    for (;;) {
        ssize_t const len = high - low;
        if (len == 1L) {
            return ~high;
        } else {
            ssize_t const mid = len / 2L + low;
            i32 const at_mid = xs[mid];
            if (at_mid < x) {
                low = mid;
            } else if (x < at_mid) {
                high = mid;
            } else {
                return mid;
            }
        }
    }
}

static i32 difference(i32 a, i32 b) {
    return std::abs(a - b);
}

static i32 closest(i32 x, std::vector<i32> const &xs) {
    ssize_t const index = approx_binary_search(x, xs);
    if (index < 0L) {
        ssize_t const indexR = ~index;
        ssize_t const indexL = indexR - 1L;
        if (indexR >= xs.size()) {
            return xs[indexL];
        } else if (indexL >= 0L) {
            // There is an ambiguity. We find the one
            // with the minimum difference with x.
            i32 const left = xs[indexL];
            i32 const right = xs[indexR];
            if (difference(x, left) < difference(x, right)) {
                return left;
            } else {
                return right;
            }
        } else {
            // indexL = -1 && indexR = 0
            return xs[0L];
        }
    } else {
        // Exact match found.
        return xs[index];
    }
}

static std::vector<i32> pairwise_sums(std::vector<i32> const &xs) {
    size_t const n = xs.size();
    size_t const nm1 = n - 1uL;
    std::vector<i32> sums;

    for (size_t i = 0uL; i < nm1; ++i) {
        for (size_t j = i + 1uL; j < n; ++j) {
            sums.push_back(xs[i] + xs[j]);
        }
    }

    std::sort(sums.begin(), sums.end());

    return sums;
}

static void test_case(std::vector<i32> const &queries, std::vector<i32> const &xs) {
    auto const sums = pairwise_sums(xs);
    for (i32 const query : queries) {
        i32 const sum = closest(query, sums);
        std::cout << "Closest sum to " << query << " is " << sum << ".\n";
    }
}

int main() {
    size_t case_i = 1L;
    size_t n;
    while (std::cin >> n) {
        std::vector<i32> xs;
        xs.reserve(n);
        while (n--) {
            i32 a;
            std::cin >> a;
            xs.push_back(a);
        }

        size_t m;
        std::cin >> m;
        std::vector<i32> queries;
        queries.reserve(m);
        while (m--) {
            i32 q;
            std::cin >> q;
            queries.push_back(q);
        }

        std::cout << "Case " << (case_i++) << ":\n";
        test_case(queries, xs);
    }
    return 0;
}

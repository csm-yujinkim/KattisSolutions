#include <iostream>
#include <unordered_map>
#include <vector>

typedef unsigned __int128 u128;
typedef uint64_t u64;

namespace impl {
    //https://stackoverflow.com/questions/11656241/how-to-print-uint128-t-number-using-gcc
    //            UINT64_MAX   18446744073709551615ULL
    u64 constexpr P10_UINT64 = 10000000000000000000ULL; /* 19 zeros */
    static void print_u128(u128 x) {
        if (x > UINT64_MAX) {
            u128 leading = x / P10_UINT64;
            u64 trailing = x % P10_UINT64;
            print_u128(leading);
            std::cout << trailing;
        } else {
            std::cout << static_cast<u64>(x);
        }
    }

    static std::unordered_map<u128, u128> catalan_memo {
            {0ULL, 1ULL}
    };

    static u128 catalan(u128 x);

    static u128 make_catalan(u128 x);

    static u128 catalan(u128 const x) {
        if (catalan_memo.count(x)) {
            return catalan_memo.at(x);
        } else {
            u128 const y = make_catalan(x);
            catalan_memo[x] = y;
            return y;
        }
    }

    static u128 make_catalan(u128 const x) {
        u128 const xm1 = x - 1ULL;
        u128 prod = 0ULL;
        for (u128 i = 0ULL; i <= xm1; ++i) {
            prod += catalan(i) * catalan(xm1 - i);
        }
        std::cout << "make_catalan(" << x << ") = " << prod << '\n';
        return prod;
    }
}

static u128 catalan(u128 x) { return impl::catalan(x); }

int main() {
    size_t q;
    std::cin >> q;
    std::vector<u128> xs, ys;
    xs.reserve(q);
    ys.reserve(q);
    while (q--) {
        u128 x;
        std::cin >> x;
        xs.push_back(x);
    }
    for (u128 const x : xs) {
        ys.push_back(catalan(x));
    }
    for (u128 const y : ys) {
        std::cout << y << '\n';
    }
    return 0;
}

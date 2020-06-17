#include <iostream>
#include <unordered_map>
#include <vector>

typedef unsigned long long u128;

namespace impl {
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

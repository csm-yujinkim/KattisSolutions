#include <iostream>
#include <unordered_map>

typedef unsigned long long i128;

namespace impl {
    static std::unordered_map<i128, i128> catalan_memo {
            {0ULL, 1ULL}
    };

    static i128 catalan(i128 x);

    static i128 make_catalan(i128 x);

    static i128 catalan(i128 const x) {
        if (catalan_memo.count(x)) {
            return catalan_memo.at(x);
        } else {
            i128 const y = make_catalan(x);
            catalan_memo[x] = y;
            return y;
        }
    }

    static i128 make_catalan(i128 const x) {
        i128 const xm1 = x - 1ULL;
        i128 sum = 0ULL;
        for (i128 i = 0ULL; i < xm1; ++i) {
            sum += catalan(i) + catalan(xm1 - i);
        }
        return sum;
    }
}

static i128 catalan(i128 x) { return impl::catalan(x); }

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

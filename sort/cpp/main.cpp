#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>

typedef std::vector<unsigned> vector;

struct compare {
    std::multiset<unsigned> bag;
    std::map<unsigned, size_t> indices;

    explicit compare(vector const &xs) {
        for (size_t i = 0u; i < xs.size(); ++i) {
            unsigned const x = xs[i];
            bag.insert(x);
            if (!indices.count(x)) {
                indices[x] = i;
            }
        }
    }

    [[nodiscard]] bool operator()(unsigned x, unsigned y) const {
        return bag.count(x) > bag.count(y)
               || (bag.count(x) == bag.count(y) && indices.at(x) < indices.at(y));
    }
};

static void sort(vector &v) {
    compare c(v);
    std::sort(v.begin(), v.end(), c);
}

int main() {
    vector v;
    {
        unsigned n, c;
        std::cin >> n >> c;
        v.reserve(n);
        while (n--) {
            unsigned x;
            std::cin >> x;
            v.push_back(x);
        }
    }
    sort(v);
    for (unsigned const x : v) {
        std::cout << x << ' ';
    }
    return 0;
}

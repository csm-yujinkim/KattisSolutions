#include <vector>
#include <set>
#include <map>
#include <memory>
#include <algorithm>
#include <iostream>

typedef std::vector<unsigned> vector;

struct compare {
private:
    struct vector_context {
        std::multiset<unsigned> bag;
        std::map<unsigned, size_t> indices;
    };

    std::shared_ptr<vector_context> context;

public:
    explicit compare(vector const &xs) : context(new vector_context) {
        for (size_t i = 0u; i < xs.size(); ++i) {
            unsigned const x = xs[i];
            context->bag.insert(x);
            if (!context->indices.count(x)) {
                context->indices[x] = i;
            }
        }
    }

    [[nodiscard]] bool operator()(unsigned x, unsigned y) const {
        return context->bag.count(x) > context->bag.count(y)
               || (context->bag.count(x) == context->bag.count(y)
                   && context->indices.at(x) < context->indices.at(y));
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

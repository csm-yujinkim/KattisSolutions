#define NDEBUG

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cassert>

class list {
    struct greater_functor {
        [[nodiscard]] bool operator()(int x, int y) const {
            return x > y;
        }
    };
    // Sorts numbers from greatest to smallest
    std::set<int, greater_functor> representation;
public:
    explicit list(int x) {
        representation.insert(x);
    }
    bool try_insert(int x) {
        if (representation.count(x - 1)) {
            representation.insert(x);
            return true;
        }
        else {
            return false;
        }
    }
    [[nodiscard]] bool operator<(list const &other) const {
        assert(!representation.empty());
        assert(!other.representation.empty());
        return *this->representation.cbegin() < *other.representation.cbegin();
    }
    void print() const {
        assert(!representation.empty());
        size_t length = representation.size();
        if (length == 1uL) {
            auto x = *representation.cbegin();
            std::cout << x << ' ';
        }
        else if (length == 2uL) {
            auto it = representation.crbegin();
            std::cout << *it << ' ';
            ++it;
            std::cout << *it << ' ';
        }
        else {
            auto at_begin = *representation.crbegin();
            auto at_end = *representation.cbegin();
            std::cout << at_begin << '-' << at_end << ' ';
        }
    }
};

int main() {
    // numbers are sorted ascending order
    std::vector<int> numbers;
    std::vector<list> buckets;
    size_t n;
    std::cin >> n;
    numbers.reserve(n);
    while (n--) {
        int x;
        std::cin >> x;
        numbers.push_back(x);
    }
    std::sort(numbers.begin(), numbers.end());
    for (int x : numbers) {
        bool inserted = false;
        for (list &bucket : buckets) {
            if (bucket.try_insert(x)) {
                inserted = true;
            }
        }
        if (!inserted) {
            buckets.emplace_back(x);
        }
        std::sort(buckets.begin(), buckets.end());
    }
    for (list const &bucket : buckets) {
        bucket.print();
    }
    return 0;
}

#include <iostream>
#include <queue>
#include <algorithm>
#include <cassert>

namespace program {
    struct interval {
        int start, end;

        interval() {
            start = 0;
            end = 0;
        }

        interval(int start, int end) : start(start), end(end) {}

        // Orders by start point
        [[nodiscard]] bool operator<(interval const &other) const {
            return start < other.start;
        }

        // FIXME: What if the union produces two distinct intervals?
        interval &operator+=(interval const &other) {
            start = std::min(start, other.start);
            end = std::max(end, other.end);
            return *this;
        }

        // Intervals are only valid if the endpoint is greater than or equal to the start point.
        // Intervals of length 0 are accepted and valid.
        [[nodiscard]] bool invalid() const {
            return end < start;
        }
    };

    struct greater_f {
        [[nodiscard]] bool operator()(interval const &left, interval const &right) const {
            return right < left;
        }
    };

    typedef std::priority_queue<interval, std::deque<interval>, greater_f> pq;

    static bool
    greedy_cover(interval &range, pq &touching_candidates, std::queue<interval> &solution) {
        size_t n = touching_candidates.size();
        while (n--) {
            auto const x = touching_candidates.top();
            touching_candidates.pop();
            if (range < x) {
                return false;
            } else {
                solution.push(x);
                range.start = x.end;
                if (range.invalid()) {
                    return true;
                }
            }
        }
        return true;
    }
}

int main() {
    // Test
    program::interval range(-5, 10);
    program::pq touch;
    touch.emplace(-9, -1);
    touch.emplace(-2, 20);
    touch.emplace(-7, 10);
    std::queue<program::interval> solution;
    bool const result = program::greedy_cover(range, touch, solution);
    assert(result);
    assert(solution.size() == 1uL);
    program::interval s = solution.front();
    assert(s.start == -7);
    assert(s.end == 10);
    return 0;
}

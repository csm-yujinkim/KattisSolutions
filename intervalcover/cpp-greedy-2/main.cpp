#include <iostream>
#include <utility>
#include <vector>
#include <list>

struct interval {
    double start, end;

    interval(double start, double end) : start(start), end(end) {}

    [[nodiscard]] bool proper() const {
        return start < end;
    }

    [[nodiscard]] bool covers(interval other) const {
        return this->start <= other.start && other.end <= this->end;
    }
};

namespace help {
    struct problem {
        interval range;
        std::list<ssize_t> indices;
        std::vector<interval> const &intervals;

        problem(interval range,
                std::list<ssize_t> indices,
                std::vector<interval> const &intervals) : range(range),
                                                          indices(std::move(indices)),
                                                          intervals(intervals) {}
    };

    // Finds the element with the maximum intersection with range. Then,
    // 1. Removes that index;
    // 2. Returns the index (now invalid);
    // 3. Returns what was stored at the index.
    static std::pair<ssize_t, interval>
    max_cover(problem &s, interval range) {
        double max_coverage = -1.0;
        auto it = s.indices.begin();
        auto max_it = s.indices.end();
        ssize_t max_index = -1L, index = 0L;
        for (interval i : s.intervals) {
            double const coverage = std::max(0.0, std::min(i.end, range.end) - std::min(i.start, range.start));
            if (max_coverage < coverage) {
                max_coverage = coverage;
                max_index = index;
                max_it = it;
            }
            ++it;
            ++index;
        }
        if (max_it != s.indices.end()) {
            s.indices.erase(max_it);
        }
        return std::make_pair(max_index, s.intervals[max_index]);
    }

    static bool strictly_disjoint(interval a, interval b) {
        return a.end < b.start || b.end < a.start;
    }

    static bool
    union_covers(problem const &s, interval range) {
        double leftmost_endpoint, rightmost_endpoint;
        {
            for (ssize_t const i : s.indices) {
                interval const n = s.intervals[i];
                leftmost_endpoint = std::min(leftmost_endpoint, n.start);
                rightmost_endpoint = std::max(rightmost_endpoint, n.end);
            }
        }
        return interval(leftmost_endpoint, rightmost_endpoint).covers(range);
    }

    static std::vector<interval> forward_difference(interval minuend, interval subtrahend) {
        // The subtrahend is subtracted FROM the minuend.
        // The end result may be a list (vector) of 0, 1 or 2 intervals.
        // If two intervals result, then the first one comes before (has lower coordinates) than the other.
        // Both the minuend and the subtrahend are assumed to be proper. (This is not checked.)
        // The resultants will also be proper.
        interval const left(minuend.start, subtrahend.start);
        interval const right(subtrahend.end, minuend.end);
        std::vector<interval> resultants;
        if (left.proper()) {
            resultants.push_back(left);
        }
        if (right.proper()) {
            resultants.push_back(right);
        }
        return resultants;
    }
}


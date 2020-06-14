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
    static std::pair<ssize_t, interval>
    max_cover(std::list<ssize_t> const &indices, std::vector<interval> const &intervals, interval range) {
        double max_coverage = -1.0;
        ssize_t max_index = -1L, index = 0L;
        for (interval i : intervals) {
            double const coverage = std::max(0.0, std::min(i.end, range.end) - std::min(i.start, range.start));
            if (max_coverage < coverage) {
                max_coverage = coverage;
                max_index = index;
            }
            ++index;
        }
        return std::make_pair(max_index, intervals[max_index]);
    }

    static bool strictly_disjoint(interval a, interval b) {
        return a.end < b.start || b.end < a.start;
    }

    static bool
    union_covers(std::list<ssize_t> const &indices, std::vector<interval> const &intervals, interval range) {
        double leftmost_endpoint, rightmost_endpoint;
        {
            for (ssize_t const i : indices) {
                interval const n = intervals[i];
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
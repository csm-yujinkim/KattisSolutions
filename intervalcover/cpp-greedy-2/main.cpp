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
}
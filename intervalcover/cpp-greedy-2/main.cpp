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
    max_cover(problem &s) {
        double max_coverage = -1.0;
        auto it = s.indices.begin();
        auto max_it = s.indices.end();
        ssize_t max_index = -1L, index = 0L;
        for (auto const a : s.indices) {
            interval const i = s.intervals[a];
            double const coverage = std::max(0.0, std::min(i.end, s.range.end) - std::max(i.start, s.range.start));
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
    union_covers(problem const &s) {
        double leftmost_endpoint, rightmost_endpoint;
        {
            for (ssize_t const i : s.indices) {
                interval const n = s.intervals[i];
                leftmost_endpoint = std::min(leftmost_endpoint, n.start);
                rightmost_endpoint = std::max(rightmost_endpoint, n.end);
            }
        }
        return interval(leftmost_endpoint, rightmost_endpoint).covers(s.range);
    }

    // The subtrahend is subtracted FROM the minuend.
    // The end result may be a list (vector) of 0, 1 or 2 intervals.
    // If two intervals result, then the first one comes before (has lower coordinates) than the other.
    // Both the minuend and the subtrahend are assumed to be proper. (This is not checked.)
    // The resultants will also be proper.
    static std::vector<interval> forward_difference(interval minuend, interval subtrahend) {
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

static std::list<ssize_t> interval_covers(help::problem &problem) {
    // Block 1
    auto const[s_i, s] = help::max_cover(problem);
    auto const difference = help::forward_difference(problem.range, s);
    if (help::strictly_disjoint(s, problem.range)) {
        return std::list<ssize_t>();
    }
    // Block 2
    if (s.covers(problem.range)) {
        return std::list<ssize_t>{s_i};
    }
    // Block 3
    if (problem.indices.empty()) {
        return std::list<ssize_t>();
    }
    // Blocks 4-5 (concurrent execution possible)
    std::list<ssize_t> left_sub, right_sub;
    // Block 4 (left subproblem)
    if (difference.size() > 0uL && difference.at(0).proper()) {
        help::problem copy_problem(problem);
        copy_problem.range = difference.at(0);
        left_sub = interval_covers(problem);
    }
    // Block 5 (right subproblem)
    if (difference.size() > 1uL && difference.at(1).proper()) {
        help::problem copy_problem(problem);
        copy_problem.range = difference.at(1);
        right_sub = interval_covers(problem);
    }
    // Join: Blocks 4-5
    left_sub.push_back(s_i);
    left_sub.merge(right_sub);
    help::problem p(problem.range, left_sub, problem.intervals);
    if (help::union_covers(p)) {
        return left_sub;
    } else {
        return std::list<ssize_t>();
    }
}

int main() {
    for (;;) {
        std::vector<interval> intervals;
        std::list<ssize_t> indices;
        double left, right;
        size_t n;
        if (std::cin >> left >> right) {
            interval range(left, right);
            std::cin >> n;
            for (ssize_t i = 0L; i < n; ++i) {
                double sub_left, sub_right;
                std::cin >> sub_left >> sub_right;
                interval sub(sub_left, sub_right);
                if (sub.proper()) {
                    intervals.push_back(sub);
                    indices.push_back(i);
                }
            }

            // Construct & solve the problem
            help::problem p(range, indices, intervals);
            auto const solution = interval_covers(p);

            // Report the problem
            size_t const sol_n = solution.size();
            if (sol_n) {
                std::cout << sol_n << '\n';
                for (auto const i : solution) {
                    std::cout << i << '\n';
                }
            } else {
                std::cout << "impossible\n";
            }
        } else {
            return 0;
        }
    }
}

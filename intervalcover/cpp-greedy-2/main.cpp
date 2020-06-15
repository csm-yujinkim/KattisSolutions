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
        ssize_t max_index = -1L;
        for (auto const a : s.indices) {
            interval const i = s.intervals[a];
            double const coverage = std::max(0.0, std::min(i.end, s.range.end) - std::max(i.start, s.range.start));
            if (max_coverage < coverage) {
                max_coverage = coverage;
                max_index = a;
                max_it = it;
            }
            ++it;
        }
        if (max_it != s.indices.end()) {
            s.indices.erase(max_it);
        }
        return std::make_pair(max_index, s.intervals[max_index]);
    }

    static bool disjoint(interval a, interval b) {
        return a.end <= b.start || b.end <= a.start;
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
        if (disjoint(minuend, subtrahend)) {
            return std::vector<interval>();
        }
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
    if (help::disjoint(s, problem.range)) {
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
        left_sub = interval_covers(copy_problem);
    }
    // Block 5 (right subproblem)
    if (difference.size() > 1uL && difference.at(1).proper()) {
        help::problem copy_problem(problem);
        copy_problem.range = difference.at(1);
        right_sub = interval_covers(copy_problem);
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

static void multiply_million(interval &i) {
    i.start *= 1000000;
    i.end *= 1000000;
}

int main() {
    for (;;) {
        std::vector<interval> intervals;
        std::list<ssize_t> indices;
        double left, right;
        size_t n;
        if (std::cin >> left >> right) {
            interval range(left, right);
            multiply_million(range);
            std::cin >> n;
            for (ssize_t i = 0L; i < n; ++i) {
                double sub_left, sub_right;
                std::cin >> sub_left >> sub_right;
                interval sub(sub_left, sub_right);
                multiply_million(sub);
                intervals.push_back(sub);
                indices.push_back(i);
            }

            // Construct & solve the problem
            help::problem p(range, indices, intervals);
            if (range.proper()) {
                std::list<ssize_t> solution;
                if (!intervals.empty()) {
                    solution = interval_covers(p);
                }

                // Report the problem
                size_t const sol_n = solution.size();
                if (sol_n) {
                    std::cout << sol_n << '\n';
                    for (auto const i : solution) {
                        std::cout << i << ' ';
                    }
                    std::cout << '\n';
                } else {
                    std::cout << "impossible\n";
                }
            } else {
                // If the range isn't proper, then we use a special routine.
                for (auto const a : p.indices) {
                    if (p.intervals[a].covers(p.range)) {
                        std::cout << "1\n" << a << '\n';
                        goto exit_inner_for;
                    }
                }
                std::cout << "impossible\n";
                exit_inner_for:;
            }
        } else {
            return 0;
        }
    }
}

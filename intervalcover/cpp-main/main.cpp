#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

namespace internal {
    namespace types {
        // Inclusive interval
        struct interval {
            int start, end;
            interval(int start, int end) : start(start), end(end) {}
            // Union
            interval &operator+=(interval const &other) {
                start = std::min(start, other.start);
                end = std::max(end, other.end);
                return *this;
            }
            // Covers another?
            [[nodiscard]] bool covers(interval const &other) const {
                return start <= other.start && end >= other.end;
            }
        };
    }
    namespace algorithm {
        static types::interval unionize(std::vector<types::interval> const &intervals) {
            assert(!intervals.empty());
            auto it = intervals.cbegin();
            auto seed = *it++;
            for (; it != intervals.cend(); ++it) {
                seed += *it;
            }
            return seed;
        }

        static std::vector<size_t> min_intervals;

        static void process_power_sets(types::interval const &range, std::vector<types::interval> const &set, std::vector<size_t> &indices) {
            if (indices.empty()) {
                for (size_t i = 0uL; i < set.size(); ++i) {
                    std::vector<size_t> singleton{i};
                    process_power_sets(range, set, singleton);
                }
            } else {
                size_t const max = *std::max_element(indices.cbegin(), indices.cend());
                std::vector<size_t> new_indices;
                for (size_t i = max + 1uL; i < set.size(); ++i) {
                    new_indices.push_back(i);
                }
                // Process: START
                {
                    std::vector<types::interval> filter;
                    filter.reserve(indices.size());
                    for (size_t i : indices) {
                        filter.push_back(set[i]);
                    }
                    auto altogether = unionize(filter);
                    if (altogether.covers(range)) {
                        if (indices.size() < min_intervals.size()) {
                            min_intervals = indices;
                        }
                    }
                }
                // Process: End
                if (!new_indices.empty()) {
                    for (size_t i : new_indices) {
                        indices.push_back(i);
                        process_power_sets(range, set, indices);
                        indices.pop_back();
                    }
                }
            }
        }
        static void report() {
            std::cout << min_intervals.size() << '\n';
            for (size_t i : min_intervals) {
                std::cout << i << ' ';
            }
            std::cout << '\n';
        }
    }
}

int main() {
    int start, end;
    while (std::cin >> start >> end) {
        start *= 100000;
        end *= 100000;
        internal::types::interval range(start, end);
        size_t n;
        std::cin >> n;
        std::vector<internal::types::interval> intervals;
        std::vector<size_t> empty;
        intervals.reserve(n);
        while (n--) {
            double start2, end2;
            std::cin >> start2 >> end2;
            intervals.emplace_back(start2 * 100000, end2 * 100000);
        }
        internal::algorithm::process_power_sets(range, intervals, empty);
        internal::algorithm::report();
    }
    return 0;
}

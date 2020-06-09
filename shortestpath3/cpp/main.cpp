#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>

static ssize_t const INF = std::numeric_limits<ssize_t>::max();
static ssize_t const UNDEFINED_PREDECESSOR = -1L;

struct edge_t {
    ssize_t from, to, weight;

    edge_t(ssize_t from, ssize_t to, ssize_t weight) : from(from), to(to), weight(weight) {}
};

static std::pair<std::vector<bool>, std::vector<ssize_t>>
bellman_ford(std::vector<edge_t> const &edges, size_t const n_nodes, ssize_t source) {
    std::vector<ssize_t> predecessor(n_nodes, UNDEFINED_PREDECESSOR);
    std::vector<ssize_t> distances(n_nodes, INF);
    std::vector<bool> inclusion(n_nodes, true);
    distances[source] = 0L;

    size_t nm1 = n_nodes - 1uL;
    bool iter_stay = true;
    for (size_t i = 0uL; i < nm1; ++i) {
        for (auto const &edge : edges) {
            ssize_t const early_estimate = distances[edge.to];
            ssize_t const newer_estimate = edge.weight + distances[edge.from];
            if (distances[edge.from] != INF && newer_estimate < early_estimate) {
                distances[edge.to] = newer_estimate;
                predecessor[edge.to] = edge.from;
                iter_stay = false;
            }
        }
        if (iter_stay) {
            return std::make_pair(inclusion, distances);
        }
    }

    for (ssize_t i = 0uL; i < predecessor.size(); ++i) {
        bool cycle_exists = false;
        std::vector<ssize_t> chain{i};
        ssize_t x = predecessor[i];
        while (x != -1) {
            if (std::any_of(chain.cbegin(), chain.cend(), [x](ssize_t y) { return x == y; })) {
                chain.push_back(x);
                cycle_exists = true;
                break;
            } else {
                chain.push_back(x);
                x = predecessor[x];
            }
        }
        if (cycle_exists) {
            for (ssize_t z : chain) {
                inclusion[z] = false;
            }
        }
    }

    return std::make_pair(inclusion, distances);
}

int main() {
    for (;;) {
        ssize_t n_nodes, n_edges, n_queries, source;
        std::cin >> n_nodes >> n_edges >> n_queries >> source;
        if (!n_nodes) {
            return 0;
        }

        std::vector<edge_t> edges;
        edges.reserve(n_edges);
        while (n_edges--) {
            ssize_t from, to, weight;
            std::cin >> from >> to >> weight;
            edges.emplace_back(from, to, weight);
        }

        std::vector<ssize_t> queries;
        queries.reserve(n_queries);
        while (n_queries--) {
            ssize_t v;
            std::cin >> v;
            queries.push_back(v);
        }

        auto const &[inclusion, minimum] = bellman_ford(edges, n_nodes, source);
        for (ssize_t v : queries) {
            if (inclusion[v]) {
                ssize_t distance = minimum[v];
                if (distance == INF) {
                    std::cout << "Impossible\n";
                } else {
                    std::cout << distance << '\n';
                }
            } else {
                std::cout << "-Infinity\n";
            }
        }

        std::cout << '\n';
    }
}

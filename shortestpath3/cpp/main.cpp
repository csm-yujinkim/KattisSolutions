#include <iostream>
#include <vector>
#include <utility>
#include <limits>

static ssize_t const INF = std::numeric_limits<ssize_t>::max();

struct edge_t {
    size_t from, to;
    ssize_t weight;

    edge_t(size_t from, size_t to, ssize_t weight) : from(from), to(to), weight(weight) {}
};

static std::pair<std::vector<bool>, std::vector<ssize_t>>
bellman_ford(std::vector<edge_t> const &edges, size_t const n_nodes, size_t source) {
    std::vector<bool> inclusion(n_nodes, true);
    std::vector<ssize_t> distances(n_nodes, INF);
    bool iter_update_made = false;
    distances[source] = 0L;

    size_t nm1 = n_nodes - 1uL;
    for (size_t i = 0uL; i < nm1; ++i) {
        for (auto const &edge : edges) {
            ssize_t const early_estimate = distances[edge.to];
            ssize_t const newer_estimate = edge.weight + distances[edge.from];
            if (distances[edge.from] != INF && newer_estimate < early_estimate) {
                distances[edge.to] = newer_estimate;
                iter_update_made = true;
            }
            // Early exit
            if (!iter_update_made) {
                return std::make_pair(inclusion, distances);
            }
        }
    }

    std::vector<ssize_t> distances_check_copy = distances;
    for (auto const &edge : edges) {
        ssize_t const early_estimate = distances_check_copy[edge.to];
        ssize_t const newer_estimate = edge.weight + distances_check_copy[edge.from];
        if (distances_check_copy[edge.from] != INF && newer_estimate < early_estimate) {
            distances_check_copy[edge.to] = newer_estimate;
            inclusion[edge.to] = false;
        }
        // else = exactly when detecting a vertex on negative cycle.
    }

    return std::make_pair(inclusion, distances);
}

int main() {
    for (;;) {
        size_t n_nodes, n_edges, n_queries;
        ssize_t source;
        std::cin >> n_nodes >> n_edges >> n_queries >> source;
        if (!n_nodes) {
            return 0;
        }

        std::vector<edge_t> edges;
        edges.reserve(n_edges);
        while (n_edges--) {
            size_t from, to;
            ssize_t weight;
            std::cin >> from >> to >> weight;
            edges.emplace_back(from, to, weight);
        }

        std::vector<size_t> queries;
        queries.reserve(n_queries);
        while (n_queries--) {
            size_t v;
            std::cin >> v;
            queries.push_back(v);
        }

        auto const &[inclusion, minimum] = bellman_ford(edges, n_nodes, source);
        for (size_t v : queries) {
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

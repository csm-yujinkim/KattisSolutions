#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

[[nodiscard]] static double average(std::vector<double> const &xs) {
    assert(!xs.empty());
    double sum = std::reduce(xs.cbegin(), xs.cend());
    double n = xs.size();
    return sum / n;
}

int main() {
    size_t n;
    std::cin >> n;
    while (n--) {
        std::cin.get(); // ignore \n
        size_t n_cs, n_ec;
        std::cin >> n_cs >> n_ec;
        std::vector<double> computer_science, economics;
        computer_science.reserve(n_cs);
        economics.reserve(n_ec);
        while (n_cs--) {
            size_t iq;
            std::cin >> iq;
            computer_science.push_back((double) iq);
        }
        while (n_ec--) {
            size_t iq;
            std::cin >> iq;
            economics.push_back((double) iq);
        }
        double const cs_avg = average(computer_science);
        double const ec_avg = average(economics);
        size_t const count = std::count_if(computer_science.cbegin(), computer_science.cend(),
                                           [cs_avg, ec_avg](double iq) {
                                               return (ec_avg < iq) && (iq < cs_avg);
                                           });
        std::cout << count << '\n';
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cinttypes>

using namespace std;

vector<uint32_t> inputs;

void task_two_sum() {
    uint32_t constexpr SUM = 7777;
    unordered_set<uint32_t> q;
    for (uint32_t input : inputs) {
        if (q.count(SUM - input)) {
            cout << "Yes\n";
            return;
        } else {
            q.insert(input);
        }
    }
    cout << "No\n";
}

void task_uniqueness() {
    unordered_set<uint32_t> enc;
    for (uint32_t input : inputs) {
        if (enc.count(input)) {
            cout << "Contains duplicate\n";
            return;
        } else {
            enc.insert(input);
        }
    }
    cout << "Unique\n";
}

void task_absolute_majority() {
    unordered_map<uint32_t, size_t> histogram;
    for (uint32_t input : inputs) {
        histogram[input]++;
    }
    uint32_t m_k = -1;
    size_t const nd2 = inputs.size() >> 1u;
    for (auto const &[k, s] : histogram) {
        if (s > nd2) {
            m_k = k;
        }
    }
    if (m_k != -1) {
        cout << m_k << '\n';
    } else {
        cout << "-1\n";
    }
}

void task_median() {
    sort(inputs.begin(), inputs.end());
    bool const n_odd = inputs.size() & 1u;
    size_t const i_mid_left = inputs.size() >> 1u;
    if (n_odd) {
        cout << inputs[i_mid_left] << '\n';
    } else {
        cout << inputs[i_mid_left - 1] << ' '
             << inputs[i_mid_left] << '\n';
    }
}

void task_sort_100_999() {
    sort(inputs.begin(), inputs.end());
    for (auto const input : inputs) {
        if (input >= 100 && input <= 999) {
            cout << input << ' ';
        }
    }
    cout << '\n';
}

int main() {
    size_t n, t;
    cin >> n >> t;
    inputs = vector<uint32_t>(n, 0);
    for (size_t i = 0; i < n; ++i) {
        cin >> inputs[i];
    }
    if (t == 1) {
        task_two_sum();
    } else if (t == 2) {
        task_uniqueness();
    } else if (t == 3) {
        task_absolute_majority();
    } else if (t == 4) {
        task_median();
    } else if (t == 5) {
        task_sort_100_999();
    }
    return 0;
}

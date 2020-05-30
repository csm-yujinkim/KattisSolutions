#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

static vector<int> decompose_number(int n) {
    vector<int> result;
    while (n) {
        result.push_back(n % 10);
        n /= 10;
    }
    sort(result.begin(), result.end());
    return result;
}

static int compose_number(vector<int> const &vector) {
    int power_10 = 1;
    int x = 0;
    for (int const i : vector) {
        x += i * power_10;
        power_10 *= 10;
    }
    return x;
}

int main() {
    // 1. read the integer
    int n;
    cin >> n;

    // 2. generate all valid permutations of the integer, and find the global minimum if exists
    vector<int> digits = decompose_number(n);
    size_t n_perms = 0uL;
    int perm_min = numeric_limits<int>::max();
    do {
        int x = compose_number(digits);
        if (n < x) {
            n_perms += 1;
            perm_min = min(perm_min, x);
        }
    }
    while (next_permutation(digits.begin(), digits.end()));

    // 3. print the result
    cout << (n_perms ? perm_min : 0) << endl;

    return 0;
}
#include <iostream>
#include <algorithm>

using namespace std;

static void reduce_fraction(int &n, int &d) {
    int rem, rm2, rm1;
    rm2 = max(n, d);
    rm1 = min(n, d);
    do {
        rem = rm2 % rm1;
        rm2 = rm1;
        rm1 = rem;
    }
    while (rem);
    // At this point, `rm2` contains gcd of n and d.
    n /= rm2;
    d /= rm2;
}

int main() {
    size_t n;
    cin >> n;

    int first_gear;
    cin >> first_gear;
    n--;
    while (n--) {
        int copy_first_gear = first_gear;
        int subsequent_gear;
        cin >> subsequent_gear;
        reduce_fraction(subsequent_gear, copy_first_gear);
        cout << copy_first_gear << '/' << subsequent_gear << '\n';
    }
    return 0;
}

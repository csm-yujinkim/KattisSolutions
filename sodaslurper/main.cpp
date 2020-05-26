#include <iostream>

using namespace std;

int main() {
    long x_0, c;
    {
        long e, f;
        cin >> e >> f >> c;
        x_0 = e + f;
        if (x_0 < c) {
            cout << "0\n";
            return 0;
        }
    }
    long n = 1 + (x_0 - c) / (c - 1);
    cout << n << '\n';
    return 0;
}

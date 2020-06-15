#include <iostream>

typedef long long i128;

static i128 modll(i128 a, i128 b) {
    return (a % b + b) % b;
}

struct bezout {
    i128 x, gcd;

    bezout(i128 a, i128 b) {
        i128 rm1, rm2, sm1, sm2, tm1, tm2;
        rm1 = b;
        rm2 = a;
        sm1 = tm2 = 0;
        sm2 = tm1 = 1;

        while (rm1) {
            i128 quo = rm2 / rm1; // round toward 0.
            i128 tmpr = rm1;
            rm1 = rm2 - quo * rm1;
            rm2 = tmpr;
            i128 tmps = sm1;
            sm1 = sm2 - quo * sm1;
            sm2 = tmps;
            i128 tmpt = tm1;
            tm1 = tm2 - quo * tm1;
            tm2 = tmpt;
        }

        x = sm2;
        gcd = rm2;
    }
};

int main() {
    i128 n, t;
    while ((std::cin >> n >> t) && n) {
        while (t--) {
            i128 a, b, f;
            char op;
            std::cin >> a >> op >> b;
            switch (op) {
                case '+':
                    f = (a % n + b % n) % n;
                    break;
                case '-':
                    f = modll((a % n - b % n), n);
                    break;
                case '*':
                    f = ((a % n) * (b % n)) % n;
                    break;
                default: /* '/' (division) */
                {
                    bezout bz(b, n);
                    i128 binv = modll(bz.x, n);
                    if (bz.gcd == 1) {
                        f = ((a % n) * binv) % n;
                    } else {
                        f = -1;
                    }
                }
                    break;
            }
            std::cout << f << '\n';
        }
    }
    return 0;
}

#include <iostream>
#include <iomanip>
#include <cmath>

#define M_TO_DEG (180.0 / M_PI)

typedef double float_type;

using namespace std;

[[nodiscard]] static float_type square(float_type const x) {
    return x * x;
}

int main() {
    cout << fixed << setprecision(2);
    for (;;) {
        float_type nb, ma;
        size_t s;
        {
            size_t a, b, m, n;
            cin >> a >> b >> s >> m >> n;
            if (!a || !b || !s || !m || !n) {
                return 0;
            }
            nb = n * b;
            ma = m * a;
        }
        float_type speed = sqrt(square(nb) + square(ma)) / s;
        float_type deg_angle = 90.0 - M_TO_DEG * atan(ma / nb);
        cout << deg_angle << ' ' << speed << '\n';
    }
}

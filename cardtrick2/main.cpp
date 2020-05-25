#define NDEBUG

#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

int main() {
    size_t n;
    cin >> n;
    while (n--) {
        deque<int> q;
        size_t t;
        cin >> t;
        while (t) {
            // push on top
            q.push_front(t);
            // reverse-shuffle
            size_t dbg_keep_size = q.size();
            for (size_t i = 1; i <= t; ++i) {
                int bottom = q.back();
                q.push_front(bottom);
                q.pop_back();
            }
            assert(dbg_keep_size == q.size());
            --t;
        }
        // print the queue, top to bottom
        while (!q.empty()) {
            cout << q.front() << ' ';
            q.pop_front();
        }
        cout << '\n';
    }
    return 0;
}

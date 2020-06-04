#include <iostream>
#include <stack>
#include <deque>

int main() {
    size_t set_id = 0;
    for (;;) {
        size_t n;
        std::cin >> n;
        if (!n) {
            return 0;
        }
        std::stack<std::string> in_names;
        std::deque<std::string> out_names;
        size_t o = n / 2;
        bool rem = n % 2;
        for (size_t i = 0; i < n; ++i) {
            std::string name;
            std::cin >> name;
            in_names.push(name);
        }
        if (rem) {
            for (size_t i = 0; i < o; ++i) {
                out_names.push_front(in_names.top());
                in_names.pop();
                out_names.push_back(in_names.top());
                in_names.pop();
            }
            out_names.push_front(in_names.top());
            in_names.pop();
        } else {
            for (size_t i = 0; i < o; ++i) {
                out_names.push_back(in_names.top());
                in_names.pop();
                out_names.push_front(in_names.top());
                in_names.pop();
            }
        }
        std::cout << "SET " << ++set_id << '\n';
        for (std::string const &name : out_names) {
            std::cout << name << '\n';
        }
    }
}



#include <vector>
#include <queue>
#include <cstring>
#include <cassert>
#include <iostream>

enum op_e {
    PUSH = 1,
    POP = 2
};

static std::vector<op_e> operations;
static std::vector<int> pushes, pops;

static bool probably_queue() {
    // Use naive algorithm
    size_t pushes_front = 0uL, pops_front = 0uL;
    std::queue<int> stack;
    for (auto op : operations) {
        switch (op) {
            case PUSH:
                stack.push(pushes[pushes_front++]);
                break;
            case POP:
                if (stack.front() != pops[pops_front++]) {
                    return false;
                }
                stack.pop();
                break;
        }
    }
    return true;
}

static bool probably_stack() {
    // Use naive algorithm
    size_t pushes_front = 0uL, pops_front = 0uL;
    std::vector<int> stack;
    stack.reserve(operations.size()); // maximum size (worst case; if all operations were of one kind)
    for (auto op : operations) {
        switch (op) {
            case PUSH:
                stack.push_back(pushes[pushes_front++]);
                break;
            case POP:
                if (stack.back() != pops[pops_front++]) {
                    return false;
                }
                stack.pop_back();
                break;
        }
    }
    return true;
}

static bool probably_priority_queue() {
    // Use naive algorithm
    size_t pushes_front = 0uL, pops_front = 0uL;
    std::priority_queue<int> priority_queue;
    for (auto op : operations) {
        switch (op) {
            case PUSH:
                priority_queue.push(pushes[pushes_front++]);
                break;
            case POP:
                if (priority_queue.top() != pops[pops_front++]) {
                    return false;
                }
                priority_queue.pop();
                break;
        }
    }
    return true;
}

static void cleanup() {
    operations = std::vector<op_e>();
    pushes = std::vector<int>();
    pops = std::vector<int>();
}

int main() {
    size_t n;
    while (std::cin >> n) {
        operations.reserve(n);
        pushes.reserve(n);
        pops.reserve(n);
        while (n--) {
            // get data
            int operation, x;
            std::cin >> operation >> x;
            switch (operation) {
                case 1:
                    operations.push_back(PUSH);
                    pushes.push_back(x);
                    break;
                case 2:
                    operations.push_back(POP);
                    pops.push_back(x);
                    break;
                default:
                    throw std::exception();
            }
        }
        if (pushes.size() < pops.size()) {
            std::cout << "impossible\n";
            cleanup();
            continue;
        }
        bool const queue = probably_queue();
        bool const stack = probably_stack();
        bool const priority_queue = probably_priority_queue();
        unsigned const score = queue + stack + priority_queue;
        switch (score) {
            case 0: std::cout << "impossible\n"; goto cleanup;
            case 1:
                if (queue) std::cout << "queue\n";
                if (stack) std::cout << "stack\n";
                if (priority_queue) std::cout << "priority queue\n";
                goto cleanup;
            default:
                std::cout << "not sure\n";
                goto cleanup;
        }
    cleanup:
        cleanup();
    }
    return 0;
}

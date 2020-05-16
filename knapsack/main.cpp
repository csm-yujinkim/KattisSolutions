#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

using namespace std;

#define MY_DEBUG

// The arrays are indexed starting 1
size_t constexpr CAP = 2000ul;
// index of item -> value of that item
size_t values[CAP + 1];
// index of item -> weight of that item
size_t weights[CAP + 1];
// indices of chosen items in ascending order
size_t carry[CAP];
// Bottom-up table (0-indexed both ways)
size_t **ks_table;

size_t weight_limit, n_objects;

// Each number is between 1 and 10000.
// In the worst case every number is 10000.
// There are at most two such numbers in a line.
// "10000 " * 2 + '\0' = 13 characters
// Use 16 characters for safety.
size_t constexpr BUF_LEN = 16;
char in_buf[BUF_LEN];

void make_ks_table() {
    ks_table = new size_t *[n_objects + 1];
    for (size_t r = 0; r <= n_objects; ++r) {
        ks_table[r] = new size_t[weight_limit + 1];
    }
}

void delete_ks_table() {
    for (size_t r = 0; r <= n_objects; ++r) {
        delete[] ks_table[r];
    }
    delete[] ks_table;
}

#ifdef MY_DEBUG
// DEBUG: Prints the ks_table to standard error.
void print_ks_table() {
    if (ks_table) {
        cerr << ',';
        for (size_t c = 0; c <= weight_limit; ++c) {
            cerr << c << ',';
        }
        cerr << '\n';
        for (size_t r = 0; r <= n_objects; ++r) {
            cerr << r << ',';
            for (size_t c = 0; c <= weight_limit; ++c) {
                cerr << ks_table[r][c] << ',';
            }
            cerr << '\n';
        }
        cerr << '\n';
    }
    else {
        cerr << "ks_table NULL\n";
    }
}
#else // MY_DEBUG
static void print_ks_table() {
}
#endif // MY_DEBUG

void fill_knapsack() {
    // Fill row 0 with 0.
    for (size_t c = 0; c <= weight_limit; ++c) {
        ks_table[0][c] = 0;
    }
    // Fill column 0 with 0.
    for (size_t r = 0; r <= n_objects; ++r) {
        ks_table[r][0] = 0;
    }
    // Starting from column = 1 and row = 1, do the following
    // 1. If w_r is greater than weight_limit, then use @(r-1, w_r), and then skip
    // 2. If @(r-1,weight_limit-w_r) + v_r > @(r-1,weight_limit),
    //  then use the first, and then skip
    // 3. Use the second, and then skip
    //
    // "Skip" is defined as follows.
    // 1. If possible, move onto the right column then repeat the procedure
    // 2. Move onto the next row and then repeat the procedure
    // 3. Stop and return @(n_objects, weight_limit)
    for (size_t r = 1; r <= n_objects; ++r) {
        for (size_t c = 1; c <= weight_limit; ++c) {
            size_t const w_r = weights[r];
            size_t const rm1 = r - 1;
            if (c >= w_r) {
                size_t const do_carry = ks_table[rm1][c - w_r] + values[r];
                size_t const dont_carry = ks_table[rm1][c];
                ks_table[r][c] = max(do_carry, dont_carry);
            }
            else {
                ks_table[r][c] = ks_table[rm1][c];
            }
        }
    }
}

// Returns the length of the filled
size_t find_carry() {
    size_t n_carry = 0;
    size_t w = weight_limit;
    for (size_t r = n_objects; r > 0; --r) {
        if (ks_table[r][w] != ks_table[r - 1][w]) {
            w -= weights[r];
            carry[n_carry++] = r;
        }
    }
    sort(carry, carry + n_carry);
    return n_carry;
}

// Accept input until user interrupt
// For each test case,
//  First line: (weight_limit, n_objects)
//  Other lines: n_objects * (value, weight)
int main() {
    //string line;
    while (cin.getline(in_buf, BUF_LEN)) {
        char *idx;
        weight_limit = strtoul(in_buf, &idx, 10);
        n_objects = strtoul(idx + 1, &idx, 10); // +1 to skip space
        for (size_t i = 1; i <= n_objects; ++i) {
            cin.getline(in_buf, BUF_LEN);
            values[i] = strtoul(in_buf, &idx, 10);
            weights[i] = strtoul(idx + 1, &idx, 10); // +1 to skip space
        }
        make_ks_table();
        fill_knapsack();
        size_t const n_carry = find_carry();
        cout << n_carry << '\n';
        for (size_t i = 0; i < n_carry; ++i) {
            // Convert 1-indices to 0-indices
            cout << carry[i] - 1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}

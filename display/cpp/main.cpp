#define NDEBUG

#include <iostream>
#include <array>
#include <algorithm>
#include <cassert>

std::array<std::array<char, 30uL>, 7uL> display;

static void clear_display() {
    for (auto &row : display) {
        std::fill(row.begin(), row.end(), ' ');
        *row.rbegin() = '\0';
    }
}

static void print_display() {
    for (auto const &row : display) {
        char const * const c_row = row.data();
        std::cout << c_row << '\n';
    }
}

typedef std::array<std::array<char, 6uL>, 7uL> pattern_t;

pattern_t const pattern_0 {
    "+---+",
    "|   |",
    "|   |",
    "+   +",
    "|   |",
    "|   |",
    "+---+"
};

pattern_t const pattern_1 {
    "    +",
    "    |",
    "    |",
    "    +",
    "    |",
    "    |",
    "    +"
};

pattern_t const pattern_2 {
    "+---+",
    "    |",
    "    |",
    "+---+",
    "|    ",
    "|    ",
    "+---+"
};

pattern_t const pattern_3 {
    "+---+",
    "    |",
    "    |",
    "+---+",
    "    |",
    "    |",
    "+---+"
};

pattern_t const pattern_4 {
    "+   +",
    "|   |",
    "|   |",
    "+---+",
    "    |",
    "    |",
    "    +"
};

pattern_t const pattern_5 {
    "+---+",
    "|    ",
    "|    ",
    "+---+",
    "    |",
    "    |",
    "+---+"
};

pattern_t const pattern_6 {
    "+---+",
    "|    ",
    "|    ",
    "+---+",
    "|   |",
    "|   |",
    "+---+"
};

pattern_t const pattern_7 {
    "+---+",
    "    |",
    "    |",
    "    +",
    "    |",
    "    |",
    "    +"
};

pattern_t const pattern_8 {
    "+---+",
    "|   |",
    "|   |",
    "+---+",
    "|   |",
    "|   |",
    "+---+"
};

pattern_t const pattern_9 {
    "+---+",
    "|   |",
    "|   |",
    "+---+",
    "    |",
    "    |",
    "+---+"
};

pattern_t const pattern_colon {
    " ",
    " ",
    "o",
    " ",
    "o",
    " ",
    " "
};

std::array<size_t, 5uL> starting_columns {
    0uL, 7uL, 14uL, 17uL, 24uL
};

enum digit_size_e {
    DIGIT = 5uL,
    COLON = 1uL
};

static void pattern_row_copy(pattern_t const &from, digit_size_e digit_size, size_t row, size_t st_col) {
    // copy all except the last character, which is '\0'
    assert(std::all_of(from[row].cbegin(), from[row].cbegin() + digit_size, [](char c) { return c != '\0'; }));
    std::copy_n(from[row].cbegin(), digit_size, display[row].begin() + st_col);
}

static void which_pattern(char c, pattern_t const *&to_ptr, digit_size_e &pattern_width) {
    switch (c) {
        case '0': to_ptr = &pattern_0; pattern_width = DIGIT; break;
        case '1': to_ptr = &pattern_1; pattern_width = DIGIT; break;
        case '2': to_ptr = &pattern_2; pattern_width = DIGIT; break;
        case '3': to_ptr = &pattern_3; pattern_width = DIGIT; break;
        case '4': to_ptr = &pattern_4; pattern_width = DIGIT; break;
        case '5': to_ptr = &pattern_5; pattern_width = DIGIT; break;
        case '6': to_ptr = &pattern_6; pattern_width = DIGIT; break;
        case '7': to_ptr = &pattern_7; pattern_width = DIGIT; break;
        case '8': to_ptr = &pattern_8; pattern_width = DIGIT; break;
        case '9': to_ptr = &pattern_9; pattern_width = DIGIT; break;
        case ':': to_ptr = &pattern_colon; pattern_width = COLON; break;
        default: throw std::exception();
    }
}

static void etch(char character, size_t column) {
    pattern_t const *pattern;
    digit_size_e size;
    which_pattern(character, pattern, size);
    for (size_t i = 0uL; i < display.size(); ++i) {
        pattern_row_copy(*pattern, size, i, column);
    }
}

int main() {
    std::string line;
    while (std::getline(std::cin, line) && line[0] != 'e') {
        assert(line.size() == 5uL);
        clear_display();
        for (size_t i = 0uL; i < 5uL; ++i) {
            etch(line[i], starting_columns[i]);
        }
        print_display();
        std::cout << "\n\n";
    }
    std::cout << "end\n";
    return 0;
}

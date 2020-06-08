

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cassert>

enum life_form_t : char {
    END_C_STR = '\0',
    ROCK = 'R',
    SCISSORS = 'S',
    PAPER = 'P'
};

struct rc_t {
    size_t row, column;

    rc_t(size_t row, size_t column) : row(row), column(column) {}

    [[nodiscard]] rc_t right() const {
        return rc_t(row, column + 1uL);
    }

    [[nodiscard]] rc_t down() const {
        return rc_t(row + 1uL, column);
    }

    [[nodiscard]] bool operator==(rc_t const &other) const {
        return row == other.row && column == other.column;
    }
};

namespace std {
    template<>
    struct hash<rc_t> {
        [[nodiscard]] size_t operator()(const rc_t &coords) const {
            return hash<size_t>()(coords.row) ^ hash<size_t>()(coords.column);
        }
    };
}

static std::array<std::array<life_form_t, 101uL>, 100uL> battleground;
static size_t width, height;
static std::vector<std::pair<rc_t, life_form_t>> transformations;

static void initialize() {
    assert(width);
    assert(height);
    for (auto &row : battleground) {
        std::fill(row.begin(), row.end(), END_C_STR);
    }
    transformations.clear();
}

// Must call initialize(size_t, size_t) first!
static void feed_row(size_t row) {
    std::string line;
    std::getline(std::cin, line);
    assert(line.size() == width);
    for (size_t i = 0uL; i < width; ++i) {
        auto const attempt_convert = static_cast<life_form_t> (line[i]);
        assert(attempt_convert == ROCK || attempt_convert == SCISSORS || attempt_convert == PAPER);
        battleground[row][i] = attempt_convert;
    }
}

static void print_battleground() {
    for (size_t row = 0uL; row < height; ++row) {
        assert(battleground[row][width] == END_C_STR);
        std::cout << (const char *) battleground[row].data() << '\n';
    }
}

static life_form_t &at_battle(rc_t const coords) {
    return battleground[coords.row][coords.column];
}

static void set_battle(life_form_t const life_form, rc_t const coords) {
    transformations.emplace_back(coords, life_form);
}

namespace direction_dependent {
    static void battle_left_right(rc_t const left_pos) {
        rc_t const right_pos = left_pos.right();
        life_form_t const left = at_battle(left_pos);
        life_form_t const right = at_battle(right_pos);
        if (left == ROCK && right == SCISSORS) {
            set_battle(ROCK, right_pos);
        } else if (left == SCISSORS && right == ROCK) {
            set_battle(ROCK, left_pos);
        } else if (left == SCISSORS && right == PAPER) {
            set_battle(SCISSORS, right_pos);
        } else if (left == PAPER && right == SCISSORS) {
            set_battle(SCISSORS, left_pos);
        } else if (left == PAPER && right == ROCK) {
            set_battle(PAPER, right_pos);
        } else if (left == ROCK && right == PAPER) {
            set_battle(PAPER, left_pos);
        } else {
            // NO UPDATES
            assert(true);
        }
    }

    static void battle_top_down(rc_t const top_pos) {
        rc_t const bottom_pos = top_pos.down();
        life_form_t const top = at_battle(top_pos);
        life_form_t const bottom = at_battle(bottom_pos);
        if (top == ROCK && bottom == SCISSORS) {
            set_battle(ROCK, bottom_pos);
        } else if (top == SCISSORS && bottom == ROCK) {
            set_battle(ROCK, top_pos);
        } else if (top == SCISSORS && bottom == PAPER) {
            set_battle(SCISSORS, bottom_pos);
        } else if (top == PAPER && bottom == SCISSORS) {
            set_battle(SCISSORS, top_pos);
        } else if (top == PAPER && bottom == ROCK) {
            set_battle(PAPER, bottom_pos);
        } else if (top == ROCK && bottom == PAPER) {
            set_battle(PAPER, top_pos);
        } else {
            // NO UPDATES
            assert(true);
        }
    }
}

static void generate_updates() {
    size_t const last_row = height - 1uL, last_column = width - 1uL;
    // Last row (except the last column)
    for (size_t column = 0uL; column < last_column; ++column) {
        direction_dependent::battle_left_right(rc_t(last_row, column));
    }
    // Last column (except the last row)
    for (size_t row = 0uL; row < last_row; ++row) {
        direction_dependent::battle_top_down(rc_t(row, last_column));
    }
    // General (except the last row and column and the bottom-right cell)
    for (size_t row = 0uL; row < last_row; ++row) {
        for (size_t column = 0uL; column < last_column; ++column) {
            rc_t const coords(row, column);
            direction_dependent::battle_left_right(coords);
            direction_dependent::battle_top_down(coords);
        }
    }
}

static void process_updates() {
    for (auto const &[coords, new_life] : transformations) {
        at_battle(coords) = new_life;
    }
}

int main() {
    size_t n_cases;
    std::cin >> n_cases;
    while (n_cases--) {
        size_t n_iterations;
        std::cin >> height >> width >> n_iterations;
        std::cin.ignore(); // ignore \n
        if (height == 0uL || width == 0uL) {
            std::cout << '\n';
            continue;
        }
        initialize();
        for (size_t row = 0uL; row < height; ++row) {
            feed_row(row);
        }
        while (n_iterations--) {
            generate_updates();
            process_updates();
        }
        print_battleground();
        if (n_cases) {
            // Print a newline for each test case except the last test case.
            std::cout << '\n';
        }
    }
    return 0;
}

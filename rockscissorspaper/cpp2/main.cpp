#define NDEBUG
#include <iostream>
#include <cassert>
#include <vector>
#include <stack>

namespace internal {
    struct rc_t {
        ssize_t row, column;

        rc_t(ssize_t row, ssize_t column) : row(row), column(column) {}
    };

    class board_t : public std::vector<std::string> {
    public:
        [[nodiscard]] ssize_t height() const {
            return size();
        }

        [[nodiscard]] ssize_t width() const {
            return (*this)[0].size();
        }

        void println() const {
            for (auto const &row : *this) {
                std::cout << row << '\n';
            }
        }
    };

    class challenges_t : public std::stack<std::pair<rc_t, char>> {
    };

    namespace search {
        enum : char {
            ROCK = 'R',
            SCISSORS = 'S',
            PAPER = 'P'
        };

        [[nodiscard]] static char dominate(char challenged, char challenger) {
            assert(challenger == ROCK || challenger == SCISSORS || challenger == PAPER);
            assert(challenged == ROCK || challenged == SCISSORS || challenged == PAPER);
            if (challenger == ROCK && challenged == SCISSORS) {
                return ROCK;
            }
            if (challenger == SCISSORS && challenged == PAPER) {
                return SCISSORS;
            }
            if (challenger == PAPER && challenged == ROCK) {
                return PAPER;
            }
            return challenged;
        }

        // If the one on the left is challenged, then register for a replacement.
        // (Draw left arrows, and go right each step).
        static void go_row(ssize_t const row, std::string const &line, challenges_t &challenges) {
            ssize_t last = line.size() - 1L;
            for (ssize_t i = 0L; i < last; ++i) {
                char const left = line[i];
                char const right = line[i + 1L];
                if (left != right) {
                    char const left_prime = dominate(left, right);
                    if (left != left_prime) {
                        challenges.emplace(rc_t(row, i), left_prime);
                        // because arrows don't run both ways.
                        continue;
                    }
                    char const right_prime = dominate(right, left);
                    if (right != right_prime) {
                        challenges.emplace(rc_t(row, i + 1L), right_prime);
                    }
                }
            }
        }

        // Challenge above; go below
        static void go_column(ssize_t const column, board_t const &board, challenges_t &challenges) {
            ssize_t last_row = board.size() - 1L;
            for (ssize_t i = 0L; i < last_row; ++i) {
                char const above = board[i][column];
                char const below = board[i + 1L][column];
                if (above != below) {
                    char const above_prime = dominate(above, below);
                    if (above != above_prime) {
                        challenges.emplace(rc_t(i, column), above_prime);
                        // because arrows don't run both ways.
                        continue;
                    }
                    char const below_prime = dominate(below, above);
                    if (below != below_prime) {
                        challenges.emplace(rc_t(i + 1L, column), below_prime);
                    }
                }
            }
        }

        [[nodiscard]] static challenges_t go(board_t const &board) {
            challenges_t cs;
            for (ssize_t r = 0L; r < board.height(); ++r) {
                auto const &row = board[r];
                go_row(r, row, cs);
            }
            for (ssize_t c = 0L; c < board.width(); ++c) {
                go_column(c, board, cs);
            }
            return cs;
        }
    }

    namespace update {
        static void go(board_t &board, challenges_t &challenges) {
            size_t n = challenges.size();
            while (n--) {
                auto const &[rc, c] = challenges.top();
                board[rc.row][rc.column] = c;
                challenges.pop();
            }
        }
    }

    static void test_case() {
        board_t board;
        ssize_t height_expected, width_expected, n_iterations;
        std::cin >> height_expected >> width_expected >> n_iterations;
        std::cin.ignore(); // ignore \n
        board.reserve(height_expected);
        while (height_expected--) {
            std::string line;
            std::getline(std::cin, line);
            board.emplace_back(line);
        }

        while (n_iterations--) {
            challenges_t challenges = search::go(board);
            update::go(board, challenges);
        }
        board.println();
    }
}

int main() {
    size_t n_test_cases;
    std::cin >> n_test_cases;
    while (n_test_cases--) {
        internal::test_case();
        if (n_test_cases) {
            std::cout << '\n';
        }
    }
    return 0;
}

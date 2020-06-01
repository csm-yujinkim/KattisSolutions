#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

enum kind_e {
    KIND_KING = 5,
    KIND_QUEEN = 4,
    KIND_ROOK = 3,
    KIND_BISHOP = 2,
    KIND_KNIGHT = 1,
    KIND_PAWN = 0
};

enum color_e {
    COLOR_WHITE,
    COLOR_BLACK
};

static bool get_kind(char c, kind_e &kind, color_e &color) {
    switch (c) {
        case 'K':
            color = COLOR_WHITE;
            kind = KIND_KING;
            return true;
        case 'Q':
            color = COLOR_WHITE;
            kind = KIND_QUEEN;
            return true;
        case 'R':
            color = COLOR_WHITE;
            kind = KIND_ROOK;
            return true;
        case 'B':
            color = COLOR_WHITE;
            kind = KIND_BISHOP;
            return true;
        case 'N':
            color = COLOR_WHITE;
            kind = KIND_KNIGHT;
            return true;
        case 'P':
            color = COLOR_WHITE;
            kind = KIND_PAWN;
            return true;
        case 'k':
            color = COLOR_BLACK;
            kind = KIND_KING;
            return true;
        case 'q':
            color = COLOR_BLACK;
            kind = KIND_QUEEN;
            return true;
        case 'r':
            color = COLOR_BLACK;
            kind = KIND_ROOK;
            return true;
        case 'b':
            color = COLOR_BLACK;
            kind = KIND_BISHOP;
            return true;
        case 'n':
            color = COLOR_BLACK;
            kind = KIND_KNIGHT;
            return true;
        case 'p':
            color = COLOR_BLACK;
            kind = KIND_PAWN;
            return true;
        default:
            return false;
    }
}

struct chess_record_t {
    kind_e kind;
    char row;
    char column;
    std::string str_for_comparison;
    std::string str_for_print;

    chess_record_t(kind_e kind, char row, char column, color_e color)
            : kind(kind), row(row), column(column) {
        int const nine_plus_oh = '9' + '0';
        char const alternative_row = static_cast<char> (nine_plus_oh - static_cast<int>(row));
        std::stringstream build_comparison, build_print;
        build_comparison << static_cast<int>(kind)
                         << (color == COLOR_BLACK ? alternative_row : row)
                         << static_cast<char>('h' - column);
        build_print << (kind == KIND_PAWN ? "" : print_kind(kind))
                    << column
                    << alternative_row;
        str_for_comparison = build_comparison.str();
        str_for_print = build_print.str();
    }

    [[nodiscard]] bool operator<(chess_record_t const &other) const {
        return this->str_for_comparison < other.str_for_comparison;
    }

    [[nodiscard]] std::string const &print() const {
        return str_for_print;
    }

private:
    [[nodiscard]] static const char *print_kind(kind_e k) {
        switch (k) {
            case KIND_KING:
                return "K";
            case KIND_QUEEN:
                return "Q";
            case KIND_ROOK:
                return "R";
            case KIND_BISHOP:
                return "B";
            case KIND_KNIGHT:
                return "N";
            case KIND_PAWN:
                return "";
        }
    }
};

typedef std::vector<std::string> board_t;

struct chess_summary_t {
    std::vector<chess_record_t> black, white;

    explicit chess_summary_t(board_t const &board) {
        for (size_t column = 'h'; column >= 'a'; --column) {
            for (size_t row = '1'; row <= '8'; ++row) {
                int i_row = index_row(static_cast<char>(row));
                int i_col = index_col(static_cast<char>(column));
                char c = board[i_row][i_col];
                color_e color;
                kind_e kind;
                if (get_kind(c, kind, color)) {
                    switch (color) {
                        case COLOR_BLACK:
                            black.emplace_back(kind, row, column, COLOR_BLACK);
                            break;
                        case COLOR_WHITE:
                            white.emplace_back(kind, row, column, COLOR_WHITE);
                            break;
                    }
                }
            }
        }
    }

    void print_black() const {
        print_internal(COLOR_BLACK);
    }

    void print_white() const {
        print_internal(COLOR_WHITE);
    }

private:
    [[nodiscard]] static int index_row(char row) {
        return (row - '1') * 2 + 1;
    }

    [[nodiscard]] static int index_col(char column) {
        return (column - 'a') * 4 + 2;
    }

    void print_internal(color_e color) const {
        std::vector<chess_record_t> rows;
        switch (color) {
            case COLOR_BLACK:
                std::cout << "Black: ";
                rows = black;
                break;
            case COLOR_WHITE:
                std::cout << "White: ";
                rows = white;
                break;
        }
        if (!rows.empty()) {
            std::sort(rows.rbegin(), rows.rend());
            std::vector<std::string> representations(rows.size());
            for (size_t i = 0; i < rows.size(); ++i) {
                representations[i] = rows[i].print();
            }
            for (size_t i = 0; i < rows.size() - 1; ++i) {
                std::cout << representations[i] << ',';
            }
            std::cout << representations[rows.size() - 1];
        }
        std::cout << '\n';
    }
};

int main() {
    board_t board;
    board.reserve(17);
    for (size_t i = 0; i < 17; ++i) {
        std::string line;
        getline(std::cin, line);
        board.push_back(line);
    }
    chess_summary_t summary(board);
    summary.print_white();
    summary.print_black();
    return 0;
}

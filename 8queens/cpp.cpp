#include <cstdio>

enum board_t {
    QU,         // queen
    NQ          // not queen
};

struct coord_t {
    int r;
    int c;
};

inline bool valid_coord(struct coord_t const &c) {
    return
        c.r >= 0 &&
        c.r < 8 &&
        c.c >= 0 &&
        c.c < 8;
}

// modes
//  0: up left
//  1: up right
//  2: down right
//  3: down left
//  other values: invalid
inline void advance(int mode, struct coord_t &to, struct coord_t const &from) {
    switch (mode)
    {
    case 0:
        to.r = from.r - 1;
        to.c = from.c - 1;
        break;
    
    case 1:
        to.r = from.r - 1;
        to.c = from.c + 1;
        break;
    
    case 2:
        to.r = from.r + 1;
        to.c = from.c + 1;
        break;
    
    case 3:
        to.r = from.r + 1;
        to.c = from.c - 1;
        break;
    
    default:
        break;
    }
}

inline void invalid() {
    fputs_unlocked("invalid", stdout);
}

inline void valid() {
    fputs_unlocked("valid", stdout);
}

inline void get_row(char *row) {
    fgets_unlocked(row, 9, stdin);
    getc_unlocked(stdin); // discard \n
}

int main() {
    board_t board[8][8];
    struct coord_t queens[8];
    size_t queens_top = 0;

    for (size_t r = 0; r < 8; ++r) {
        char row[9];
        get_row(row);
        for (size_t c = 0; c < 8; ++c) {
            if (row[c] == '*') {
                board[r][c] = QU;
                queens[queens_top].r = r;
                queens[queens_top].c = c;
                ++queens_top;
            }
            else {
                board[r][c] = NQ;
            }
        }
    }

    // Are there exactly eight queens?
    if (queens_top != 8) {
        invalid();
        return 0;
    }

    // Solve rook problem
    for (size_t r = 0; r < 8; ++r) {
        bool queen_found = false;
        for (size_t c = 0; c < 8; ++c) {
            if (board[r][c] == QU) {
                if (queen_found) {
                    invalid();
                    return 0;
                }
                queen_found = true;
            }
        }
    }
    for (size_t c = 0; c < 8; ++c) {
        bool queen_found = false;
        for (size_t r = 0; r < 8; ++r) {
            if (board[r][c] == QU) {
                if (queen_found) {
                    invalid();
                    return 0;
                }
                queen_found = true;
            }
        }
    }

    // Solve diagonal problem
    for (size_t i_queen = 0; i_queen < 8; ++i_queen) {
        struct coord_t new_adv = queens[i_queen];
        for (int mode = 0; mode < 4; ) {
            advance(mode, new_adv, new_adv);
            if (valid_coord(new_adv)) {
                if (board[new_adv.r][new_adv.c] == QU) {
                    invalid();
                    return 0;
                }
            }
            else {
                ++mode;
                break;
            }
        }
    }

    // If cannot find problem, then valid.
    valid();
    return 0;
}

#include <cstdio>
#include <cstring>

#define QU '*'

struct coord_t {
    int r;
    int c;

	inline bool operator== (coord_t const &other) {
		return this->r == other.r && this->c == other.c;
	}
};

inline void invalid() {
    puts("invalid");
}

inline void valid() {
    puts("valid");
}

int main() {
	coord_t queens[8];
	size_t c_queens = 0;	// count of detected queens

    // Input rows
    for (size_t r = 0; r < 8; ++r) {
		// includes 8-sequence of '*'|'.' and then \0.
		char line[9];
		fgets(line, 9, stdin);
		getchar();	// consume \n

		// detect the queen(s) in each row
		// say invalid if more than one queen found
		bool queen_found = false;
		for (size_t c = 0; c < 8; ++c) {
			if (line[c] == QU) {
				if (queen_found) {
					invalid();
					return 0;
				}
				queen_found = true;
				queens[c_queens].r = r;
				queens[c_queens].c = c;
				++c_queens;
			}
		}
    }

	// There must be exactly 8 queens.
	if (c_queens != 8) {
		invalid();
		return 0;
	}

	// Detect whether there are more than one queen in any column.
	bool column_queen_found[8] = {0};   // true if a queen found in column c; false otherwise.
	for (size_t q = 0; q < c_queens; ++q) {
		if (column_queen_found[queens[q].c]) {
			invalid();
			return 0;
		}
		else {
			column_queen_found[queens[q].c] = true;
		}
	}

	// Detect whether there are queens in the diagonal lines from any queen.
	for (size_t q = 0; q < c_queens; ++q) {
		for (size_t dir = 0; dir < 4; ++dir) {
			for (size_t mag = 1; ; ++mag) {
				coord_t adv = queens[q];
				switch (dir) {
				case 0:
					adv.r -= mag;
					adv.c -= mag;
					if (adv.r < 0 || adv.c < 0) {
						goto when_invalid;
					}
					break;
				case 1:
					adv.r -= mag;
					adv.c += mag;
					if (adv.r < 0 || adv.c >= 8) {
						goto when_invalid;
					}
					break;
				case 2:
					adv.r += mag;
					adv.c += mag;
					if (adv.r >= 8 || adv.c >= 8) {
						goto when_invalid;
					}
					break;
				case 3:
					adv.r += mag;
					adv.c -= mag;
					if (adv.r >= 8 || adv.c < 0) {
						goto when_invalid;
					}
					break;
				}
				for (size_t oq = 0; oq < c_queens; ++oq) {
					if (queens[oq] == adv) {
						invalid();
						return 0;
					}
				}
				continue;
				when_invalid:
					break;
			}
		}
	}

	// All conditions meet.
	valid();
	return 0;
}

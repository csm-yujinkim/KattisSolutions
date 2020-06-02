// uncomment below for submission.
// macro NDEBUG indicates that assert() statements be ignored
// <cassert> may or may not have been included
#define NDEBUG

#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <algorithm>

namespace program {
    namespace common {
        size_t const HEIGHT = 17;
        std::array<std::string, HEIGHT> table;

        static void make_table() {
            size_t j = 0;
            for (size_t i = 0; i < 4; ++i) {
                // send copies
                table[j++] = std::string("+---+---+---+---+---+---+---+---+");
                table[j++] = std::string("|...|:::|...|:::|...|:::|...|:::|");
                table[j++] = std::string("+---+---+---+---+---+---+---+---+");
                table[j++] = std::string("|:::|...|:::|...|:::|...|:::|...|");
            }
            table[j] = std::string("+---+---+---+---+---+---+---+---+");
        }

        static void show_table() {
            for (auto const &line : table) {
                std::cout << line << '\n';
            }
        }

        static void read_cin_comma_separate(std::vector<std::string> &out) {
            // unlike the F# code, this one does not seek to
            // reverse the string itself
            std::cin.ignore(7); // Ignore initial "White: " or "Black: " tag
            std::string token;
            std::getline(std::cin, token);
            std::istringstream line(token);
            while (std::getline(line, token, ',') && !token.empty()) {
                out.emplace_back(token);
            }
        }
    }
    namespace color_dependent {
        enum color_e {
            COLOR_WHITE,
            COLOR_BLACK
        };

        static int get_row(char row) {
            int const number_1 = static_cast<int> ('1');
            int const coded = (static_cast<int> (row) - number_1);
            int const inverted = coded * 2 + 1;
            return 16 - inverted; // 16 is the last index for the row
        }

        static int get_column(char height) {
            int const char_a = static_cast<int> ('a');
            int const coded = (static_cast<int> (height) - char_a);
            return coded * 4 + 2;
        }

        static void populate_table(color_e color) {
            std::vector<std::string> tokens;
            common::read_cin_comma_separate(tokens);
            for (std::string const &token : tokens) {
                size_t const length = token.size();
                int row, column;
                char kind;
                switch (length) {
                    case 2:
                        kind = (color == COLOR_WHITE ? 'P' : 'p');
                        column = get_column(token[0]);
                        row = get_row(token[1]);
                        break;
                    case 3:
                        kind = (color == COLOR_WHITE ?
                                token[0] : static_cast<char> (tolower(token[0])));
                        column = get_column(token[1]);
                        row = get_row(token[2]);
                        break;
                    default:
                        throw std::exception();
                }
                common::table[row][column] = kind;
            }
        }
    }

    int real_main() {
        common::make_table();
        color_dependent::populate_table(color_dependent::COLOR_WHITE);
        color_dependent::populate_table(color_dependent::COLOR_BLACK);
        common::show_table();
        return 0;
    }
}

int main() {
    return program::real_main();
}

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

std::string lis(std::string input);


int main() {
    std::string line, input_str;
    std::istringstream sin;

    std::getline(std::cin, line);
    while (line != "") {
        sin.str(line);
        sin.clear();
        std::getline(sin, input_str, ' ');
        std::cout << lis(input_str) << std::endl;
        std::getline(std::cin, line);
    }

    return 0;
}

std::string lis(std::string input) {
    int size = input.length();
    int *length_table = new int[size];
    int *index_table = new int[size];
    std::string ret_val = "";
    int longest_len = 0, longest_idx = -1;

    for (int i = 0; i < size; ++i) {
        char curr_char = input[i];
        int max_len = 1;
        int max_idx = -1;
        for (int j = 0; j < i; ++j) {
            if (curr_char > input[j] && length_table[j] >= max_len) {
                max_len = length_table[j] + 1;
                max_idx = j;
            }
        }
        length_table[i] = max_len;
        index_table[i] = max_idx;

        if (longest_len < max_len) {
            longest_len = max_len;
            longest_idx = i;
        }
    }

    while (longest_idx >= 0) {
        ret_val.push_back(input[longest_idx]);
        longest_idx = index_table[longest_idx];
    }

    std::reverse(ret_val.begin(), ret_val.end());

    delete[] index_table;
    delete[] length_table;

    return ret_val;
}

#include <iostream>
#include <climits>
#include <sstream>
#include <string>
#include <vector>


struct MergeInfo {
    int size;
    int cost;
    int optimum_idx;
};

std::string IntToStr(int num);
int MergeSlides(std::vector<int> input, std::string &sequence);
void FindMergeSequence(MergeInfo **table, std::string &sequence, int begin, int end);

int main() {
    std::string line;
    std::istringstream sin;
    int temp_num;

    std::getline(std::cin, line);
    while (line != "") {
        std::vector<int> input_nums;
        std::string sequence;
        sin.str(line);
        sin.clear();
        while (sin >> temp_num) {
            if (temp_num <= 0) {
                return 0;
            }
            input_nums.push_back(temp_num);
        }
        if (!sin.eof()) {
            return 0;
        }
        std::cout << MergeSlides(input_nums, sequence) << ' ' << sequence << std::endl;
        std::getline(std::cin, line);
    }

    return 0;
}

int MergeSlides(std::vector<int> input, std::string &sequence) {
    int input_length = input.size();
    MergeInfo **table = new MergeInfo*[input_length];
    int ret_val;
    for (int i = 0; i < input_length; ++i) {
        table[i] = new MergeInfo[input_length];
    }

    for (int i = 0; i < input_length; ++i) {
        table[i][i].size = input[i];
        table[i][i].cost = 0;
        table[i][i].optimum_idx = -1;
    }

    for (int num_of_merge = 1; num_of_merge <= input_length - 1; ++num_of_merge) {
        for (int i = 0; i + num_of_merge < input_length; ++i) {

            MergeInfo min_info, curr_info;

            min_info.size = table[i][i + num_of_merge - 1].size + table[i + num_of_merge][i + num_of_merge].size;
            min_info.cost = INT_MAX;
            min_info.optimum_idx = -1;

            for (curr_info.optimum_idx = i; curr_info.optimum_idx < i + num_of_merge; ++curr_info.optimum_idx) {

                curr_info.cost = table[i][curr_info.optimum_idx].cost + table[curr_info.optimum_idx + 1][i + num_of_merge].cost;

                if (curr_info.cost < min_info.cost) {
                    min_info.cost = curr_info.cost;
                    min_info.optimum_idx = curr_info.optimum_idx;
                }
            }
            min_info.cost += min_info.size;

            table[i][i + num_of_merge] = min_info;
        }
    }

    ret_val = table[0][input_length - 1].cost;
    if (input_length > 1) FindMergeSequence(table, sequence, 0, input_length - 1);
    else sequence = "";

    for (int i = 0; i < input_length; ++i) {
        delete[] table[i];
    }
    delete[] table;

    return ret_val;
}

void FindMergeSequence(MergeInfo **table, std::string &sequence, int begin, int end) {
    int idx = table[begin][end].optimum_idx;
    if (idx < 0) {
        sequence.append(IntToStr(table[begin][end].size));
        return;
    }
    sequence.push_back('(');
    FindMergeSequence(table, sequence, begin, idx);
    sequence.push_back(',');
    FindMergeSequence(table, sequence, idx + 1, end);
    sequence.push_back(')');
}

std::string IntToStr(int num) {
    std::ostringstream sout;
    sout << num;
    return sout.str();
}

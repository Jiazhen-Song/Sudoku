#include <fstream>
#include <iostream>
#include <vector>
#include "../src/core.hpp"


int cpp_rand() {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<> dis;
    return dis(gen);
}

int flag = 0;

std::vector<board_t> read_boards(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        throw std::runtime_error("数独文件不存在");
    }

    std::vector<board_t> boards;

    std::string line;
    while (std::getline(fin, line) && !line.empty()) {
        std::stringstream linein(line);

        board_t board;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char v{};
                linein >> v;
                if (!(v >= '1' && v <= '9' || v == '$')) {
                    throw std::runtime_error("数独文件格式错误");
                }
                if (v == '$') {
                    v = '0';
                }
                board[i][j] = v - '0';
            }
        }
        boards.emplace_back(board);
    }

    return boards;
}

void write_boards(const std::string& filename, const std::vector<board_t>& boards) {
    std::ofstream fout(filename);
    for (const board_t& board : boards) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char v = board[i][j] == 0 ? '$' : board[i][j] + '0';
                fout << v;
            }
        }
        fout << std::endl;
    }
}

void print_board(const board_t& board) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            std::cout << "+-------+-------+-------+" << std::endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                std::cout << "| ";
            }
            std::cout << static_cast<char> (board[i][j] == 0 ?
                ' ' : board[i][j] + '0')
                << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+-------+-------+-------+" << std::endl;
}

std::vector<board_t> generate_final_boards(int count) {
    // TODO: 生成数独终盘
    return {};
}

void solve(int i, int j, board_t& res, int solve_num) {
    
}

board_t solve_board(const board_t &board) {
    flag = 0;
    board_t res;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            res[i][j] = board[i][j];
        }
    }
    solve(0, 0, res, 1);
    return res;
}

board_t generate_game_board(int mode, std::pair<int, int> range, bool unique) {
    // TODO: 生成游戏
    return {};
}

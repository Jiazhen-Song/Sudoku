/*
# Copyright (c) 2023 Jiazhen Song, Yuxuan Li. All rights reserved.
*/

#include <iostream>
#include <regex>
#include "./cxxopts.hpp"
#include "./core.hpp"

int main(int argc, char *argv[]) {
    cxxopts::Options options("Sudoku", "Sudoku solver & generator");
    options.add_options()
            ("c,count", "Number of Answer Grid you need (1-1000000)", cxxopts::value<int>())
            ("s,solve", "Path of the Sudoku Grid to be solved", cxxopts::value<std::string>())
            ("n,number", "Number of the Sudoku Grid you need (1-10000)", cxxopts::value<int>())
            ("m,mode", "Difficulty degree of the Sudoku Grid to be generated (1-3)",
             cxxopts::value<int>()->default_value("1"))
            ("r,range", "Range of the blank number of Sudoku Grid to be generated (20~55)",
             cxxopts::value<std::string>()->default_value("20~55"))
            ("u,unique", "Answer to the Sudoku Grid is unique",
             cxxopts::value<bool>()->default_value("false"))
            ("h,help", "Show the help information");
    try {
        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }

        // 判断是否为生成终盘
        if (result.count("count")) {
            // 参数获取 & 校验
            int count = result["count"].as<int>();
            if (!(count >= 1 && count <= 1000000)) {
                std::cout << "Number of Answer Grid should range from 1 to 1000000"
                          << std::endl;
                return 1;
            }

            std::cout << "Generate Answer Grid" << std::endl;
            std::cout << "Number of Answer Grid you need：" << count << std::endl;

            std::vector<board_t> boards = generate_final_boards(count);
            size_t i = 1;
            for (const board_t &board : boards) {
                // 打印终局
                std::cout << "Generate " << i++ << " Answer Grid：" << std::endl;
                print_board(board);
            }
            write_boards("final.txt", boards);
            return 0;
        }
        // 判断是否为求解数独
        if (result.count("solve")) {
            std::string filename = result["solve"].as<std::string>();

            std::cout << "Solve Sudoku Grid" << std::endl;
            std::cout << "Sudoku file：" << filename << std::endl;

            std::vector<board_t> boards = read_boards(filename);
            for (board_t &board : boards) {
                board = solve_board(board);
                std::cout << "Result of Sudoku Grid：" << std::endl;
                print_board(board);
            }
            write_boards("sudoku.txt", boards);
            return 0;
        }

        // 判断是否为生成游戏
        if (result.count("number")) {
            int number = result["number"].as<int>();
            int mode = result["mode"].as<int>();
            std::string range_str = result["range"].as<std::string>();
            bool unique = result["unique"].as<bool>();

            if (!(number >= 1 && number <= 10000)) {
                std::cout << "Number of Sudoku Grid should range from 1 to 10000" << std::endl;
                return 1;
            }
            if (!(mode >= 1 && mode <= 3)) {
                std::cout << "Difficulty degree of Sudoku Grid should range from 1 to 3" << std::endl;
                return 1;
            }
            std::smatch m;
            if (!std::regex_match(range_str, m,
                                  std::regex(R"(^(\d+)~(\d+)$)"))) {
                std::cout << "Format of the range is wrong, which should be 20~55" << std::endl;
                return 1;
            }
            std::pair range = {std::stoi(m[1]), std::stoi(m[2])};
            if (!(range.first >= 20 && range.second <= 55 &&
                  range.first <= range.second)) {
                std::cout << "Range of the blank number of Sudoku Grid should range from 20 to 55" << std::endl;
                return 1;
            }

            std::cout << "Generate Sudoku Grid" << std::endl;
            std::cout << "Number of Sudoku Grid you need：" << number << std::endl;
            std::cout << "Difficulty degree：" << mode << std::endl;
            std::cout << "Range of the blank number：" << range.first << " ~ " << range.second
                      << std::endl;
            std::cout << "Answer is unique：" << (unique ? "Yes" : "No") << std::endl;

            std::vector<board_t> boards =
                    generate_game_boards(number, mode, range, unique);
            size_t i = 1;
            for (const board_t &board : boards) {
                // 打印游戏
                std::cout << "Generate " << i++ << " Sudoku Grid：" << std::endl;
                print_board(board);
            }
            write_boards("game.txt", boards);
            return 0;
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    std::cout << "Format of arguments is illegal" << std::endl;
    return 1;
}

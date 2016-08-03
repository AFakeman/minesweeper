//
//  mineui.cpp
//  minesweeper
//
//  Created by Anton Suslov on 02/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#include "mineui.hpp"

bool UI::run() {
    while(true) {
        print();
        std::string command;
        std::vector<std::string> tok_com;
        getline(std::cin, command);
        std::stringstream strstream(command);
        std::string token = "";
        while (getline(strstream, token, ' ')) {
            tok_com.push_back(token);
        }
        if(tok_com.empty()) {
            continue;
        }
        if (tok_com[0] == "click") {
            size_t x = std::stoi(tok_com[1]);
            size_t y = std::stoi(tok_com[2]);
            int code = engine->click(Game::a_open, x, y);
            if(code == 1) {
                print_lose();
                return false;
            }
            if(code == 2) {
                std::cout << "You won!" << std::endl;
                return true;
            }
        } else if (tok_com[0] == "quest") {
            size_t x = std::stoi(tok_com[1]);
            size_t y = std::stoi(tok_com[2]);
            engine->click(Game::a_question, x, y);
        } else if (tok_com[0] == "flag") {
            size_t x = std::stoi(tok_com[1]);
            size_t y = std::stoi(tok_com[2]);
            engine->click(Game::a_flag, x, y);
        } else if (tok_com[0] == "bombs") {
            print_mines();
        } else if (tok_com[0] == "quit") {
            std::cout << "Bye!" << std::endl;
            return false;
        } else {
            std::cout << "Unknown command: " << tok_com[0] << std::endl;
        }
    }
}

void UI::print() const {
    auto mask = engine->get_mask();
    auto numbers = engine->get_numbers();
    auto size_x = engine->get_size_x();
    auto size_y = engine->get_size_y();
    std::vector<std::vector<char>> result;
    for(size_t y = 0; y < size_y; y++) {
        for(size_t x = 0; x < size_x; x++) {
            if(mask[x][y] == ' ') {
                std::cout << numbers[x][y] << ' ';
            } else {
                std::cout << mask[x][y] << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void UI::print_mines() const {
    for(auto y : engine->get_bombs()) {
        for(auto cell : y) {
            std::cout << (cell ? 1 : 0) << " ";
        }
        std::cout << std::endl;
    }
}

void UI::print_lose() const {
    auto mask = engine->get_mask();
    auto numbers = engine->get_numbers();
    auto bombs = engine->get_bombs();
    auto size_x = engine->get_size_x();
    auto size_y = engine->get_size_y();
    for(size_t y = 0; y < size_y; y++) {
        for(size_t x = 0; x < size_x; x++) {
            if(mask[x][y] == ' ') {
                std::cout << numbers[x][y] << ' ';
            } else {
                if(bombs[x][y]) {
                    std::cout << '*' << ' ';
                } else {
                    std::cout << mask[x][y] << ' ';
                }
            }
        }
        std::cout << std::endl;
    }
}
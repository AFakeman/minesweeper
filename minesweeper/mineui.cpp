//
//  mineui.cpp
//  minesweeper
//
//  Created by Anton Suslov on 02/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#include "mineui.hpp"

void UI::run() {
    CommandManager kek;
    kek.AddCommand("click", std::function<bool(const std::vector<std::string>&)>([this](const std::vector<std::string> &tok_com){
        size_t x = std::stoi(tok_com[1]);
        size_t y = std::stoi(tok_com[2]);
        int code = engine->click(Game::a_open, x, y);
        if(code == 1) {
            print_lose();
            status = 1;
            return true;
        }
        if(code == 2) {
            std::cout << "You won!" << std::endl;
            status = 2;
            return true;
        }
        return false;
    }));
    kek.AddCommand("quest", std::function<bool(const std::vector<std::string>&)>([this](const std::vector<std::string> &tok_com){
        size_t x = std::stoi(tok_com[1]);
        size_t y = std::stoi(tok_com[2]);
        engine->click(Game::a_question, x, y);
        return false;
    }));
    kek.AddCommand("flag", std::function<bool(const std::vector<std::string>&)>([this](const std::vector<std::string> &tok_com){
        size_t x = std::stoi(tok_com[1]);
        size_t y = std::stoi(tok_com[2]);
        engine->click(Game::a_flag, x, y);
        return false;
    }));
    kek.AddCommand("bombs", std::function<bool(const std::vector<std::string>&)>([this](const std::vector<std::string> &tok_com){
        print_mines();
        return false;
    }));
    kek.AddCommand("quit", std::function<bool(const std::vector<std::string>&)>([this](const std::vector<std::string> &tok_com){
        std::cout << "Bye!" << std::endl;
        return true;
    }));
    kek.SetPrompt(std::function<void()>([this](){
        print();
    }));
    status = 0;
    kek.Loop();
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
//
//  minesweeper.cpp
//  minesweeper
//
//  Created by Anton Suslov on 02/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#include "minesweeper.hpp"

void Game::generate(size_t x_, size_t y_) {
    for(size_t bomb = 0; bomb < difficulty; bomb++) {
        size_t xcoord = x_;
        size_t ycoord = y_;
        while(xcoord == x_ && ycoord == y_) {
            xcoord = rand() % size_x;
            ycoord = rand() % size_y;
        }
        bombs[xcoord][ycoord] = true;
    }
    generate_numbers();
}

void Game::recursive_open(size_t x_, size_t y_) {
    if(mask[x_][y_] == ' ') {
        return;
    }
    mask[x_][y_] = ' ';
    if(numbers[x_][y_] != 0) {
        return;
    }
    cycle_cells(x_, y_, [this](size_t x_, size_t y_){
        recursive_open(x_, y_);
    });
    return;
}

void Game::generate_numbers() {
    for(size_t x = 0; x < size_x; x++) {
        for(size_t y = 0; y < size_y; y++) {
            if(bombs[x][y]) {
                cycle_cells(x, y, [this, x ,y](size_t x_, size_t y_){
                    numbers[x_][y_]++;
                });
            }
        }
    }
}

bool Game::did_win() {
    for(size_t x = 0; x < size_x; x++) {
        for(size_t y = 0; y < size_y; y++) {
            if((mask[x][y] != ' ') && (!bombs[x][y])) {
                return false;
            }
        }
    }
    return true;
}

Game::Game(size_t x_, size_t y_, size_t diff_) {
    srand((unsigned)time(NULL));
    size_x = x_;
    size_y = y_;
    started = false;
    difficulty = diff_;
    for(size_t x = 0; x < x_; x++) {
        bombs.push_back(std::vector<bool>());
        for(size_t y = 0; y < y_; y++) {
            bombs[x].push_back(false);
        }
    }
    for(size_t x = 0; x < x_; x++) {
        mask.push_back(std::vector<char>());
        for(size_t y = 0; y < y_; y++) {
            mask[x].push_back('#');
        }
    }
    for(size_t x = 0; x < x_; x++) {
        numbers.push_back(std::vector<size_t>());
        for(size_t y = 0; y < y_; y++) {
            numbers[x].push_back(0);
        }
    }
}

int Game::click(action act_, size_t x_, size_t y_) {
    if(mask[x_][y_] == ' ') {
        return 0;
    }
    switch(act_) {
        case a_open:
            if (!started) {
                started = true;
                generate(x_, y_);
                return click(act_, x_, y_);
            } else {
                if(bombs[x_][y_]) {
                    return 1;
                } else {
                    recursive_open(x_, y_);
                    if(did_win()) {
                        return 2;
                    } else {
                        return 0;
                    }
                }
            }
            break;
        case a_flag:
            if(mask[x_][y_] == 'f') {
                mask[x_][y_] = '#';
            } else {
                mask[x_][y_] = 'f';
            }
            return 0;
        case a_question:
            if(mask[x_][y_] == '?') {
                mask[x_][y_] = '#';
            } else {
                mask[x_][y_] = '?';
            }
            return 0;
    }
}

const Game::field_t &Game::get_bombs() const {
    return bombs;
}

const Game::numbers_t &Game::get_numbers() const {
    return numbers;
}

const Game::mask_t &Game::get_mask() const {
    return mask;
}
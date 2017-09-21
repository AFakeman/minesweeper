//
//  minesweeper.cpp
//  minesweeper
//
//  Created by Anton Suslov on 02/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#include "minesweeper.hpp"

void Game::reset_table() {
    for(size_t x = 0; x < size_x; x++) {
        for(size_t y = 0; y < size_y; y++) {
            numbers[x][y] = 0;
            bombs[x][y] = false;
            mask[x][y] = '#';
        }
    }
}

void Game::generate(size_t x_, size_t y_) {
    numbers[x_][y_] = 1;
    while(numbers[x_][y_] != 0) {
        reset_table();
        for(u_long bomb = 0; bomb < difficulty; bomb++) {
            auto xcoord = x_;
            auto ycoord = y_;
            while((xcoord == x_ && ycoord == y_) || bombs[xcoord][ycoord]) {
                xcoord = rand() % size_x;
                ycoord = rand() % size_y;
            }
            bombs[xcoord][ycoord] = true;
        }
        generate_numbers();
    }
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

Game::Game(size_t x_, size_t y_, size_t diff_)
      : bombs(x_, std::vector<bool>(y_, false)),
        mask(x_, std::vector<char>(y_, '#')),
        numbers(x_, std::vector<size_t>(y_, 0)),
        size_x(x_),
        size_y(y_),
        started(false),
        difficulty(diff_) {}

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

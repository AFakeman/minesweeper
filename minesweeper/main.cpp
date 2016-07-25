//
//  main.cpp
//  minesweeper
//
//  Created by Anton Suslov on 24/07/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

class Game {
    size_t size_x;
    size_t size_y;
    typedef std::vector<std::vector<bool>> field_t;
    field_t bombs;
    typedef std::vector<std::vector<char>> mask_t;
    mask_t mask;
    typedef std::vector<std::vector<size_t>> numbers_t;
    numbers_t numbers;
    bool started;
    size_t difficulty;
    void generate(size_t x_, size_t y_) {
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
    void recursive_open(size_t x_, size_t y_) {
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
    void generate_numbers() {
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
    template<class Function>
    void cycle_cells(size_t x_, size_t y_, Function f) {
        size_t x_lower = (x_ == 0) ? x_ : x_ - 1;
        size_t x_upper = (x_ == (size_x - 1)) ? x_ : x_+1;
        size_t y_lower = (y_ == 0) ? y_ : y_ -1;
        size_t y_upper = (y_ == (size_y - 1)) ? y_ : y_+1;
        size_t x = x_lower;
        size_t y = y_lower;
        do {
            f(x,y);
            if(y == y_upper) {
                x++;
                y = y_lower;
            } else {
                y++;
            }
        } while (x != x_upper || y != y_upper);
        f(x,y);
    }
    bool did_win() {
        for(size_t x = 0; x < size_x; x++) {
            for(size_t y = 0; y < size_y; y++) {
                if((mask[x][y] != ' ') && (!bombs[x][y])) {
                    return false;
                }
            }
        }
        return true;
    }
public:
    enum action {
        a_open,
        a_flag,
        a_question
    };
    Game(size_t x_, size_t y_, size_t diff_) {
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
    void print_mines() {
        for(auto y : bombs) {
            for(auto cell : y) {
                std::cout << (cell ? 1 : 0) << " ";
            }
            std::cout << std::endl;
        }
    }
    void print_numbers() {
        for(auto y : numbers) {
            for(auto cell : y) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }
    void print() {
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
    void print_lose() {
        for(size_t y = 0; y < size_y; y++) {
            for(size_t x = 0; x < size_y; x++) {
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
    int click(action act_, size_t x_, size_t y_) {
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
    
    void test(size_t x, size_t y) {
        cycle_cells(x, y, [](size_t x_, size_t y_){
            std::cout << x_ << " " << y_ << std::endl;
        });
    }
};

int main(int argc, const char * argv[]) {
    Game kek(10,10,10);
    kek.print();
    while(true) {
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
            int code = kek.click(Game::a_open, x, y);
            if(code == 1) {
                kek.print_lose();
                break;
            }
            if(code == 2) {
                std::cout << "You won!" << std::endl;
                break;
            }
        } else if (tok_com[0] == "quest") {
            size_t x = std::stoi(tok_com[1]);
            size_t y = std::stoi(tok_com[2]);
            kek.click(Game::a_question, x, y);
        } else if (tok_com[0] == "flag") {
            size_t x = std::stoi(tok_com[1]);
            size_t y = std::stoi(tok_com[2]);
            kek.click(Game::a_flag, x, y);
        } else if (tok_com[0] == "bombs") {
            kek.print_mines();
        } else if (tok_com[0] == "quit") {
            std::cout << "Bye!" << std::endl;
            break;
        } else {
            std::cout << "Unknown command: " << tok_com[0] << std::endl;
        }
        kek.print();
    }

    return 0;
}

//
//  minesweeper.hpp
//  minesweeper
//
//  Created by Anton Suslov on 02/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#ifndef minesweeper_hpp
#define minesweeper_hpp

#include <iostream>
#include <vector>

class Game {
    typedef std::vector<std::vector<bool>> field_t;
    typedef std::vector<std::vector<char>> mask_t;
    typedef std::vector<std::vector<size_t>> numbers_t;
    size_t size_x;
    size_t size_y;
    field_t bombs;
    mask_t mask;
    numbers_t numbers;
    bool started;
    u_long difficulty;
    void generate(size_t x_, size_t y_);
    void recursive_open(size_t x_, size_t y_);
    void generate_numbers();
    void reset_table();
    bool did_win();
public:
    enum action {
        a_open,
        a_flag,
        a_question
    };
    Game(size_t x_, size_t y_, size_t diff_);
    size_t get_size_x() const {
        return size_x;
    }
    size_t get_size_y() const {
        return size_y;
    }
    size_t get_difficulty() const {
        return difficulty;
    }
    int click(action act_, size_t x_, size_t y_);
    const mask_t &get_mask() const;
    const field_t &get_bombs() const;
    const numbers_t &get_numbers() const;
    void test(size_t x, size_t y) {
        cycle_cells(x, y, [](size_t x_, size_t y_){
            std::cout << x_ << " " << y_ << std::endl;
        });
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
};



#endif /* minesweeper_hpp */

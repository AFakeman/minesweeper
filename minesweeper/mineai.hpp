//
//  mineai.hpp
//  minesweeper
//
//  Created by Anton Suslov on 03/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#ifndef mineai_hpp
#define mineai_hpp

#include "minesweeper.hpp"
#include <vector>

class AI {
    Game *engine;
    void print() const;
    void print_mines() const;
    void print_lose() const;
    auto get_field() const;
    std::ostream *ostr;
    bool verbose;
public:
    AI(Game *eng_, bool verb_, std::ostream *ostr_) {
        engine = eng_;
        verbose = verb_;
        ostr = ostr_;
    }
    AI() = delete;
    bool run();
};
#endif /* mineai_hpp */

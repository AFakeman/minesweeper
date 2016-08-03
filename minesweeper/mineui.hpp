//
//  mineui.hpp
//  minesweeper
//
//  Created by Anton Suslov on 02/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#ifndef mineui_hpp
#define mineui_hpp

#include "minesweeper.hpp"
class UI {
    Game *engine;
    void print() const;
    void print_mines() const;
    void print_lose() const;
public:
    UI(Game *eng_) {
        engine = eng_;
    }
    UI() = delete;
    void run();
};
#endif /* mineui_hpp */

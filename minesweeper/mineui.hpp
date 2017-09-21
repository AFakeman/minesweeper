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
#include <sstream>
#include "manager.hpp"

class UI {
 public:
  UI(Game *eng_)
    : engine(eng_),
      status(-1) {}
  
  void run();

 private:
  Game *engine;
  int status;
  void print() const;
  void print_mines() const;
  void print_lose() const;
};
#endif /* mineui_hpp */

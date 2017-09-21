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
 public:
  AI(Game *eng_, bool verb_, std::ostream *ostr_);
  bool run();
  
 private:
  void print() const;
  void print_mines() const;
  void print_lose() const;
  auto get_field() const;
  
  Game *engine;
  std::ostream *ostr;
  bool verbose;
};
#endif /* mineai_hpp */

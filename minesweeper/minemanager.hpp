//
//  minemanager.hpp
//  minesweeper
//
//  Created by Anton Suslov on 03/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#ifndef minemanager_hpp
#define minemanager_hpp
#include "mineai.hpp"
#include "minesweeper.hpp"

class Manager {
  size_t size_x;
  size_t size_y;
  u_long diff;
  u_long tries;
public:
  Manager();
  Manager(size_t height, size_t width, u_long diff, u_long tries);
  void run();
};
#endif /* minemanager_hpp */

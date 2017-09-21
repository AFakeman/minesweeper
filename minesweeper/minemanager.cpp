//
//  minemanager.cpp
//  minesweeper
//
//  Created by Anton Suslov on 03/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#include "minemanager.hpp"

Manager::Manager() {
  size_x = 10;
  size_y = 10;
  diff = 10;
  tries = 1000000;
}

Manager::Manager(size_t width, size_t height, u_long diff_, u_long tries_)
  : size_x(width),
    size_y(height),
    diff(diff_),
    tries(tries_) {}

void Manager::run() {
  u_long wins = 0;
  u_long losses = 0;
  for(u_long i = 0; i < tries; i++) {
    Game game(size_x, size_y, diff);
    AI ai(&game, false, &(std::cout));
    if(ai.run()) {
      wins++;
    } else {
      losses++;
    }
    std::cout << std::endl;
  }
  std::cout << wins << " " << losses << std::endl;
}

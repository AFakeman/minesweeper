//
//  mineai.cpp
//  minesweeper
//
//  Created by Anton Suslov on 03/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#include "mineai.hpp"

AI::AI(Game *eng_, bool verb_, std::ostream *ostr_)
  : engine(eng_),
    verbose(verb_),
    ostr(ostr_) {}

void AI::print() const {
  auto mask = engine->get_mask();
  auto numbers = engine->get_numbers();
  size_t size_x = engine->get_size_x();
  size_t size_y = engine->get_size_y();
  for(size_t y = 0; y < size_y; y++) {
    for(size_t x = 0; x < size_x; x++) {
      if(mask[x][y] == ' ') {
        (*ostr) << numbers[x][y] << ' ';
      } else {
        (*ostr) << mask[x][y] << ' ';
      }
    }
    (*ostr) << std::endl;
  }
}

void AI::print_mines() const {
  for(auto y : engine->get_bombs()) {
    for(auto cell : y) {
      (*ostr) << (cell ? 1 : 0) << " ";
    }
    (*ostr) << std::endl;
  }
}

void AI::print_lose() const {
  auto mask = engine->get_mask();
  auto numbers = engine->get_numbers();
  auto bombs = engine->get_bombs();
  size_t size_x = engine->get_size_x();
  size_t size_y = engine->get_size_y();
  for(size_t y = 0; y < size_y; y++) {
    for(size_t x = 0; x < size_x; x++) {
      if(mask[x][y] == ' ') {
        (*ostr) << numbers[x][y] << ' ';
      } else {
        if(bombs[x][y]) {
          (*ostr) << '*' << ' ';
        } else {
          (*ostr) << mask[x][y] << ' ';
        }
      }
    }
    (*ostr) << std::endl;
  }
}

auto AI::get_field() const {
  std::vector<std::vector<char>> result;
  auto mask = engine->get_mask();
  auto numbers = engine->get_numbers();
  size_t size_x = engine->get_size_x();
  size_t size_y = engine->get_size_y();
  for(size_t x = 0; x < size_x; x++) {
    result.push_back(std::vector<char>());
    for(size_t y = 0; y < size_y; y++) {
      if(mask[x][y] == ' ') {
        result[x].push_back(numbers[x][y] + '0');
      } else {
        result[x].push_back(mask[x][y]);
      }
    }
  }
  return result;
}

void print_field(const std::vector<std::vector<char>> &f_, std::ostream *ostr) {
  size_t size_x = f_.size();
  size_t size_y = f_[0].size();
  for(size_t y = 0; y < size_y; y++) {
    for(size_t x = 0; x < size_x; x++) {
      (*ostr) << f_[x][y] << ' ';
    }
    (*ostr) << std::endl;
  }
}

bool AI::run() {
  engine->click(Game::a_open, 5, 5);
  size_t size_x = engine->get_size_x();
  size_t size_y = engine->get_size_y();
  bool changed = false;
  bool won = false;
  do {
    changed = false;
    auto field = get_field();
    if(verbose){
      print_field(field, ostr);
      (*ostr) << std::endl;
    }
    for(size_t x = 0; x < size_x; x++) {
      for(size_t y = 0; y < size_y; y++) {
        if((field[x][y] >= '1') && (field[x][y] <= '8')) {
          size_t count = 0;
          engine->cycle_cells(x, y, [&field, &count](size_t x_, size_t y_) {
            if((field[x_][y_] == '#') || (field[x_][y_] == 'f')) {
              count++;
            }
          });
          if(count == (field[x][y] - '0')) {
            engine->cycle_cells(x, y, [&field, this, &changed](size_t x_, size_t y_) {
              if(field[x_][y_] == '#') {
                this->engine->click(Game::a_flag, x_, y_);
                field[x_][y_] = 'f';
                changed = true;
              }
            });
          }
        }
      }
    }
    field = get_field();
    if(verbose){
      print_field(field, ostr);
      (*ostr) << std::endl;
    }
    for(size_t x = 0; x < size_x; x++) {
      for(size_t y = 0; y < size_y; y++) {
        if((field[x][y] >= '1') && (field[x][y] <= '8')) {
          size_t count = 0;
          engine->cycle_cells(x, y, [&field, &count](size_t x_, size_t y_) {
            if(field[x_][y_] == 'f') {
              count++;
            }
          });
          if(count == (field[x][y] - '0')) {
            engine->cycle_cells(x, y, [&field, this, &changed, &won](size_t x_, size_t y_) {
              if(field[x_][y_] == '#') {
                auto code = this->engine->click(Game::a_open, x_, y_);
                if(code == 1) {
                  if(verbose){
                    print_lose();
                    (*ostr) << "I lost!" << std::endl;
                  }
                  changed = false;
                } else if (code == 2) {
                  changed = false;
                  won = true;
                  if(verbose) {
                    print();
                    (*ostr) << "I won!" << std::endl;
                  }
                }
                field = get_field();
                
              }
            });
          }
        }
      }
    }
  } while (changed);
  if(!won) {
    if(verbose) {
      (*ostr) << "Not sure what to do here..." << std::endl;
    } else {
      print();
    }
  }
  return won;
}

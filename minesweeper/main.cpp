//
//  main.cpp
//  minesweeper
//
//  Created by Anton Suslov on 24/07/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#include <iostream>
#include "minesweeper.hpp"
#include "mineui.hpp"
#include "mineai.hpp"
#include "minemanager.hpp"

int main(int argc, const char * argv[]) {
    Manager man;
    man.run();
    return 0;
}

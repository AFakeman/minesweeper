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
    Game eng(10, 10, 10);
    UI ui(&eng);
    ui.run();
    return 0;
}

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

void smart_click(Game &game_) {
    
}

int main(int argc, const char * argv[]) {
    Game kek(10,10,10);
    UI ui(&kek);
    ui.run();
    return 0;
}

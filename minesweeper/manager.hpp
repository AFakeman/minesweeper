//
//  manager.hpp
//  mrmanager
//
//  Created by Anton Suslov on 17/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#ifndef manager_hpp
#define manager_hpp

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
class CommandManager {
    typedef std::function<bool(const std::vector<std::string>&)> func;
    std::map<std::string, func> commands;
    std::function<void()> prompt;
    bool status;
public:
    CommandManager() = default;
    auto ProcessCommand(const std::string &command);
    void AddCommand(const std::string &com, const func &fun);
    void Loop();
    void SetPrompt(std::function<void()> pr_) {
        prompt = pr_;
    }
};
#endif /* manager_hpp */

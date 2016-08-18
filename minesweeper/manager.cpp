//
//  manager.cpp
//  mrmanager
//
//  Created by Anton Suslov on 17/08/16.
//  Copyright © 2016 Anton Suslov. All rights reserved.
//

#include "manager.hpp"
auto CommandManager::ProcessCommand(const std::string &command) {
    std::vector<std::string> tok_com;
    std::stringstream strstream(command);
    std::string token = "";
    while (getline(strstream, token, ' ')) {
        tok_com.push_back(token);
    }
    if(tok_com.empty()) {
        return std::pair<std::string, bool>("", false);
    }
    auto result = std::pair<std::string, bool>(tok_com[0], true);
    auto func = commands.find(tok_com[0]);
    if(func != commands.end()) {
        status = func->second(tok_com);
    } else {
        result.second = false;
    }
    return result;
}

void CommandManager::Loop() {
    auto result = ProcessCommand("");
    status = false;
    do {
        prompt();
        std::string command;
        getline(std::cin, command);
        result = ProcessCommand(command);
        if(!result.second) {
            if(result.first != "") {
                std::cout << "Unrecognised command: " << result.first << std::endl;
            }
        }
    } while (!status);
}

void CommandManager::AddCommand(const std::string &com, const func &fun) {
    if(commands.find(com) != commands.end()) {
        throw std::exception();
    }
    commands[com] = fun;
}
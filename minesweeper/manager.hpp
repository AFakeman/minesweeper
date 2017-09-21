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
 public:
    typedef std::function<bool(const std::vector<std::string>&)> func_t;
  
    std::pair<std::string, bool> ProcessCommand(const std::string &command);
  
    void AddCommand(const std::string &com, const func_t &fun);
    void SetPrompt(std::function<void()> pr_) {
      prompt = pr_;
    }
    void Loop();
  
 private:
  std::map<std::string, func_t> commands;
  std::function<void()> prompt;
  bool status;
};
#endif /* manager_hpp */

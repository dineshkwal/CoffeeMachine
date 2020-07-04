//
//  Utils.cpp
//  CoffeeMachine
//
//  Created by Strike on 04/07/20.
//  Copyright © 2020 Strike. All rights reserved.
//

#include "Utils.h"

#include <mutex>
#include <iostream>

namespace utils {

    std::mutex gMutex;

    void safe_print(const std::string& str) {
        std::scoped_lock guard(gMutex);
        std::cout << str;
    }

} // namespace utils



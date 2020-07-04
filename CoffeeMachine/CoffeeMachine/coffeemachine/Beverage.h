//
//  Beverage.h
//  CoffeeMachine
//
//  Created by Strike on 04/07/20.
//  Copyright © 2020 Strike. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

namespace dcm {

    struct Ingredient {
        std::string name;
        int quantity = 0;
    };

    struct Beverage {
        std::string name;
        std::vector<Ingredient> ingredients;
    };

} // namespace dcm

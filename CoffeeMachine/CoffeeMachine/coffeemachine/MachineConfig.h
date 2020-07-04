//
//  MachineConfig.h
//  CoffeeMachine
//
//  Created by Strike on 04/07/20.
//  Copyright © 2020 Strike. All rights reserved.
//

#pragma once

#include "Stock.h"
#include "Beverage.h"

namespace dunzo {

    struct MachineConfig {
        int outlets;
        Stock stock;
        std::vector<Beverage> beverages;
    };

} // namespace dunzo

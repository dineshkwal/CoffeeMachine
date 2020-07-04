//
//  CoffeeMachine.h
//  CoffeeMachine
//
//  Created by Strike on 04/07/20.
//  Copyright © 2020 Strike. All rights reserved.
//

#pragma once

#include "Stock.h"

#include "threading/Semaphore.h"

namespace dunzo {
    // forward declaration
    struct Beverage;
    class MachineConfig;

    class CoffeeMachine {
    public:
        // Initialie the machine with give config
        CoffeeMachine(const MachineConfig& config);
        
        // prepare a given beverage
        void Prepare(const std::string& beverageName);
        
        // Output the name of one of the beverages randomly
        std::string ListABeverage() const;
        
        // Number of outlets
        int Outlets() const;
        
    private:
        int mOutlets;
        threading::Semaphore mOutletSemaphore;
        Stock mStock;
        std::vector<Beverage> mBeverages;
        std::atomic_int mID;
    };

} // namespace dunzo

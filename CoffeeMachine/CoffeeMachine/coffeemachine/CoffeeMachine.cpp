//
//  CoffeeMachine.cpp
//  CoffeeMachine
//
//  Created by Strike on 04/07/20.
//  Copyright © 2020 Strike. All rights reserved.
//

#include "CoffeeMachine.h"

#include "MachineConfig.h"
#include "Beverage.h"
#include "Utils.h"

#include <iostream>

namespace dcm {

    CoffeeMachine::CoffeeMachine(const MachineConfig& config)
    : mOutlets(config.outlets)
    , mStock(config.stock)
    , mBeverages(config.beverages)
    , mOutletSemaphore(config.outlets)
    , mID(0)
    {
    }
    
    void CoffeeMachine::Prepare(const std::string& beverageName) {
        // Acquire a free outlet, if any, otherwise wait
        mOutletSemaphore.acquire();
        
        const auto id = mID.load();
        mID++;
        utils::safe_print(std::string("==== Request ID: ") + std::to_string(id) + std::string(" -> Prepare: ") + beverageName + std::string(" ====\n"));
        
        auto it = std::find_if(mBeverages.begin(), mBeverages.end(), [&](const auto& b) {
            return b.name == beverageName;
        });
        
        if (it == mBeverages.end()) {
            utils::safe_print(std::string("==== Response ID: ") + std::to_string(id) +  std::string(" -> Beverage not found ====\n"));
        }
        
        bool prepared = true;
        try {
            const auto& ingredients = it->ingredients;
            for (auto ig : ingredients) {
                mStock.Consume(ig.name, ig.quantity);
            }
        }
        catch(const ItemNotAvailableException& e) {
            prepared = false;
            utils::safe_print(std::string("==== Response ID: ") + std::to_string(id) +  std::string(" -> Ingredient not available : ") + e.GetItem() + std::string(" ====\n"));
        }
        catch(...) {
            prepared = false;
        }
        
        if (prepared) {
            utils::safe_print(std::string("==== Response ID: ") + std::to_string(id) +  std::string(" -> Prepared Beverage : ") + beverageName + std::string(" ====\n"));
        }
        else{
            utils::safe_print(std::string("==== Response ID: ") + std::to_string(id) +  std::string(" -> Couldn't prepare : ") + beverageName + std::string(" ====\n"));
        }
    }
    
    std::string CoffeeMachine::ListABeverage() const {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        const int r = std::rand() % mBeverages.size();
        return mBeverages[r].name;
    }
    
    int CoffeeMachine::Outlets() const {
        return mOutlets;
    }

} // namespace dcm

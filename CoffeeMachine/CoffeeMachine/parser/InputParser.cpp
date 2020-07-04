//
//  InputParser.cpp
//  CoffeeMachine
//
//  Created by Strike on 04/07/20.
//  Copyright © 2020 Strike. All rights reserved.
//

#include "InputParser.h"

#include "MachineConfig.h"

#include "json.hpp"

using json = nlohmann::json;

namespace dcm {

    MachineConfig InputParser::Parse(const std::string& jsonData) {
        MachineConfig config;
        json machine = json::parse(jsonData)["machine"];
        // parse number of outlets
        config.outlets = machine["outlets"]["count_n"];
        // parse items
        auto items = machine["total_items_quantity"];
        for (json::iterator it = items.begin(); it != items.end(); ++it) {
            config.stock.AddItem(it.key(), it.value());
        }
        // parse beverages
        auto beverages = machine["beverages"];
        for (json::iterator it = beverages.begin(); it != beverages.end(); ++it) {
            Beverage b;
            b.name = it.key();
            auto ingredients = it.value();
            // parse beverage ingredients
            for (json::iterator it2 = ingredients.begin(); it2 != ingredients.end(); ++it2) {
                b.ingredients.push_back(Ingredient{it2.key(), it2.value()});
            }
            config.beverages.push_back(b);
        }
        return config;
    }

} // namespace dcm


//
//  Stock.h
//  CoffeeMachine
//
//  Created by Strike on 04/07/20.
//  Copyright © 2020 Strike. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <exception>
#include <mutex>

namespace dunzo {

    struct ItemNotAvailableException : public std::exception {
    public:
        ItemNotAvailableException(const std::string& name) : itemName(name) {}
        const std::string& GetItem() const { return itemName; }
    private:
        std::string itemName;
    };

    class Stock {
    public:
        Stock();
        
        Stock(const Stock& other);
        
        void AddItem(const std::string& name, int quantity);
        
        bool IsAvailable(const std::string& item, int quantity);
        
        void Consume(const std::string& item, int quantity);
        
    private:
        std::unordered_map<std::string, int> mItemQuantity;
        std::mutex mMutex;
    };

} // namespace dunzo

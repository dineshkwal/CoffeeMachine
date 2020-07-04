//
//  Stock.cpp
//  CoffeeMachine
//
//  Created by Strike on 04/07/20.
//  Copyright © 2020 Strike. All rights reserved.
//

#include "Stock.h"

namespace dunzo {

    Stock::Stock() = default;
    
    void Stock::AddItem(const std::string& name, int quantity) {
        std::scoped_lock guard(mMutex);
        mItemQuantity.emplace(name, quantity);
    }
    
    bool Stock::IsAvailable(const std::string& item, int quantity) {
        std::scoped_lock guard(mMutex);
        return mItemQuantity.count(item) && mItemQuantity[item] >= quantity;
    }
    
    void Stock::Consume(const std::string& item, int quantity) {
        std::scoped_lock guard(mMutex);
        if (!mItemQuantity.count(item) || mItemQuantity[item] < quantity) {
             throw ItemNotAvailableException{item};
        }
        mItemQuantity[item] -= quantity;
    }
    
    Stock::Stock(const Stock& other) {
        std::scoped_lock guard(mMutex);
        this->mItemQuantity = other.mItemQuantity;
    }

} // namespace dunzo

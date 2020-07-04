//
//  InputParser.h
//  CoffeeMachine
//
//  Created by Strike on 04/07/20.
//  Copyright © 2020 Strike. All rights reserved.
//

#pragma once

#include <string>

namespace dcm {
    // forward declaration
    class MachineConfig;

    class InputParser {
    public:
        static MachineConfig Parse(const std::string& jsonData);
    };

} // namespace dcm

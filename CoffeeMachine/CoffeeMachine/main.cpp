//
//  main.cpp
//  CoffeeMachine
//
//  Created by Strike on 04/07/20.
//  Copyright © 2020 Strike. All rights reserved.
//

#include "MachineConfig.h"
#include "InputParser.h"
#include "CoffeeMachine.h"

#include "ThreadPool.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

void RunTestCase(const std::string& jsonData) {
    // parse json data
   dcm::MachineConfig machineConfig = dcm::InputParser::Parse(jsonData);
   
   // init machine
   dcm::CoffeeMachine machine(machineConfig);
   
   // test machine with a threadpool
    threading::ThreadPool pool(machine.Outlets());
    std::vector<std::future<void>> futures;
    for (int i = 0; i < machine.Outlets(); ++i) {
        // randomly select a beverage from machine and try to prepare it
        futures.push_back(pool.enqueue([&]{ machine.Prepare(machine.ListABeverage()); }));
    }
    
    for (auto& f : futures) {
        f.wait();
    }
}

int main() {
    // Path to Test files folder
    std::filesystem::path testFilesPath = std::filesystem::current_path();
    testFilesPath.append("TestFiles");
    
    std::cout << "Scanning test cases folder...\n";
    // Scan each file in test files folder
    for (const auto& testFile : std::filesystem::recursive_directory_iterator(testFilesPath)) {
        if (testFile.is_regular_file()) {
            std::cout << "Running test case -> " << testFile.path().filename() << '\n';
            // Get content of the file
            std::ifstream f(testFile);
            std::stringstream content;
            content << f.rdbuf();
            // Run test case with the json content
            RunTestCase(content.str());
            std::cout << "----------------------------------------------------- \n";
        }
    }
}

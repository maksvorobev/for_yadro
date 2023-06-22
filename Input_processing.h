#pragma once 
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


class Input_processing{
public:
    Input_processing() = default;
    std::vector<std::vector<std::string>>    input_processing(const std::string& filename);

};

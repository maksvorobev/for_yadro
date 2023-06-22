#pragma once
#include <string>
#include <vector>
#include <sstream>



class Split_string_by_character{
public:
    Split_string_by_character() = default;
    std::vector<std::string> split(const std::string& str, char sep);

};
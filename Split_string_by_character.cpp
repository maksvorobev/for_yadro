#include "Split_string_by_character.h"

std::vector<std::string> Split_string_by_character::split(const std::string& str, char sep){
    std::vector<std::string> seglist;
    std::string segment;
    std::stringstream test(str);
    while(std::getline(test, segment, sep))
    {
        seglist.push_back(segment);
    }
    return seglist;
}
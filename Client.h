#pragma once
#include <string>


class Client{
    std::string name;
    
public:
    Client() = default;
    Client(const std::string& name);
    std::string get_name();
};
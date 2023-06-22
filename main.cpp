#include "bits/stdc++.h"
//#include "input_processing.cpp"
#include "Client.h"
#include "Event_handler.h"
#include "Split_string_by_character.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Invalid number of arguments." << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    /*
    auto res = read_from_file(filename);
    for (auto x : res){
        for (auto y : x){
            std::cout << y << ' ';
        }
        std::cout << std::endl;
    }
    Client cl("fwfwgf");
    std::cout << cl.get_name();
    */
   Event_handler handle(filename);
   std::string str = "12:45";
   Split_string_by_character sp;
   auto v  = sp.split(str, ':');
   //std::cout << v[0] << ' ' << v[1];

}

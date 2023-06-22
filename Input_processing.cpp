#include "Input_processing.h"


    std::vector<std::vector<std::string>> Input_processing::input_processing(const std::string& filename){
    std::ifstream fin;
    fin.open(filename);
    std::vector<std::vector<std::string>> v;
    if (!fin.is_open()){
        std::cout << "error with open file !";
    }
    else{
        std::string str;
        while (!fin.eof()){
            str = "";
            std::getline(fin, str);
            std::istringstream input(std::move(str));
            std::vector<std::string> curr;
            while (!input.eof()) {
                std::string substring;
                input  >> substring;
                curr.push_back(substring);
            }
            v.push_back(curr);
            //std::cout << str << '\n';
        }
    }
    fin.close();
    return v;
}

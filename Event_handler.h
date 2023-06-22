#pragma once
#include "Input_processing.h"
#include "Game_club.h"
#include "Split_string_by_character.h"
#include <iostream>
#include <stdexcept>


class Event_handler{
    
    enum INPUT_EVENT{
        CLIENT_CAME = 1,
        CLIENT_SAT_AT_THE_TABLE,
        CIENT_IS_WAITING,
        CLIENT_LEFT,
    };
    
    Game_club club;
    Time time_end;
    std::vector<std::vector<std::string>> events;
    void error(Time erroe_time, std::string error_name);
    void client_left(Time erroe_time, std::string client_name);
    void client_sat_at_the_table(Time time, int table_number);

    void end_of_working_day();
public:
    //Event_handler() = default;
    Event_handler(const std::string& filename);
    void start_processing();

};

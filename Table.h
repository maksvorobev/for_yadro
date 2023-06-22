#pragma once
#include "Client.h"
#include "Time.h"
#include <cmath>
#include <iostream>

class Table{
    Client client = Client("");
    Time time_start;
    //Time time_end;
    int total_profit = 0;
    bool table_free = true;
    int hourly_cost;
    int total_work_time_in_min = 0;

public:
    Table() = default;
    Table(int hourly_cost);
    Client get_client();
    void land_a_client(Client client, Time time_start);
    void client_leaves_the_table(Time time);
    bool is_table_free();
    int get_salary();
    Time get_total_work_time();

};
#pragma once
#include "Table.h"
#include "Client.h"
#include <map>
#include <string>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <algorithm>

class Game_club{
    int number_of_visitors;
    Time opening_time;
    Time closing_time;
    int hourly_cost;
    std::map<std::string, Client> mp_users;
    std::map<int, Table> mp_tables;
    std::queue<Client> user_queue;

public:
    Game_club(int number_of_visitors, Time opening_time, Time closing_time, int hourly_cost);
    Game_club() = default;
    bool does_the_user_exist(const std::string& name);
    void let_the_clint_in(const std::string& name);
    Time get_closing_time();
    Time get_opening_time();
    Table& get_Table_by_index(int index);  // TODO
    bool is_there_a_free_table();
    std::queue<Client>& get_user_queue();
    int get_number_of_visitors();
    int find_where_client_is_sitting_by_name(std::string client_name);
    std::vector<std::string> list_left_at_the_end_of_the_day();
    void withdraw_salary();
};
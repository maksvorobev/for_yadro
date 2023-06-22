#include "Game_club.h"


Game_club::Game_club(int number_of_visitors, Time opening_time, Time closing_time, int hourly_cost): 
number_of_visitors(number_of_visitors), 
opening_time(opening_time), 
closing_time(closing_time),
hourly_cost(hourly_cost){

    for (int i = 1; i <= number_of_visitors; ++i){
        mp_tables[i] = Table(hourly_cost);
    }
}



bool Game_club::does_the_user_exist(const std::string& name){
    return mp_users.count(name) == 0 ? false : true;
}

void Game_club::let_the_clint_in(const std::string& name){
    mp_users[name] = Client(name);
}

Time Game_club::get_closing_time() {return closing_time;}

Time Game_club::get_opening_time() {return opening_time;}

Table& Game_club::get_Table_by_index(int index){return mp_tables[index];}


bool Game_club::is_there_a_free_table(){
    for (auto& [l, r] : mp_tables){
        if (r.is_table_free() == true){
            return true;
        }
    }
    return false;
}


std::queue<Client>& Game_club::get_user_queue(){return user_queue;}


int Game_club::get_number_of_visitors() {return number_of_visitors;}


int Game_club::find_where_client_is_sitting_by_name(std::string client_name){

    for (auto& [l, r] : mp_tables){
        if (r.get_client().get_name() == client_name){
            return l;
        }
    }
    return -1;
}



std::vector<std::string> Game_club::list_left_at_the_end_of_the_day(){
    std::vector<std::string> v;
    for (auto& [l, r]: mp_tables){
        if (r.is_table_free() == false){
            v.push_back(r.get_client().get_name());
            r.client_leaves_the_table(closing_time);
        }
    }
    std::sort(v.begin(), v.end());
    return move(v);

}



void Game_club::withdraw_salary(){
    for (auto& [l, r] : mp_tables){
        std::cout << l << ' ' << r.get_salary() << ' ' << r.get_total_work_time().hours <<
        ':' << r.get_total_work_time().minutes << '\n';
    }
}
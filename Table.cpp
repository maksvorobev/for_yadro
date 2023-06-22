#include "Table.h"

Table::Table(int hourly_cost): hourly_cost(hourly_cost) {}


Client Table::get_client() {return client;}


void Table::land_a_client(Client client, Time time_start){
    table_free = false;
    //std::cout << table_free << '\n';

    this->client = client;
    this->time_start = time_start;
}


void Table::client_leaves_the_table(Time time){
    double salary = std::ceil(static_cast<double>((time.hours*60 + time.minutes) - (time_start.hours*60 + time_start.minutes)) / 60.0)*hourly_cost;
    total_profit += salary;
    table_free = true;
    total_work_time_in_min += ((time.hours*60 + time.minutes) - (time_start.hours*60 + time_start.minutes));
}



bool Table::is_table_free(){ return table_free;}


int Table::get_salary() {return total_profit;}


Time Table::get_total_work_time() {return Time(total_work_time_in_min/60, total_work_time_in_min%60);}
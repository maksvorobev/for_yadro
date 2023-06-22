 #include "Event_handler.h"




Event_handler::Event_handler(const std::string& filename){
    Input_processing proc;
    events = proc.input_processing(filename);
    Split_string_by_character sp; 
    Time open = Time(std::stoi(sp.split(events[1][0], ':')[0]), std::stoi(sp.split(events[1][0], ':')[1]));
    Time end = Time(std::stoi(sp.split(events[1][1], ':')[0]), std::stoi(sp.split(events[1][1], ':')[1]));
    this->time_end = end;
    std::printf("%02d:%02d\n", open.hours, open.minutes);
    club = Game_club(static_cast<int>(std::stoi(events[0][0])), open, end, std::stoi(events[2][0]));
    start_processing();
    end_of_working_day();
    
}

void Event_handler::start_processing(){

    for (int i = 3; i < events.size(); ++i){

       Split_string_by_character sp;
        switch(stoi(events[i][1])){
            case INPUT_EVENT::CLIENT_CAME:
            {
                int h =  stoi(sp.split(events[i][0], ':')[0]);
                int m = stoi(sp.split(events[i][0], ':')[1]);
                std::string name = events[i][2];
                check_CLIENT_CAME_input(events[i][0], name);
                std::printf("%02d:%02d %d %s\n", h, m, 1, name.c_str());
        
                if (club.does_the_user_exist(events[i][2]) == true){
                    error(Time(h, m), "YouShallNotPass");
                }
                else if (!(60*h + m <= club.get_closing_time().convert_to_min() and 
                   60*h + m >= club.get_opening_time().convert_to_min() )){
                    error(Time(h, m), "NotOpenYet");
                }
                else{
                    club.let_the_clint_in(events[i][2]);
                    
                }
                break;
            }
            case INPUT_EVENT::CLIENT_SAT_AT_THE_TABLE:
            {

                int h =  stoi(sp.split(events[i][0], ':')[0]);
                int m = stoi(sp.split(events[i][0], ':')[1]);
                int table_number = stoi(events[i][3]);
                std::string name = events[i][2];
                check_CLIENT_SAT_AT_THE_TABLE_input(events[i][0], name, table_number);
                std::printf("%02d:%02d %d %s %d\n", h, m, 2, name.c_str(), table_number);
         
                if (club.does_the_user_exist(events[i][2]) == false){
                    error(Time(h, m), "ClientUnknown");
                }
                else if (club.get_Table_by_index(table_number).is_table_free() == false){
                    error(Time(h, m), "PlaceIsBusy");
                }
                else{
                    //std::cout << h << ':' << m << ' ' << name << ' ' << club.get_Table_by_index(table_number).is_table_free() << ' ' << table_number <<  '\n';
                    club.get_Table_by_index(table_number).land_a_client(name, Time(h, m));
                    
                }
                break;
            }
            case INPUT_EVENT::CIENT_IS_WAITING:
                {
                    int h =  stoi(sp.split(events[i][0], ':')[0]);
                    int m = stoi(sp.split(events[i][0], ':')[1]);
                    std::string name = events[i][2];
                    check_CIENT_IS_WAITING_input(events[i][0], name);
                    std::printf("%02d:%02d %d %s\n", h, m, 3, name.c_str());
                    if (club.is_there_a_free_table() == true){
                        error(Time(h, m), "ICanWaitNoLonger!");
                    }
                    else if (club.get_user_queue().size() > club.get_number_of_visitors()){
                        client_left(Time(h, m), name);
                    }
                    else{
                        club.get_user_queue().push(Client(name)); // ??? mb issue
                    }

                }
                break;
            case INPUT_EVENT::CLIENT_LEFT:
                {
                    int h =  stoi(sp.split(events[i][0], ':')[0]);
                    int m = stoi(sp.split(events[i][0], ':')[1]);
                    std::string name = events[i][2];
                    check_CLIENT_LEFT_input(events[i][0], name);
                     std::printf("%02d:%02d %d %s\n", h, m, 4, name.c_str());
            
                    if (club.does_the_user_exist(events[i][2]) == false){
                        error(Time(h, m), "ClientUnknown");
                    }
                    else {
                        int table_number = club.find_where_client_is_sitting_by_name(name);
                        if (table_number == -1){
                            std::runtime_error("clint dose not seat anywhere !!");
                        }
                        else{
                            club.get_Table_by_index(table_number).client_leaves_the_table(Time(h, m));
                            client_sat_at_the_table(Time(h, m), table_number);
                            club.client_left_from_club(name);
                            
                        }
                    }
                }
                break;
            default:
                throw std::runtime_error("smth wrong !!!");
        }
    }
}



void Event_handler::error(Time erroe_time, std::string error_name){
    std::printf("%02d:%02d %d %s\n", erroe_time.hours,
        erroe_time.minutes, 13, error_name.c_str());
}



void Event_handler::client_left(Time erroe_time, std::string client_name){
    std::printf("%02d:%02d %d %s\n", erroe_time.hours,
        erroe_time.minutes, 11, client_name.c_str());
}   



void Event_handler::client_sat_at_the_table(Time time, int table_number){
    if (club.get_user_queue().size() ==0 ){
        std::runtime_error("queue is empty !!!");
    }
    else{
        Client cl = club.get_user_queue().front();
        club.get_user_queue().pop();
        club.get_Table_by_index(table_number).land_a_client(cl, time);
        std::printf("%02d:%02d %d %s %d\n", time.hours,
        time.minutes, 12, cl.get_name().c_str(), table_number);
    }
}



void Event_handler::end_of_working_day(){
    auto remaining_in_end = club.list_left_at_the_end_of_the_day();
    for (auto& x : remaining_in_end){
        std::printf("%02d:%02d %d %s\n", time_end.hours,
        time_end.minutes, 11, x.c_str());
    }
    std::printf("%02d:%02d \n", time_end.hours,
        time_end.minutes );
    club.withdraw_salary();
}


void Event_handler::check_correct_name(std::string& name){
    for (auto x : name){
        if (!((97 <= x and x <= 122) or ( x >= 48 and x <= 57))){
            
            throw std::runtime_error("incorrect input(name)!!!");
        }
    }
}

void Event_handler::check_correct_date(std::string& date){
    Split_string_by_character sp;
    auto h_str =  sp.split(date, ':')[0];
    auto m_str = sp.split(date, ':')[1];
    int h =  stoi(sp.split(date, ':')[0]);
    int m = stoi(sp.split(date, ':')[1]);
    if (!(h >= 0 and h <=23)){
        throw std::runtime_error("incorrect input(date)!!!");
    }
    else if (h_str.size() != 2 or m_str.size() != 2){
        throw std::runtime_error("incorrect input(date)!!!");
    }
    else if (!(m >= 0 and m <= 60)){
        throw std::runtime_error("incorrect input(date)!!!");
    }
}


void Event_handler::check_correct_table_number(int number){
    if (!(number >= 1 and number <= club.get_number_of_visitors())){
        throw std::runtime_error("incorrect input(number of table)!!!");
    }
}


void Event_handler::check_CLIENT_CAME_input(std::string& date, std::string& name){
    check_correct_name(name);
    check_correct_date(date);
}

void Event_handler::check_CLIENT_SAT_AT_THE_TABLE_input(std::string& date, std::string& name, int number){
    check_correct_name(name);
    check_correct_date(date);
    check_correct_table_number(number);

}

void Event_handler::check_CIENT_IS_WAITING_input(std::string& date, std::string& name){
    check_correct_name(name);
    check_correct_date(date);
}


void Event_handler::check_CLIENT_LEFT_input(std::string& date, std::string& name){
    check_correct_name(name);
    check_correct_date(date);
}


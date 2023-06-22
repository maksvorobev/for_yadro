#include "Time.h"


Time::Time(int hours, int minutes): hours(hours), minutes(minutes) {}


int Time::convert_to_min(){
    return 60*hours + minutes;
}
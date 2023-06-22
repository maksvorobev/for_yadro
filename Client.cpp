#include "Client.h"


Client::Client(const std::string& name): name(name) {}


std::string Client::get_name(){ return name;}
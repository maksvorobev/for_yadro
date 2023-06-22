cmake_minimum_required(VERSION 3.13)  # CMake version check
project(gamer_club)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 20)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES 
    main.cpp
    Input_processing.cpp
    Client.cpp
    Table.cpp
    Time.cpp
    Game_club.cpp
    Event_handler.cpp
    Split_string_by_character.cpp
    
)

set(HEADERS_FILES 
    Client.h
    Table.h
    Time.h
    Game_club.h
    Event_handler.h
    Input_processing.h
    Split_string_by_character.h
)



# Add executable target with source files listed in SOURCE_FILES variable
add_executable(a.out ${SOURCE_FILES})
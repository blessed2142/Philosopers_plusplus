cmake_minimum_required(VERSION 3.1)

project(Philosophers++ VERSION 1.0 LANGUAGES CXX)

set(SRC main.cpp OptionsParser.cpp Philo.cpp Waiter.cpp )

include_directories( . )
add_executable(philosophers ${SRC})
add_compile_options( -O0 -g -std=c++17 )

target_link_libraries(philosophers pthread)

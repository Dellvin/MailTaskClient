cmake_minimum_required(VERSION 3.15)
project(EnteringTask_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -Wextra -Werror=pedantic")

enable_testing()

add_executable(EnteringTask_client project/main.cpp project/UI/ui.cpp project/UI/ui.h)

add_subdirectory(project/tests)
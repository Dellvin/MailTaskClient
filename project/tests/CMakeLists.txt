cmake_minimum_required(VERSION 3.15)

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_subdirectory(./lib/googletest)
include_directories(lib/googletest/include)
add_executable(Tests test.cpp ../UI/ui.cpp ../UI/ui.h)

target_link_libraries(Tests gtest gmock gtest_main)

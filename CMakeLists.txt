cmake_minimum_required(VERSION 4.0)
project(COP3530_Project_2_LoL_Game_Stats)

set(CMAKE_CXX_STANDARD 14)

#compile flags to match Gradescope test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror") # remove -Wall if you don't want as many warnings treated as errors
# gradescope does use -Werror, so if you remove it here you may run into issues when trying to submit
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

##pull in desired version of catch through cmake automatically, make it available
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2 # if you run into issues, try updating your editor or downgrading to a lower version of catch v3
)
FetchContent_MakeAvailable(Catch2)

include_directories(src)

add_executable(Main
        src/main.cpp
        src/quicksort.h
        src/heapsort.h)

add_executable(Tests
        test/test.cpp
        src/quicksort.h
        src/heapsort.h)


target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)


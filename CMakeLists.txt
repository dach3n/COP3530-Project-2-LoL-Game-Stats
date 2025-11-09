cmake_minimum_required(VERSION 3.30)

project(COP3530_Project_2_LoL_Game_Stats)

set(CMAKE_CXX_STANDARD 14)

# Compile flags to match Gradescope test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# =========================================================
# 1. Fetch Catch2 for testing
# =========================================================
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# =========================================================
# 2. Fetch SFML for graphic output
# =========================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# =========================================================
# 3. Include source directories
# =========================================================
include_directories(src)

# =========================================================
# 4. Define executables
# =========================================================
add_executable(Main
        src/main.cpp
        src/quicksort.h
        src/heapsort.h
        src/importCSV.h
)

add_executable(Tests
        test/test.cpp
        src/quicksort.h
        src/heapsort.h
)

# =========================================================
# 5. Link libraries
# =========================================================
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)
target_compile_features(Main PRIVATE cxx_std_17)
target_link_libraries(Main PRIVATE SFML::Graphics)

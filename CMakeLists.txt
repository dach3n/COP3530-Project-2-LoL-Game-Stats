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
# 2. Find SFML installed locally
# =========================================================
# Point this to your SFML directory — adjust if needed
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

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
target_link_libraries(Main PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

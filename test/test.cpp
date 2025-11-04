#include <catch2/catch_test_macros.hpp>
#include <iostream>

// uncomment and replace the following with your own headers
// David Chen 97345471
#include <algorithm>
#include <random>

#include "heapsort.h"
#include "catch2/internal/catch_windows_h_proxy.hpp"

using namespace std;

TEST_CASE("Trivial Array", "[heapsort]") {
    vector<int> arr = {3, 2, 5, 4, 6, 1, 9, 7, 8};
    vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    heapSort(arr);
    REQUIRE(arr == expected);
}

TEST_CASE("Big Heap Sort", "[heapsort]") {
    vector<int> arr;
    for (int i = 0; i < 100000; i++) {
        arr.push_back(i + 1000 + rand() % 9000);
    }
    vector<int> test = arr;
    heapSort(arr);
    sort(test.begin(), test.end());
    for (int i = 0; i < static_cast<int>(arr.size()); i++) {
        cout << i << ": " << test[i] << " | " << arr[i] << endl;
        REQUIRE(arr[i] == test[i]);
    }
}


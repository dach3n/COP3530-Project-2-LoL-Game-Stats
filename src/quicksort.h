//
// Created by kingd on 11/3/2025.
//

#ifndef COP3530_PROJECT_2_LOL_GAME_STATS_QUICKSORT_H
#define COP3530_PROJECT_2_LOL_GAME_STATS_QUICKSORT_H

#include <cmath>
#include <vector>
#include <random>
using namespace std;

inline int partition(vector<int>& arr, const int low, const int high) {
    // Choose pivot
    const int pivot = arr[low];
    int up = low, down = high;

    while (up < down) {
        for (int i = up; i < high; i++) {
            if (arr[up] > pivot) {
                break;
            }
            up++;
        }
        for (int i = high; i > low; i--) {
            if (arr[down] < pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            swap(arr[up], arr[down]);
        }
    }
    swap(arr[low], arr[down]);
    return down;

}

inline int partition_r(vector<int>& arr, const int low, const int high) { // move random pivot into first index
    srand(time(nullptr));
    const int random = low + rand() % (high - low);
    swap(arr[random], arr[low]);
    return partition(arr, low, high);
}

inline void myQuickSort(vector<int>& arr, const int low, const int high) {
    if (low < high) {
        const int pivot = partition_r(arr, low, high);
        myQuickSort(arr, low, pivot - 1);
        myQuickSort(arr, pivot+1, high);
    }
}

#endif //COP3530_PROJECT_2_LOL_GAME_STATS_QUICKSORT_H
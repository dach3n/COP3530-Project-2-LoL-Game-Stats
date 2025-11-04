//
// Created by kingd on 11/3/2025.
//

#ifndef COP3530_PROJECT_2_LOL_GAME_STATS_QUICKSORT_H
#define COP3530_PROJECT_2_LOL_GAME_STATS_QUICKSORT_H

#include <cmath>
#include <vector>
using namespace std;

inline int partition(vector<int*> arr, const int low, const int high) {
    // Choose pivot as median of three
    const int mid = floor((low + high) / 2);
    if (*(arr[mid]) < *(arr[low])) {
        swap(arr[low], arr[mid]);
    }
    if (*(arr[high]) < *(arr[low])) {
        swap(arr[low], arr[high]);
    }
    if (*(arr[mid]) < *(arr[high])) {
        swap(arr[mid], arr[high]);
    }
    const int pivot = *(arr[high]);
    int up = low, down = high;

    while (up < down) {
        for (int i = up; i < high; i++) {
            if (*(arr[up]) > pivot) {
                break;
            }
            up++;
        }
        for (int i = high; i > low; i--) {
            if (*(arr[down]) < pivot) {
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

inline void quickSort(const vector<int*>& arr, const int low, const int high) {
    if (low < high) {
        const int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot-1);
        quickSort(arr, pivot+1, high);
    }
}

#endif //COP3530_PROJECT_2_LOL_GAME_STATS_QUICKSORT_H
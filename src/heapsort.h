//
// Created by kingd on 11/4/2025.
//

#ifndef COP3530_PROJECT_2_LOL_GAME_STATS_HEAPSORT_H
#define COP3530_PROJECT_2_LOL_GAME_STATS_HEAPSORT_H

#include <vector>
#include "LOLGameData.h"
using namespace std;

template <class Compare>
void LOLHeapSort(vector<LOLGame*> data, Compare comp);

template <class Compare>
void LOLheapify(vector<LOLGame*> arr, int size, int pos, Compare comp);

template<class Compare>
void LOLHeapSort(vector<LOLGame *> arr, Compare comp) {
    const int n = arr.size();

    // build heap in-place
    for (int i = n / 2 - 1; i >= 0; i--) {
        LOLheapify(arr, n, i, comp);
    }

    // extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        LOLheapify(arr, i, 0, comp);
    }
}

template<class Compare>
void LOLheapify(vector<LOLGame *> arr, int size, int pos, Compare comp) {
    int max_pos = pos;
    const int left = 2 * pos + 1;
    const int right = 2 * pos + 2;

    if (left < size && arr[left] > arr[max_pos]) {
        max_pos = left;
    }
    if (right < size && arr[right] > arr[max_pos]) {
        max_pos = right;
    }
    if (max_pos != pos) {
        swap(arr[pos], arr[max_pos]);
        LOLheapify(arr, size, max_pos, comp);
    }
}

inline void heapify(vector<int>& arr, int size, int pos) {
    int max_pos = pos;
    const int left = 2 * pos + 1;
    const int right = 2 * pos + 2;

    if (left < size && arr[left] > arr[max_pos]) {
        max_pos = left;
    }
    if (right < size && arr[right] > arr[max_pos]) {
        max_pos = right;
    }
    if (max_pos != pos) {
        swap(arr[pos], arr[max_pos]);
        heapify(arr, size, max_pos);
    }
}

inline void myHeapSort(vector<int>& arr) {
    const int n = arr.size();

    // build heap in-place
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

#endif //COP3530_PROJECT_2_LOL_GAME_STATS_HEAPSORT_H
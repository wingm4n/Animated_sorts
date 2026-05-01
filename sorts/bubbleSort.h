#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_

#include <iterator>
#include <algorithm>

template <typename RandomAccessIterator>
void bubbleSort(RandomAccessIterator begin, RandomAccessIterator end) {
    bool swapped = true;
    while (begin != end-- && swapped) {
        swapped = false;
        for (auto i = begin; i != end; ++i) {
            if (*(i + 1) < *i) {
                std::iter_swap(i, i + 1);
                swapped = true;
            }
        }
    }
}

#endif
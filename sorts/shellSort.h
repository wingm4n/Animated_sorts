#ifndef SHELLSORT_H_
#define SHELLSORT_H_

#include <iterator>
#include <algorithm>

template <typename RandomAccessIterator>
void shellSort(RandomAccessIterator begin, RandomAccessIterator end) {
    using diff_t = typename std::iterator_traits<RandomAccessIterator>::difference_type;
    diff_t n = end - begin;
    
    diff_t gaps[8] = {701, 301, 132, 57, 23, 10, 4, 1}; // Ciura gap sequence
    for (diff_t gap : gaps){
        for (diff_t i = gap; i < n; i++){
            for (diff_t j = i; (j >= gap) && (*(begin + (j - gap)) > *(begin + j)); j -= gap){
                std::iter_swap(begin + (j - gap), begin + j);
            }
        }
    }
}

#endif // SHELLSORT_H_

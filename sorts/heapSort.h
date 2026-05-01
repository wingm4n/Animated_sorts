#ifndef HEAPSORT_H_
#define HEAPSORT_H_

#include <iterator>
#include <algorithm>

template <typename RandomAccessIterator>
void sift(RandomAccessIterator heap_start,  
          typename std::iterator_traits<RandomAccessIterator>::difference_type heap_size, 
          typename std::iterator_traits<RandomAccessIterator>::difference_type root_idx) {
    using diff_t   = typename std::iterator_traits<RandomAccessIterator>::difference_type;
    typename std::iterator_traits<RandomAccessIterator>::value_type val = *(heap_start + root_idx);
    diff_t max_child = root_idx * 2 + 1;
    if (max_child + 1 < heap_size 
        && *(heap_start + max_child) < *(heap_start + max_child + 1))
        ++max_child;
    
    while (max_child < heap_size && val < *(heap_start + max_child)){
        std::iter_swap(heap_start + max_child, heap_start + root_idx);
        root_idx = max_child;
        max_child  = max_child * 2 + 1;
        if (max_child + 1 < heap_size 
            && *(heap_start + max_child) < *(heap_start + max_child + 1))
            ++max_child;
    }
}

template <typename RandomAccessIterator>
void heapSort(RandomAccessIterator first, RandomAccessIterator last) {
    using diff_t   = typename std::iterator_traits<RandomAccessIterator>::difference_type;
    diff_t n = std::distance(first, last);
    if (n <= 1) return;

    for (diff_t i = n / 2 - 1; i >= 0; --i)
        sift(first, n, i);

    for (diff_t right = n - 1; right > 0; --right) {
        std::iter_swap(first, first + right);
        sift(first, right, 0);
    }
}

#endif
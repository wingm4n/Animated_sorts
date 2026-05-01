#ifndef COCKTAILSORT_H_
#define COCKTAILSORT_H_

#include <iterator>
#include <algorithm>

template<class _RandomIt>
void cocktailSort(_RandomIt first, _RandomIt last) {
    if (first == last) return;

    auto size = last - first;
    if (size <= 1) return;

    _RandomIt left = first;
    _RandomIt right = last - 1;

    while (left < right) {
        // Forward pass
        _RandomIt newRight = left;
        for (_RandomIt walker = left; walker < right; ++walker) {
            if (*walker > *(walker + 1)) {
                std::iter_swap(walker, walker + 1);
                newRight = walker;
            }
        }
        right = newRight;

        if (left >= right) break;

        // Backward pass
        _RandomIt newLeft = right;
        for (_RandomIt walker = right; walker > left; --walker) {
            if (*(walker - 1) > *walker) {
                std::iter_swap(walker - 1, walker);
                newLeft = walker;
            }
        }
        left = newLeft;
    }
}

#endif
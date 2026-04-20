#ifndef COCKTAILSORT_H_
#define COCKTAILSORT_H_
#include <iostream>

template< class _RandomIt > void cocktailSort( _RandomIt first, _RandomIt last ){
    last--;
    while (first <= last) {
        _RandomIt newLast = first;
        _RandomIt newFirst = last;
        for (_RandomIt walker = first; walker < last; walker++){
            if (*walker > *(walker + 1)){
                std::swap(*walker, *(walker + 1));
                newFirst = walker;
            }
        }
        last = newFirst - 1;
        
        for (_RandomIt walker = last; walker >= first; walker--){
            if (*walker > *(walker + 1)){
                std::swap(*walker, *(walker + 1));
                newLast = walker;
            }
        }
        first = newLast + 1;
    }
    return;
}

#endif
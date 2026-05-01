#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <algorithm>
#include "SortingAlgorithm.h"
#include "sorts\heapSort.h"

class HeapSort : public SortingAlgorithm
{
public:
    void sort(SortingVisualizer::VisualIterator begin,
              SortingVisualizer::VisualIterator end) override
    {
        ::heapSort(begin, end);
    }

    QString name() const override { return "HeapSort"; }
};

#endif // HEAPSORT_H_

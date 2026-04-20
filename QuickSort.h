#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "SortingAlgorithm.h"
#include <algorithm>

class QuickSort : public SortingAlgorithm
{
public:
    void sort(SortingVisualizer::VisualIterator begin,
              SortingVisualizer::VisualIterator end) override
    {
        std::sort(begin, end);
    }

    QString name() const override { return "Quick Sort"; }
};

#endif
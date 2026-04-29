#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm>
#include "SortingAlgorithm.h"

class QuickSort : public SortingAlgorithm
{
public:
    void sort(SortingVisualizer::VisualIterator begin,
              SortingVisualizer::VisualIterator end) override
    {
        std::sort(begin, end);
    }

    QString name() const override { return "QuickSort"; }
};

#endif
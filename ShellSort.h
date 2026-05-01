#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <algorithm>
#include "SortingAlgorithm.h"
#include "sorts\shellSort.h"

class ShellSort : public SortingAlgorithm
{
public:
    void sort(SortingVisualizer::VisualIterator begin,
              SortingVisualizer::VisualIterator end) override
    {
        ::shellSort(begin, end);
    }

    QString name() const override { return "ShellSort"; }
};

#endif // SHELLSORT_H

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <algorithm>
#include "SortingAlgorithm.h"
#include "sorts\bubbleSort.h"

class BubbleSort : public SortingAlgorithm
{
public:
    void sort(SortingVisualizer::VisualIterator begin,
              SortingVisualizer::VisualIterator end) override
    {
        ::bubbleSort(begin, end);
    }

    QString name() const override { return "BubbleSort"; }
};

#endif // BUBBLESORT_H

#ifndef COCKTAILSORT_H
#define COCKTAILSORT_H

#include "SortingAlgorithm.h"
#include <algorithm>
#include "sorts\cocktailSort.h"

class CocktailSort : public SortingAlgorithm
{
public:
    void sort(SortingVisualizer::VisualIterator begin,
              SortingVisualizer::VisualIterator end) override
    {
        // Using std::sort for now, but you can implement actual bubble sort later
        ::cocktailSort(begin, end);
    }

    QString name() const override { return "CocktailSort"; }
};

#endif
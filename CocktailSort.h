#ifndef COCKTAILSORT_H
#define COCKTAILSORT_H

#include <algorithm>
#include "SortingAlgorithm.h"
#include "sorts\cocktailSort.h"

class CocktailSort : public SortingAlgorithm
{
public:
    void sort(SortingVisualizer::VisualIterator begin,
              SortingVisualizer::VisualIterator end) override
    {
        ::cocktailSort(begin, end);
    }

    QString name() const override { return "CocktailSort"; }
};

#endif
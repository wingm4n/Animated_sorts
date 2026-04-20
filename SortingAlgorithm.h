#ifndef SORTINGALGORITHM_H
#define SORTINGALGORITHM_H

#include <functional>
#include "SortingVisualizer.h"

class SortingAlgorithm
{
public:
    virtual ~SortingAlgorithm() = default;
    virtual void sort(SortingVisualizer::VisualIterator begin,
                      SortingVisualizer::VisualIterator end) = 0;
    virtual QString name() const = 0;
};

#endif
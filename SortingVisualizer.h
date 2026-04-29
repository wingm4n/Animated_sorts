#ifndef SORTINGVISUALIZER_H
#define SORTINGVISUALIZER_H

#include <QWidget>
#include <vector>
#include <QColor>
#include <QThread>
#include <QApplication>
#include <QDebug>

class SortingAlgorithm;

class SortingVisualizer : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int animationDelay READ animationDelay WRITE setAnimationDelay)

public:
    explicit SortingVisualizer(QWidget *parent = nullptr);

    // Iterator class defined inside, but implementation in .cpp
    class VisualIterator;

    void generateRandomData(int count = 50);
    void setAnimationDelay(int ms);
    int animationDelay() const { return m_animationDelay; }

public slots:
    void startSort();
    void sortWithAlgorithm(SortingAlgorithm* algorithm);
    void shuffleData();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<int> m_data;
    std::vector<QColor> m_colors;
    int m_animationDelay = 50; // ms

    void generateGradientColors();
    QColor getColorForValue(int value, int maxValue) const;

    friend class VisualIterator;
    friend void std::iter_swap<SortingVisualizer::VisualIterator, SortingVisualizer::VisualIterator>(
        SortingVisualizer::VisualIterator a, SortingVisualizer::VisualIterator b);
};

// Iterator definition
class SortingVisualizer::VisualIterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = int*;
    using reference = int&;

    std::vector<int>::iterator it;
    SortingVisualizer* widget;

    VisualIterator(std::vector<int>::iterator iter, SortingVisualizer* w);

    reference operator*() const;
    pointer operator->() const;
    VisualIterator& operator++();
    VisualIterator operator++(int);
    VisualIterator& operator--();
    VisualIterator operator--(int);
    VisualIterator& operator+=(difference_type n);
    VisualIterator& operator-=(difference_type n);
    VisualIterator operator+(difference_type n) const;
    VisualIterator operator-(difference_type n) const;
    difference_type operator-(const VisualIterator& other) const;
    reference operator[](difference_type n) const;

    bool operator==(const VisualIterator& other) const;
    bool operator!=(const VisualIterator& other) const;
    bool operator<(const VisualIterator& other) const;
    bool operator>(const VisualIterator& other) const;
    bool operator<=(const VisualIterator& other) const;
    bool operator>=(const VisualIterator& other) const;
};

// Custom swap for std::sort
namespace std {
template<>
inline void iter_swap<SortingVisualizer::VisualIterator, SortingVisualizer::VisualIterator>(
    SortingVisualizer::VisualIterator a,
    SortingVisualizer::VisualIterator b)
{
    if (!a.widget || !b.widget) return;

    // Get indices
    size_t idxA = a.it - a.widget->m_data.begin();
    size_t idxB = b.it - b.widget->m_data.begin();

    // Swap values
    std::swap(*a.it, *b.it);

    // Swap colors
    std::swap(a.widget->m_colors[idxA], a.widget->m_colors[idxB]);


    // Trigger visualization update
    a.widget->update();
    QApplication::processEvents();
    QThread::msleep(a.widget->animationDelay());
}
}

#endif // SORTINGVISUALIZER_H
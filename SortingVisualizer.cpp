#include <QPainter>
#include <QPainterPath>
#include <random>
#include <algorithm>
#include <chrono>
#include "SortingAlgorithm.h"
#include "SortingVisualizer.h"

SortingVisualizer::SortingVisualizer(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(400, 300);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // Add this line
    generateRandomData(50);
}

// VisualIterator implementation
SortingVisualizer::VisualIterator::VisualIterator(std::vector<int>::iterator iter, SortingVisualizer* w)
    : it(iter), widget(w) {}

SortingVisualizer::VisualIterator::reference SortingVisualizer::VisualIterator::operator*() const { return *it; }
SortingVisualizer::VisualIterator::pointer SortingVisualizer::VisualIterator::operator->() const { return &(*it); }

SortingVisualizer::VisualIterator& SortingVisualizer::VisualIterator::operator++() { ++it; return *this; }
SortingVisualizer::VisualIterator SortingVisualizer::VisualIterator::operator++(int) { VisualIterator tmp = *this; ++it; return tmp; }
SortingVisualizer::VisualIterator& SortingVisualizer::VisualIterator::operator--() { --it; return *this; }
SortingVisualizer::VisualIterator SortingVisualizer::VisualIterator::operator--(int) { VisualIterator tmp = *this; --it; return tmp; }

SortingVisualizer::VisualIterator& SortingVisualizer::VisualIterator::operator+=(difference_type n) { it += n; return *this; }
SortingVisualizer::VisualIterator& SortingVisualizer::VisualIterator::operator-=(difference_type n) { it -= n; return *this; }
SortingVisualizer::VisualIterator SortingVisualizer::VisualIterator::operator+(difference_type n) const { return VisualIterator(it + n, widget); }
SortingVisualizer::VisualIterator SortingVisualizer::VisualIterator::operator-(difference_type n) const { return VisualIterator(it - n, widget); }

SortingVisualizer::VisualIterator::difference_type SortingVisualizer::VisualIterator::operator-(const VisualIterator& other) const { return it - other.it; }

SortingVisualizer::VisualIterator::reference SortingVisualizer::VisualIterator::operator[](difference_type n) const { return it[n]; }

bool SortingVisualizer::VisualIterator::operator==(const VisualIterator& other) const { return it == other.it; }
bool SortingVisualizer::VisualIterator::operator!=(const VisualIterator& other) const { return it != other.it; }
bool SortingVisualizer::VisualIterator::operator<(const VisualIterator& other) const { return it < other.it; }
bool SortingVisualizer::VisualIterator::operator>(const VisualIterator& other) const { return it > other.it; }
bool SortingVisualizer::VisualIterator::operator<=(const VisualIterator& other) const { return it <= other.it; }
bool SortingVisualizer::VisualIterator::operator>=(const VisualIterator& other) const { return it >= other.it; }

void SortingVisualizer::generateRandomData(int count)
{
    m_data.resize(count);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(10, 100);

    for (int& val : m_data) {
        val = dis(gen);
    }

    generateGradientColors();
    update();
}

void SortingVisualizer::generateGradientColors()
{
    if (m_data.empty()) return;

    int maxVal = *std::max_element(m_data.begin(), m_data.end());
    m_colors.resize(m_data.size());

    // Assign color based on VALUE, not position
    for (size_t i = 0; i < m_data.size(); ++i) {
        m_colors[i] = getColorForValue(m_data[i], maxVal);
    }
}

QColor SortingVisualizer::getColorForValue(int value, int maxValue) const
{
    double ratio = static_cast<double>(value) / maxValue;

    // Smooth gradient from teal (low) to coral (high)
    int r = static_cast<int>(52 + ratio * 203);   // 52 -> 255
    int g = static_cast<int>(199 + ratio * 56);   // 199 -> 255
    int b = static_cast<int>(199 - ratio * 114);  // 199 -> 85

    return QColor(r, g, b);
}

void SortingVisualizer::setAnimationDelay(int ms)
{
    m_animationDelay = std::max(0, ms);
}

void SortingVisualizer::startSort()
{
    VisualIterator begin(m_data.begin(), this);
    VisualIterator end(m_data.end(), this);

    std::sort(begin, end);

    // generateGradientColors();
    // update();

    generateGradientColors();
    repaint();  // Force immediate repaint
    QApplication::processEvents();
}

void SortingVisualizer::shuffleData()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(m_data.begin(), m_data.end(), std::mt19937(seed));
    generateGradientColors();
    update();
}

void SortingVisualizer::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    if (m_data.empty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int height = this->height();

    // Margins
    int margin = 20;
    int chartWidth = width - 2 * margin;
    int chartHeight = height - 2 * margin;

    int maxVal = *std::max_element(m_data.begin(), m_data.end());
    double barWidth = static_cast<double>(chartWidth) / m_data.size();

    // Draw background
    painter.fillRect(rect(), QColor(30, 30, 46));

    // Draw bars
    for (size_t i = 0; i < m_data.size(); ++i) {
        double barHeight = (static_cast<double>(m_data[i]) / maxVal) * chartHeight;
        double x = margin + i * barWidth;
        double y = height - margin - barHeight;

        QPainterPath path;
        path.addRoundedRect(QRectF(x, y, barWidth - 2, barHeight), 4, 4);

        painter.fillPath(path, m_colors[i]);

        // Subtle border
        painter.setPen(QPen(QColor(255, 255, 255, 20), 1));
        painter.drawPath(path);
    }

    // Draw baseline
    painter.setPen(QPen(QColor(255, 255, 255, 40), 1));
    painter.drawLine(margin, height - margin, width - margin, height - margin);
}

void SortingVisualizer::sortWithAlgorithm(SortingAlgorithm* algorithm)
{
    if (!algorithm) return;

    VisualIterator begin(m_data.begin(), this);
    VisualIterator end(m_data.end(), this);

    algorithm->sort(begin, end);

    // generateGradientColors();
    // update();

    generateGradientColors();
    repaint();  // Force immediate repaint
    QApplication::processEvents();
}

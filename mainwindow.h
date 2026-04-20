#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include "SortingVisualizer.h"
#include <QComboBox>
#include <vector>
#include <memory>
#include "SortingAlgorithm.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // For frameless window dragging
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void onMinimizeClicked();
    void onMaximizeClicked();
    void onCloseClicked();

private:
    void setupUi();
    void setupTitleBar();
    void applyStyle();

    // UI Components
    QWidget *centralWidget;
    QWidget *titleBar;
    QWidget *navBar;
    QStackedWidget *contentStack;
    SortingVisualizer *largeWidget;

    // Title bar buttons
    QPushButton *btnMinimize;
    QPushButton *btnMaximize;
    QPushButton *btnClose;

    // Dragging state
    bool m_dragging = false;
    QPoint m_dragPosition;
    bool m_maximized = false;

    QComboBox *algorithmComboBox;
    std::vector<std::unique_ptr<SortingAlgorithm>> m_algorithms;
    SortingAlgorithm* currentAlgorithm() const;

    void registerAlgorithms();
};

#endif // MAINWINDOW_H
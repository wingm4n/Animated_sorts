# Animated_sorts
This repository contains different sorting algorithms implemented in C++ and a visual shell to run them.

# Interface
![](https://github.com/wingm4n/Animated_sorts/blob/main/Sort_visualizer_GIF.gif)

# Adding your own sort
1. Add the source code (header file) to "sorts/" 
2. Create the adapted version in the root directory (take BubbleSort.h as the example)
3. Include the adapted header into MainWindow.cpp (`#include "BubbleSort.h"`)
4. Push an instance inside MainWindow::registerAlgorithms() (`m_algorithms.push_back(std::make_unique<BubbleSort>());`)
5. Edit resources.qrc by adding source code (`<file alias="bubbleSort.h">sorts/bubbleSort.h</file>`)
6. Add to the the picker in void MainWindow::setupAnalyticsPage() (`algoSourceFiles["BubbleSort"]    = ":/source/bubbleSort.h";`)
7. Update the build system files and rebuild

This application uses Qt 6.
Qt is available under the LGPL v3 license:
https://www.qt.io/licensing/

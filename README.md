# Animated sorts
This repository contains different sorting algorithms implemented in C++ (iterators approach - standard for STL algorithms) \
and a visual shell to run them smoothly on your PC. \
Pick a sort (or add your own!), set visualization speed and more.\
\
Inspired by Wikipedia's sorting algorithms visualizations.

# Interface
<img width="800" height="548" alt="shellsort" src="https://github.com/user-attachments/assets/cf401264-4c73-436b-9af2-42a5b9eb6f1f" />
<img width="800" height="548" alt="image" src="https://github.com/user-attachments/assets/b00bb039-d2a6-4dc6-9266-131dc3ffb80f" />
<img width="800" height="548" alt="image" src="https://github.com/user-attachments/assets/bf21b93e-d246-41ae-a11e-0a1aa85e4857" />



# Adding your own sort
1. Add the source code (header file) to "sorts/" 
2. Create the adapted version in the root directory (take BubbleSort.h as the example)
3. Include the adapted header into MainWindow.cpp (`#include "BubbleSort.h"`)
4. Push an instance inside MainWindow::registerAlgorithms() (`m_algorithms.push_back(std::make_unique<BubbleSort>());`)
5. Edit resources.qrc by adding source code (`<file alias="bubbleSort.h">sorts/bubbleSort.h</file>`)
6. Add to the the picker in void MainWindow::setupAnalyticsPage() (`algoSourceFiles["BubbleSort"]    = ":/source/bubbleSort.h";`)
7. Update the build system files and rebuild

# License
This application uses Qt 6.
Qt is available under the LGPL v3 license:
https://www.qt.io/licensing/

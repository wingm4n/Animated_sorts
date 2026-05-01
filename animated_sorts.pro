QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SortingVisualizer.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BubbleSort.h \
    HeapSort.h \
    QuickSort.h \
    CocktailSort.h \
    ShellSort.h \
    SortingAlgorithm.h \
    SortingVisualizer.h \
    HeapSort.h \
    mainwindow.h \
    sorts/bubbleSort.h \
    sorts/heapSort.h \
    sorts/cocktailSort.h \
    sorts/shellSort.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    styles/style.qss

RESOURCES += \
    resources.qrc

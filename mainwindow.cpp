#include "MainWindow.h"
#include <QFile>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QSpinBox>
#include "CocktailSort.h"
#include "QuickSort.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window flags for frameless window
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    setAttribute(Qt::WA_TranslucentBackground);

    setupUi();
    setupTitleBar();
    applyStyle();

    // Set default size
    resize(1100, 750);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi()
{
    // Root container with rounded corners
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("CentralWidget");
    setCentralWidget(centralWidget);

    // Main vertical layout (contains title bar + horizontal split)
    QVBoxLayout *rootLayout = new QVBoxLayout(centralWidget);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    // Placeholder for title bar (will be replaced in setupTitleBar)
    titleBar = new QWidget(this);
    titleBar->setObjectName("TitleBar");
    titleBar->setFixedHeight(40);

    // Horizontal layout for navigation + content
    QWidget *mainContent = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainContent);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // --- NAVIGATION BAR ---
    navBar = new QWidget(this);
    navBar->setObjectName("NavBar");
    navBar->setFixedWidth(240);

    QVBoxLayout *navLayout = new QVBoxLayout(navBar);
    navLayout->setSpacing(8);
    navLayout->setContentsMargins(16, 24, 16, 24);

    // Navigation header
    QLabel *navHeader = new QLabel("MENU");
    navHeader->setObjectName("NavHeader");
    navHeader->setStyleSheet("color: #6c7086; font-size: 11px; font-weight: bold; padding-left: 12px; margin-bottom: 8px;");
    navLayout->addWidget(navHeader);

    // Navigation buttons
    QPushButton *btnHome = new QPushButton("🏠 Dashboard");
    QPushButton *btnAnalytics = new QPushButton("📊 Analytics");
    QPushButton *btnReports = new QPushButton("📈 Reports");
    QPushButton *btnSettings = new QPushButton("⚙️ Settings");

    // Make buttons checkable for visual feedback
    btnHome->setCheckable(true);
    btnAnalytics->setCheckable(true);
    btnReports->setCheckable(true);
    btnSettings->setCheckable(true);

    btnHome->setChecked(true);

    navLayout->addWidget(btnHome);
    navLayout->addWidget(btnAnalytics);
    navLayout->addWidget(btnReports);
    navLayout->addWidget(btnSettings);
    navLayout->addStretch();

    // Bottom section of nav bar (could contain user profile, etc.)
    QLabel *versionLabel = new QLabel("v1.0.0");
    versionLabel->setObjectName("VersionLabel");
    versionLabel->setStyleSheet("color: #45475a; font-size: 11px; padding: 8px;");
    versionLabel->setAlignment(Qt::AlignCenter);
    navLayout->addWidget(versionLabel);

    // --- CONTENT STACK ---
    contentStack = new QStackedWidget(this);
    contentStack->setObjectName("ContentArea");

    // Page 0: Dashboard (Large Widget)
    QWidget *dashboardPage = new QWidget();
    QVBoxLayout *dashboardLayout = new QVBoxLayout(dashboardPage);
    dashboardLayout->setContentsMargins(32, 32, 32, 32);
    dashboardLayout->setSpacing(16);

    // Control buttons
    QWidget *controlsWidget = new QWidget();
    QHBoxLayout *controlsLayout = new QHBoxLayout(controlsWidget);
    controlsLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton *btnSort = new QPushButton("Sort");
    QPushButton *btnShuffle = new QPushButton("Shuffle");
    QPushButton *btnGenerate = new QPushButton("New Data");
    QSpinBox *delaySpin = new QSpinBox();
    algorithmComboBox = new QComboBox();

    algorithmComboBox->setStyleSheet(R"(
    QComboBox {
        background-color: #313244;
        color: #cdd6f4;
        border: 1px solid #45475a;
        border-radius: 6px;
        padding: 6px 12px;
        min-width: 150px;
    }
    QComboBox:hover {
        background-color: #45475a;
    }
    QComboBox::drop-down {
        border: none;
    }
    QComboBox::down-arrow {
        image: none;
        border-left: 5px solid transparent;
        border-right: 5px solid transparent;
        border-top: 5px solid #cdd6f4;
        margin-right: 8px;
    }
    QComboBox QAbstractItemView {
        background-color: #313244;
        color: #cdd6f4;
        border: 1px solid #45475a;
        selection-background-color: #89b4fa;
        selection-color: #1e1e2e;
    }
)");

    delaySpin->setRange(0, 500);
    delaySpin->setValue(50);
    delaySpin->setSuffix(" ms");

    controlsLayout->addWidget(btnSort);
    controlsLayout->addWidget(btnShuffle);
    controlsLayout->addWidget(btnGenerate);
    controlsLayout->addWidget(algorithmComboBox);
    controlsLayout->addStretch();
    controlsLayout->addWidget(new QLabel(""));
    controlsLayout->addWidget(delaySpin);

    // Style the controls
    QString controlStyle = R"(
    QPushButton {
        background-color: #313244;
        color: #cdd6f4;
        border: none;
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 13px;
    }
    QPushButton:hover {
        background-color: #45475a;
    }
    QSpinBox {
        background-color: #313244;
        color: #cdd6f4;
        border: 1px solid #45475a;
        border-radius: 6px;
        padding: 6px;
    }
)";
    btnSort->setStyleSheet(controlStyle);
    btnShuffle->setStyleSheet(controlStyle);
    btnGenerate->setStyleSheet(controlStyle);
    delaySpin->setStyleSheet(controlStyle);

    dashboardLayout->addWidget(controlsWidget);

    // Visualizer widget
    largeWidget = new SortingVisualizer(this);
    dashboardLayout->addWidget(largeWidget, 1);  // '1' makes it expand

    // Connect buttons
    connect(btnSort, &QPushButton::clicked, this, [this]() {
        if (auto* algo = currentAlgorithm()) {
            largeWidget->sortWithAlgorithm(algo);
        }
    });
    connect(btnShuffle, &QPushButton::clicked, largeWidget, &SortingVisualizer::shuffleData);
    connect(btnGenerate, &QPushButton::clicked, [this]() {
        largeWidget->generateRandomData(50);
    });
    connect(delaySpin, QOverload<int>::of(&QSpinBox::valueChanged),
            largeWidget, &SortingVisualizer::setAnimationDelay);

    // Add to stack
    contentStack->addWidget(dashboardPage);




    btnSort->setStyleSheet(controlStyle);
    btnShuffle->setStyleSheet(controlStyle);
    btnGenerate->setStyleSheet(controlStyle);
    delaySpin->setStyleSheet(controlStyle);

    controlsLayout->addWidget(btnSort);
    controlsLayout->addWidget(btnShuffle);
    controlsLayout->addWidget(btnGenerate);
    controlsLayout->addStretch();
    QLabel *delayLabel = new QLabel("Delay:");
    delayLabel->setStyleSheet("color: #cdd6f4; font-size: 13px;");
    controlsLayout->addWidget(delayLabel);
    controlsLayout->addWidget(delaySpin);

    dashboardLayout->addWidget(controlsWidget);

    // Connect controls to visualizer
    connect(btnSort, &QPushButton::clicked, largeWidget, &SortingVisualizer::startSort);
    connect(btnShuffle, &QPushButton::clicked, largeWidget, &SortingVisualizer::shuffleData);
    connect(btnGenerate, &QPushButton::clicked, [this]() {
        largeWidget->generateRandomData(50);
    });
    connect(delaySpin, QOverload<int>::of(&QSpinBox::valueChanged),
            largeWidget, &SortingVisualizer::setAnimationDelay);

    QLabel *welcomeLabel = new QLabel("Ready to see some magic?");
    welcomeLabel->setObjectName("WelcomeLabel");
    welcomeLabel->setStyleSheet("color: #cdd6f4; font-size: 28px; font-weight: bold;");

    QLabel *subtitleLabel = new QLabel("Choose a sorting algorithm, then watch it do its job");
    subtitleLabel->setStyleSheet("color: #6c7086; font-size: 14px; margin-bottom: 32px;");


    dashboardLayout->addWidget(welcomeLabel);
    dashboardLayout->addWidget(subtitleLabel);
    dashboardLayout->addStretch();

    // Page 1: Analytics (Placeholder)
    QWidget *analyticsPage = new QWidget();
    QVBoxLayout *analyticsLayout = new QVBoxLayout(analyticsPage);
    analyticsLayout->setContentsMargins(32, 32, 32, 32);
    QLabel *analyticsLabel = new QLabel("Analytics Dashboard");
    analyticsLabel->setStyleSheet("color: #cdd6f4; font-size: 24px; font-weight: bold;");
    analyticsLayout->addWidget(analyticsLabel);
    analyticsLayout->addStretch();

    // Page 2: Reports (Placeholder)
    QWidget *reportsPage = new QWidget();
    QVBoxLayout *reportsLayout = new QVBoxLayout(reportsPage);
    reportsLayout->setContentsMargins(32, 32, 32, 32);
    QLabel *reportsLabel = new QLabel("Reports");
    reportsLabel->setStyleSheet("color: #cdd6f4; font-size: 24px; font-weight: bold;");
    reportsLayout->addWidget(reportsLabel);
    reportsLayout->addStretch();

    // Page 3: Settings (Placeholder)
    QWidget *settingsPage = new QWidget();
    QVBoxLayout *settingsLayout = new QVBoxLayout(settingsPage);
    settingsLayout->setContentsMargins(32, 32, 32, 32);
    QLabel *settingsLabel = new QLabel("Settings");
    settingsLabel->setStyleSheet("color: #cdd6f4; font-size: 24px; font-weight: bold;");
    settingsLayout->addWidget(settingsLabel);
    settingsLayout->addStretch();

    // Add pages to stack
    contentStack->addWidget(analyticsPage);
    contentStack->addWidget(reportsPage);
    contentStack->addWidget(settingsPage);

    // Connect navigation buttons
    connect(btnHome, &QPushButton::clicked, [this, btnHome, btnAnalytics, btnReports, btnSettings]() {
        contentStack->setCurrentIndex(0);
        btnHome->setChecked(true);
        btnAnalytics->setChecked(false);
        btnReports->setChecked(false);
        btnSettings->setChecked(false);
    });

    connect(btnAnalytics, &QPushButton::clicked, [this, btnHome, btnAnalytics, btnReports, btnSettings]() {
        contentStack->setCurrentIndex(1);
        btnHome->setChecked(false);
        btnAnalytics->setChecked(true);
        btnReports->setChecked(false);
        btnSettings->setChecked(false);
    });

    connect(btnReports, &QPushButton::clicked, [this, btnHome, btnAnalytics, btnReports, btnSettings]() {
        contentStack->setCurrentIndex(2);
        btnHome->setChecked(false);
        btnAnalytics->setChecked(false);
        btnReports->setChecked(true);
        btnSettings->setChecked(false);
    });

    connect(btnSettings, &QPushButton::clicked, [this, btnHome, btnAnalytics, btnReports, btnSettings]() {
        contentStack->setCurrentIndex(3);
        btnHome->setChecked(false);
        btnAnalytics->setChecked(false);
        btnReports->setChecked(false);
        btnSettings->setChecked(true);
    });

    // Assemble layout
    mainLayout->addWidget(navBar);
    mainLayout->addWidget(contentStack, 1);

    rootLayout->addWidget(titleBar);
    rootLayout->addWidget(mainContent, 1);
    registerAlgorithms();
}

void MainWindow::setupTitleBar()
{
    QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(16, 0, 8, 0);
    titleLayout->setSpacing(0);

    // Window icon (optional)
    QLabel *iconLabel = new QLabel();
    iconLabel->setPixmap(QPixmap(":/icons/app_icon.png").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setStyleSheet("margin-right: 8px;");

    // Window title
    QLabel *titleLabel = new QLabel("Animated sorts!");
    titleLabel->setObjectName("WindowTitle");
    titleLabel->setStyleSheet("color: #cdd6f4; font-size: 13px; font-weight: 500;");

    // Spacer to push buttons to the right
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Window control buttons
    btnMinimize = new QPushButton("─");
    btnMinimize->setObjectName("MinimizeButton");
    btnMinimize->setFixedSize(40, 30);
    btnMinimize->setStyleSheet(R"(
        QPushButton#MinimizeButton {
            background: transparent;
            color: #cdd6f4;
            border: none;
            border-radius: 6px;
            font-size: 16px;
            font-weight: bold;
        }
        QPushButton#MinimizeButton:hover {
            background: #313244;
        }
    )");

    btnMaximize = new QPushButton("□");
    btnMaximize->setObjectName("MaximizeButton");
    btnMaximize->setFixedSize(40, 30);
    btnMaximize->setStyleSheet(R"(
        QPushButton#MaximizeButton {
            background: transparent;
            color: #cdd6f4;
            border: none;
            border-radius: 6px;
            font-size: 14px;
            font-weight: bold;
        }
        QPushButton#MaximizeButton:hover {
            background: #313244;
        }
    )");

    btnClose = new QPushButton("✕");
    btnClose->setObjectName("CloseButton");
    btnClose->setFixedSize(40, 30);
    btnClose->setStyleSheet(R"(
        QPushButton#CloseButton {
            background: transparent;
            color: #cdd6f4;
            border: none;
            border-radius: 6px;
            font-size: 14px;
            font-weight: bold;
        }
        QPushButton#CloseButton:hover {
            background: #f38ba8;
            color: #1e1e2e;
        }
    )");

    // Add widgets to title bar
    titleLayout->addWidget(iconLabel);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(spacer);
    titleLayout->addWidget(btnMinimize);
    titleLayout->addWidget(btnMaximize);
    titleLayout->addWidget(btnClose);

    // Connect button signals
    connect(btnMinimize, &QPushButton::clicked, this, &MainWindow::onMinimizeClicked);
    connect(btnMaximize, &QPushButton::clicked, this, &MainWindow::onMaximizeClicked);
    connect(btnClose, &QPushButton::clicked, this, &MainWindow::onCloseClicked);
}

void MainWindow::applyStyle()
{
    // Try to load from resources first
    QFile file(":/styles/style.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    } else {
        // Fallback embedded stylesheet
        QString fallbackStyle = R"(
            * {
                font-family: 'Segoe UI', sans-serif;
            }

            #CentralWidget {
                background-color: #1e1e2e;
                border-radius: 12px;
                border: 1px solid #313244;
            }

            #TitleBar {
                background-color: #181825;
                border-top-left-radius: 12px;
                border-top-right-radius: 12px;
            }

            #NavBar {
                background-color: #181825;
                border-bottom-left-radius: 12px;
            }

            #NavBar QPushButton {
                background-color: transparent;
                color: #cdd6f4;
                border: none;
                border-radius: 8px;
                padding: 12px 16px;
                text-align: left;
                font-size: 13px;
                font-weight: 500;
            }

            #NavBar QPushButton:hover {
                background-color: #313244;
            }

            #NavBar QPushButton:checked {
                background-color: #89b4fa;
                color: #1e1e2e;
            }

            #ContentArea {
                background-color: #1e1e2e;
                border-bottom-right-radius: 12px;
            }
        )";
        this->setStyleSheet(fallbackStyle);
    }
}

void MainWindow::onMinimizeClicked()
{
    showMinimized();
}

void MainWindow::onMaximizeClicked()
{
    if (m_maximized) {
        showNormal();
        btnMaximize->setText("□");
        m_maximized = false;
    } else {
        showMaximized();
        btnMaximize->setText("❐");
        m_maximized = true;
    }
}

void MainWindow::onCloseClicked()
{
    close();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && titleBar->underMouse()) {
        m_dragging = true;
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        if (m_maximized) {
            // Restore window if maximized before dragging
            onMaximizeClicked();
        }
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
        event->accept();
    }
}

void MainWindow::registerAlgorithms()
{
    m_algorithms.push_back(std::make_unique<CocktailSort>());
    m_algorithms.push_back(std::make_unique<QuickSort>());
    // Add more algorithms here

    for (const auto& algo : m_algorithms) {
        algorithmComboBox->addItem(algo->name());
    }
}

SortingAlgorithm* MainWindow::currentAlgorithm() const
{
    int index = algorithmComboBox->currentIndex();
    if (index >= 0 && index < static_cast<int>(m_algorithms.size())) {
        return m_algorithms[index].get();
    }
    return nullptr;
}
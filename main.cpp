#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QIcon>
#include <QScreen>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    // Enable High DPI scaling for modern displays
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);

    // Set application metadata
    app.setApplicationName("Animated Sort");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("wingm4n");

    // Load and set application font (optional - for consistent typography)
    QFont defaultFont("Segoe UI", 10);
    defaultFont.setStyleHint(QFont::SansSerif);
    app.setFont(defaultFont);

    // Set application icon (optional - provide your own .ico file)
    // app.setWindowIcon(QIcon(":/icons/app_icon.ico"));

    // Optional: Load custom font from resources
    // int fontId = QFontDatabase::addApplicationFont(":/fonts/Inter-Regular.ttf");
    // if (fontId != -1) {
    //     QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    //     QFont customFont(family, 10);
    //     app.setFont(customFont);
    // }

    // Create and show main window
    MainWindow mainWindow;

    // Center the window on the primary screen
    QScreen *screen = QApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - mainWindow.width()) / 2;
        int y = (screenGeometry.height() - mainWindow.height()) / 2;
        mainWindow.move(x, y);
    }

    mainWindow.show();

    // Optional: Apply additional global stylesheet that couldn't be in resources
    // This can be useful for system-wide theme detection
    /*
    QString globalStyle = R"(
        QToolTip {
            background-color: #313244;
            color: #cdd6f4;
            border: none;
            border-radius: 6px;
            padding: 6px;
        }

        QScrollBar:vertical {
            background: transparent;
            width: 8px;
            margin: 0;
            border-radius: 4px;
        }

        QScrollBar::handle:vertical {
            background: #45475a;
            border-radius: 4px;
            min-height: 20px;
        }

        QScrollBar::handle:vertical:hover {
            background: #6c7086;
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
    )";
    app.setStyleSheet(globalStyle);
    */

    app.setQuitOnLastWindowClosed(true);

    return app.exec();
}
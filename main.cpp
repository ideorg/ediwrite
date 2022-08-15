#include <QApplication>
#include <SingleApplication>
#include <QCommandLineParser>
#include <QScreen>

#include "codeeditor.h"
#include "MainWindow.h"
#include "raise.h"

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addPositionalArgument(QStringLiteral("source"), QStringLiteral("The source file to highlight."));
    parser.process(app);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();

    MainWindow mainWindow;
    QObject::connect( &app, &SingleApplication::instanceStarted, [ &mainWindow ]() {
        mainWindow.handleMessage();
    });
    mainWindow.resize(int(screenGeometry.width()*0.8), int(screenGeometry.height()*0.8));
    mainWindow.show();
    return app.exec();
}

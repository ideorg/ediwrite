#include <QApplication>
#include <SingleApplication>
#include <QCommandLineParser>
#include <QScreen>

#include "codeeditor.h"
#include "MainWindow.h"
#include "raise.h"

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv, true);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();

    MainWindow mainWindow;
    // If this is a secondary instance
    if( app.isSecondary() ) {
        app.sendMessage( app.arguments().join(' ').toUtf8() );
        return 0;
    } else {
        QObject::connect(
                &app,
                &SingleApplication::receivedMessage,
                &mainWindow,
                &MainWindow::receivedMessage
        );
    }
    for (int i=1; i<app.arguments().size(); i++)
        mainWindow.openOrActivate(app.arguments()[i]);
    mainWindow.resize(int(screenGeometry.width()*0.8), int(screenGeometry.height()*0.8));
    mainWindow.show();
    return app.exec();
}

/*
    SPDX-FileCopyrightText: 2016 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: MIT
*/

#include "codeeditor.h"
#include "MainWindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QScreen>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addPositionalArgument(QStringLiteral("source"), QStringLiteral("The source file to highlight."));
    parser.process(app);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();

    MainWindow mainWindow;
    mainWindow.resize(int(screenGeometry.width()*0.8), int(screenGeometry.height()*0.8));
    mainWindow.show();
    return app.exec();
}

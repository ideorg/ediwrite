/*
    SPDX-FileCopyrightText: 2016 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: MIT
*/

#include "codeeditor.h"

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
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    CodeEditor edit;
    edit.resize(int(screenGeometry.width()*0.8), int(screenGeometry.height()*0.8));
    edit.show();
    if (parser.positionalArguments().size() == 1) {
        edit.openFile(parser.positionalArguments().at(0));
    }
    return app.exec();
}

//
// Created by andrzej on 4/10/22.
//

#ifndef EDITWRITE_MAINWINDOW_H
#define EDITWRITE_MAINWINDOW_H

#include <QMainWindow>
#include "codeeditor.h"

class MainWindow: public QMainWindow {
public:
    MainWindow();
private:
    void createMenus();
    void openFile();
    void saveFile();
    CodeEditor edit;
};


#endif //EDITWRITE_MAINWINDOW_H

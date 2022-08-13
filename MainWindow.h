//
// Created by Andrzej Borucki on 2022-04-10
//

#ifndef EDITWRITE_MAINWINDOW_H
#define EDITWRITE_MAINWINDOW_H

#include <QMainWindow>
#include "codeeditor.h"
#include "UntitleCounter.h"

class MainWindow: public QMainWindow {
public:
    MainWindow();
private:
    UntitleCounter untitleCounter;
    void createMenus();
    void newFile();
    void openFile();
    bool saveFile();
    QTabWidget *tabWidget;
    void tryCloseTab(int index);
};


#endif //EDITWRITE_MAINWINDOW_H

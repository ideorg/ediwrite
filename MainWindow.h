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
private slots:
    void onTextChanged();
    void onTabChanged(int index);
private:
    UntitleCounter untitleCounter;
    CodeEditor *getEditorByPath(QString path);
    CodeEditor *openInEditor(QString path);
    void openOrActivate(QString path);

    void createMenus();
    void newFile();
    void openFile();
    bool saveFile();
    QTabWidget *tabWidget;
    void tryCloseTab(int index);
};


#endif //EDITWRITE_MAINWINDOW_H

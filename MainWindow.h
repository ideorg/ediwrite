//
// Created by Andrzej Borucki on 2022-04-10
//

#ifndef EDITWRITE_MAINWINDOW_H
#define EDITWRITE_MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "codeeditor.h"
#include "UntitleCounter.h"

class MainWindow: public QMainWindow {
public:
    MainWindow();
private slots:
    void onTextChanged();
    void onCursorPositionChanged();
    void onTabChanged(int index);
private:
    UntitleCounter untitleCounter;
    CodeEditor *getEditorByPath(QString path);
    CodeEditor *openInEditor(QString path);
    void openOrActivate(QString path);
    QLabel *m_statusLeft;
    QLabel *m_statusMiddle;
    QLabel *m_statusRight;

    void createMenus();
    void createStatusBar();
    void newFile();
    void openFile();
    bool saveFile();
    QTabWidget *tabWidget;
    void tryCloseTab(int index);

    CodeEditor* currentEditor();
    CodeEditor* selectedEditor(int index);
};


#endif //EDITWRITE_MAINWINDOW_H

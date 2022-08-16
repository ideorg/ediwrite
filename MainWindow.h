//
// Created by Andrzej Borucki on 2022-04-10
//

#ifndef EDITWRITE_MAINWINDOW_H
#define EDITWRITE_MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "codeeditor.h"
#include "UntitleCounter.h"
#include "CloseManager.h"

class MainWindow: public QMainWindow {
public:
    MainWindow();
    ~MainWindow() { delete closeManager;}
private slots:
    void onTextChanged();
    void onCursorPositionChanged();
    void onTabChanged(int index);
public slots:
    void handleMessage();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    enum CloseTab {Ignore, Accept};
    UntitleCounter untitleCounter;
    CloseManager *closeManager;
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
    bool saveFileToPath(CodeEditor* editor);
    bool save();
    bool saveAs();
    QTabWidget *tabWidget;
    CloseTab tryCloseTab(int index);

    CodeEditor* currentEditor();
    CodeEditor* selectedEditor(int index);
};


#endif //EDITWRITE_MAINWINDOW_H

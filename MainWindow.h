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
    void openOrActivate(QString path);
private slots:
    void onTextChanged();
    void onCursorPositionChanged();
    void onTabChanged(int index);
public slots:
    void receivedMessage(int instanceId, QByteArray message);
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    enum CloseTab {Ignore, Accept};
    UntitleCounter untitleCounter;
    CloseManager *closeManager;
    CodeEditor *getEditorByPath(QString path);
    CodeEditor *openInEditor(QString path);
    QLabel *m_statusLeft;
    QLabel *m_statusMiddle;
    QLabel *m_statusRight;

    void createMenus();
    void createStatusBar();
    void newFile();
    void openFile();
    void tryCloseCurrent();
    bool saveFileToPath(CodeEditor* editor);
    bool save();
    bool saveAs();
    QTabWidget *tabWidget;
    CloseTab tryCloseTab(int index);
    CloseTab tryCloseAll();

    CodeEditor* currentEditor();
    CodeEditor* selectedEditor(int index);
    bool eventFilter(QObject *target, QEvent *event) override;
    void activateTab(int index);
};


#endif //EDITWRITE_MAINWINDOW_H

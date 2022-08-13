//
// Created by Andrzej Borucki on 2022-04-10
//

#include "MainWindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QTabBar>
#include <QMessageBox>

MainWindow::MainWindow() {
    createMenus();
    tabWidget = new QTabWidget;
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    tabWidget->setTabPosition(QTabWidget::South);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this,
            [this](int index) {
                tryCloseTab(index);
            });
    setCentralWidget(tabWidget);
}

void MainWindow::tryCloseTab(int index) {
    QWidget *tab = tabWidget->widget(index);
    CodeEditor* editor = dynamic_cast<CodeEditor*>(tab);
    if (editor->document()->isModified())
    {
        QString message = "The text has been changed.\n";
        message += "Do you want to save the modifications? (No = close and discard changes)";
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Warning", message,
                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if (reply == QMessageBox::Cancel)
            return;
        if (reply == QMessageBox::Yes)
            if (!saveFile()) return;
    }
    tabWidget->removeTab(index);
}

void MainWindow::newFile()
{
    CodeEditor *editor = new CodeEditor();
    editor->untitleId = untitleCounter.getNextId();
    tabWidget->addTab(editor, editor->getTitle());
}

void MainWindow::openFile()
{
    QFileDialog dialog(this, tr("Open File"));
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    if (dialog.exec() == QDialog::Accepted) {
        QString fileName = dialog.selectedFiles().first();
        CodeEditor *editor = new CodeEditor();
        editor->path = fileName;
        tabWidget->addTab(editor, editor->getTitle());
        editor->openFile(fileName);
    }
}

bool MainWindow::saveFile()
{
    QFileDialog dialog(this, tr("Save File"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    if (dialog.exec() == QDialog::Accepted) {
        QString fileName = dialog.selectedFiles().first();
        QWidget *tab = tabWidget->currentWidget();
        CodeEditor* editor = dynamic_cast<CodeEditor*>(tab);
        editor->saveFile(fileName);
        return true;
    }
    return false;
}

void MainWindow::createMenus() {
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *editAct;
    QAction *removeAc;

    fileMenu = menuBar()->addMenu(tr("&File"));

    newAct = new QAction(tr("&New"), this);
    fileMenu->addAction(newAct);
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
//! [1a]

    saveAct = new QAction(tr("&Save As..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addSeparator();

    exitAct = new QAction(tr("E&xit"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    toolMenu = menuBar()->addMenu(tr("&Tools"));
}

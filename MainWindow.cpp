//
// Created by Andrzej Borucki on 2022-04-10
//

#include "MainWindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QTabBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QLabel>
#include "raise.h"

MainWindow::MainWindow() {
    createMenus();
    createStatusBar();
    tabWidget = new QTabWidget;
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    tabWidget->setTabPosition(QTabWidget::South);
    connect(tabWidget, &QTabWidget::currentChanged, this,
            [this](int index) {
                onTabChanged(index);
            });
    connect(tabWidget, &QTabWidget::tabCloseRequested, this,
            [this](int index) {
                tryCloseTab(index);
            });
    closeManager = new CloseManager(tabWidget);
    setCentralWidget(tabWidget);
}

void MainWindow::tryCloseTab(int index) {
    CodeEditor* editor = selectedEditor(index);
    assert(editor);
    auto closeAction = closeManager->tryCloseTab(editor);
    if (closeAction==CloseManager::SaveAndClose) {
        if (editor->path.isEmpty()) {
            if (!saveAs()) return;
        } else {
            if (!save()) return;
        }
    }
    if (closeAction!=CloseManager::Cancel) {
        if (editor->path.isEmpty())
            untitleCounter.releaseId(editor->untitleId);
        tabWidget->removeTab(index);
        delete editor;
    }
}

void MainWindow::newFile()
{
    CodeEditor *editor = new CodeEditor();
    connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::onTextChanged);
    connect(editor, &QPlainTextEdit::cursorPositionChanged, this, &MainWindow::onCursorPositionChanged);
    editor->untitleId = untitleCounter.getNextId();
    tabWidget->addTab(editor, editor->getTitle());
    tabWidget->setCurrentWidget(editor);
    editor->setFocus();
}

CodeEditor * MainWindow::openInEditor(QString path) {
    CodeEditor *editor = new CodeEditor();
    connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::onTextChanged);
    connect(editor, &QPlainTextEdit::cursorPositionChanged, this, &MainWindow::onCursorPositionChanged);
    editor->path = path;
    tabWidget->addTab(editor, editor->getTitle());
    editor->openFile(path);
    editor->document()->setModified(false);
    onTextChanged();
    return editor;
}

CodeEditor *MainWindow::getEditorByPath(QString path) {
    for (int i=0; i<tabWidget->count(); i++) {
        QWidget *tab = tabWidget->widget(i);
        CodeEditor* editor = dynamic_cast<CodeEditor*>(tab);
        if (editor->path==path) return editor;
    }
    return nullptr;
}

void MainWindow::openOrActivate(QString path) {
    CodeEditor *editor = getEditorByPath(path);
    if (editor) {
        QTextCursor cursor = editor->textCursor();
        int position = cursor.position();
        editor->openFile(path);
        cursor.setPosition(position, QTextCursor::MoveAnchor);
        editor->setTextCursor(cursor);
        editor->activateWindow();
        editor->document()->setModified(false);
        onTextChanged();
    }
    else
        editor = openInEditor(path);
    tabWidget->setCurrentWidget(editor);
    editor->setFocus();
}

void MainWindow::openFile()
{
    QFileDialog dialog(this, tr("Open File"));
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    if (dialog.exec() == QDialog::Accepted) {
        QString path = dialog.selectedFiles().first();
        openOrActivate(path);
    }
}

bool MainWindow::saveFileToPath(CodeEditor* editor) {
    assert(editor);
    if (editor->saveFileToPath()) {
        onTextChanged();
        return true;
    }
    else
        return false;
};

bool MainWindow::save() {
    CodeEditor* editor = currentEditor();
    if (!editor) return false;
    if (editor->path.isEmpty())
        return saveAs();
    else
        return saveFileToPath(editor);
}

bool MainWindow::saveAs()
{
    CodeEditor* editor = currentEditor();
    if (!editor) return false;
    QFileDialog dialog(this, tr("Save File"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    if (dialog.exec() == QDialog::Accepted) {
        if (editor->path.isEmpty())
            untitleCounter.releaseId(editor->untitleId);
        editor->path = dialog.selectedFiles().first();
        onTextChanged();
        return saveFileToPath(editor);
    }
    else
        return false;
}

void MainWindow::createMenus() {
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *editAct;
    QAction *removeAc;

    fileMenu = menuBar()->addMenu(tr("&File"));

    newAct = new QAction(tr("&New"), this);
    newAct->setShortcut(QKeySequence("ctrl+n"));
    fileMenu->addAction(newAct);
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(QKeySequence("ctrl+o"));
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcut(QKeySequence("ctrl+s"));
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    saveAsAct = new QAction(tr("save &As..."), this);
    fileMenu->addAction(saveAsAct);
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);

    fileMenu->addSeparator();

    exitAct = new QAction(tr("E&xit"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    toolMenu = menuBar()->addMenu(tr("&Tools"));
}

void MainWindow::createStatusBar() {
    m_statusLeft = new QLabel("line:col", this);
    m_statusLeft->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_statusLeft->setMinimumWidth(40);
    m_statusMiddle = new QLabel("Middle", this);
    m_statusMiddle->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_statusRight = new QLabel("path", this);
    m_statusRight->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    statusBar()->addPermanentWidget(m_statusLeft, 0);
    statusBar()->addPermanentWidget(m_statusMiddle, 0);
    statusBar()->addPermanentWidget(m_statusRight, 1);
}

void MainWindow::onTextChanged() {
    CodeEditor* editor = currentEditor();
    if (!editor) return;
    bool modified = editor->document()->isModified();
    QColor color = modified? Qt::red : Qt::black;
    tabWidget->tabBar()->setTabTextColor(tabWidget->currentIndex(),color);
}

void MainWindow::onCursorPositionChanged() {
    CodeEditor* editor = currentEditor();
    if (!editor) return;
    QTextCursor cursor = editor->textCursor();
    auto line = cursor.blockNumber()+1;
    auto col = cursor.positionInBlock()+1;
    QString label = QString::number(line)+":"+QString::number(col);
    m_statusLeft->setText(label);
}

void MainWindow::onTabChanged(int index) {
    CodeEditor* editor = selectedEditor(index);
    if (!editor) return;
    setWindowTitle(editor->getTitle());
    m_statusRight->setText(editor->path);
}

CodeEditor* MainWindow::currentEditor() {
    QWidget *tab = tabWidget->currentWidget();
    return dynamic_cast<CodeEditor*>(tab);
}

CodeEditor* MainWindow::selectedEditor(int index) {
    QWidget *tab = tabWidget->widget(index);
    return dynamic_cast<CodeEditor*>(tab);
}

void MainWindow::handleMessage() {
    raiseThis();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    for (int index = tabWidget->count()-1; index>=0; index--) {
        CodeEditor* editor = selectedEditor(index);
        assert(editor);
        auto closeAction = closeManager->tryCloseTab(editor);
        if (closeAction==CloseManager::SaveAndClose) {
            if (editor->path.isEmpty()) {
                if (!saveAs()) {
                    event->ignore();
                    return;
                }
            } else {
                if (!save()) {
                    QMessageBox::warning(this, "error", editor->getTitle() + " can't be saved! Try SaveAs");
                    event->ignore();
                    return;
                }
            }
        }
        if (closeAction!=CloseManager::Cancel) {
            if (editor->path.isEmpty())
                untitleCounter.releaseId(editor->untitleId);
            tabWidget->removeTab(index);
            delete editor;
        } else
        {
            event->ignore();
            return;
        }
    }
    event->accept();
}

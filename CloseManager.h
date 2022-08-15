//
// Created by Andrzej Borucki on 2022-08-15
//

#pragma once
#include <QTabWidget>
#include "codeeditor.h"

class CloseManager {
    QTabWidget* tabWidget;
public:
    enum CloseAction {Cancel , SaveAndClose, CloseWithoutSaving};
    explicit CloseManager(QTabWidget* tabWidget):tabWidget(tabWidget){}
    CloseAction tryCloseTab(CodeEditor* editor);
};

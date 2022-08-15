//
// Created by Andrzej Borucki on 2022-08-15
//

#pragma once
#include <QTabWidget>

class CloseManager {
    QTabWidget* tabWidget;
public:
    explicit CloseManager(QTabWidget* tabWidget):tabWidget(tabWidget){}
};

//
// Created by Andrzej Borucki on 2022-08-15
//

#include "CloseManager.h"
#include <QMessageBox>

CloseManager::CloseAction CloseManager::tryCloseTab(CodeEditor* editor) {
    if (editor->document()->isModified())
    {
        tabWidget->setCurrentWidget(editor);
        QString message = "The text has been changed.\n";
        message += "Do you want to save the modifications? (No = close and discard changes)";
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(tabWidget, "Warning", message,
                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if (reply == QMessageBox::Cancel)
            return Cancel;
        else if (reply == QMessageBox::Yes)
            return SaveAndClose;
        else {
            assert(reply == QMessageBox::No);
            return CloseWithoutSaving;
        }
    } else
        return CloseWithoutSaving;
}

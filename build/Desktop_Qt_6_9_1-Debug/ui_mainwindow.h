/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_PDF;
    QAction *actionClose_PDF;
    QAction *actionSave_PDF;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionFind;
    QAction *actionSave_PDF_2;
    QAction *actionClose_PDF_2;
    QAction *actionPrint;
    QAction *actionHide_Inspector;
    QAction *actionFull_Screen;
    QAction *actionAbout;
    QAction *actionContact;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *openfileBtn;
    QMenuBar *menubar;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(750, 414);
        actionOpen_PDF = new QAction(MainWindow);
        actionOpen_PDF->setObjectName("actionOpen_PDF");
        actionClose_PDF = new QAction(MainWindow);
        actionClose_PDF->setObjectName("actionClose_PDF");
        actionSave_PDF = new QAction(MainWindow);
        actionSave_PDF->setObjectName("actionSave_PDF");
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName("actionUndo");
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName("actionRedo");
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName("actionCut");
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName("actionPaste");
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName("actionFind");
        actionSave_PDF_2 = new QAction(MainWindow);
        actionSave_PDF_2->setObjectName("actionSave_PDF_2");
        actionClose_PDF_2 = new QAction(MainWindow);
        actionClose_PDF_2->setObjectName("actionClose_PDF_2");
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName("actionPrint");
        actionHide_Inspector = new QAction(MainWindow);
        actionHide_Inspector->setObjectName("actionHide_Inspector");
        actionFull_Screen = new QAction(MainWindow);
        actionFull_Screen->setObjectName("actionFull_Screen");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionContact = new QAction(MainWindow);
        actionContact->setObjectName("actionContact");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        openfileBtn = new QPushButton(centralwidget);
        openfileBtn->setObjectName("openfileBtn");
        openfileBtn->setMinimumSize(QSize(160, 160));
        openfileBtn->setMaximumSize(QSize(160, 160));
        QFont font;
        font.setPointSize(15);
        openfileBtn->setFont(font);

        horizontalLayout->addWidget(openfileBtn);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 750, 23));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuView = new QMenu(menubar);
        menuView->setObjectName("menuView");
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName("menuWindow");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionFind);
        menuView->addAction(actionHide_Inspector);
        menuWindow->addAction(actionFull_Screen);
        menuHelp->addAction(actionAbout);
        menuHelp->addSeparator();
        menuHelp->addAction(actionContact);
        menuFile->addAction(actionOpen_PDF);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_PDF_2);
        menuFile->addSeparator();
        menuFile->addAction(actionClose_PDF_2);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen_PDF->setText(QCoreApplication::translate("MainWindow", "Open PDF", nullptr));
        actionClose_PDF->setText(QCoreApplication::translate("MainWindow", "Close PDF", nullptr));
        actionSave_PDF->setText(QCoreApplication::translate("MainWindow", "Save PDF", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
        actionFind->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        actionSave_PDF_2->setText(QCoreApplication::translate("MainWindow", "Save PDF", nullptr));
        actionClose_PDF_2->setText(QCoreApplication::translate("MainWindow", "Close PDF", nullptr));
        actionPrint->setText(QCoreApplication::translate("MainWindow", "Print", nullptr));
        actionHide_Inspector->setText(QCoreApplication::translate("MainWindow", "Hide Inspector", nullptr));
        actionFull_Screen->setText(QCoreApplication::translate("MainWindow", "Full Screen", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionContact->setText(QCoreApplication::translate("MainWindow", "Contact", nullptr));
        openfileBtn->setText(QCoreApplication::translate("MainWindow", "Open PDF", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuWindow->setTitle(QCoreApplication::translate("MainWindow", "Window", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

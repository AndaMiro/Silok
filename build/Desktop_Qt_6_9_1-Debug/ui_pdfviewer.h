/********************************************************************************
** Form generated from reading UI file 'pdfviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDFVIEWER_H
#define UI_PDFVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PdfViewer
{
public:
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QListView *inspector;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QFrame *PdfViewer)
    {
        if (PdfViewer->objectName().isEmpty())
            PdfViewer->setObjectName("PdfViewer");
        PdfViewer->resize(550, 300);
        PdfViewer->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(PdfViewer);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(PdfViewer);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        splitter->setHandleWidth(0);
        inspector = new QListView(splitter);
        inspector->setObjectName("inspector");
        inspector->setMinimumSize(QSize(150, 0));
        inspector->setMaximumSize(QSize(16777215, 16777215));
        inspector->setStyleSheet(QString::fromUtf8(""));
        splitter->addWidget(inspector);
        scrollArea = new QScrollArea(splitter);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setMinimumSize(QSize(200, 0));
        scrollArea->setAutoFillBackground(false);
        scrollArea->setStyleSheet(QString::fromUtf8(""));
        scrollArea->setLineWidth(5);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 198, 298));
        scrollAreaWidgetContents->setAutoFillBackground(true);
        scrollAreaWidgetContents->setStyleSheet(QString::fromUtf8(""));
        scrollArea->setWidget(scrollAreaWidgetContents);
        splitter->addWidget(scrollArea);

        horizontalLayout->addWidget(splitter);


        retranslateUi(PdfViewer);

        QMetaObject::connectSlotsByName(PdfViewer);
    } // setupUi

    void retranslateUi(QFrame *PdfViewer)
    {
        PdfViewer->setWindowTitle(QCoreApplication::translate("PdfViewer", "Frame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PdfViewer: public Ui_PdfViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDFVIEWER_H

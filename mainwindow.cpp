#include "ui_mainwindow.h"
#include <mainwindow.h>
#include <QFileDialog>
#include <pdfviewer.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_openfileBtn_clicked() {
    QFileDialog dialog(this);
    dialog.setNameFilter("PDF Files (*.pdf)");
    dialog.setWindowTitle("Select a PDF file.");

    if (dialog.exec() == QDialog::Accepted) {
        QString file = dialog.selectedFiles().first();
        if (!file.isEmpty()){
            PdfViewer *viewer = new PdfViewer(file, this);
            setCentralWidget(viewer);
        }
    }
}

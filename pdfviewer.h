#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QFrame>
#include <QFileDialog>
#include <QImage>
#include <QVBoxLayout>
#include <QVector>
#include <poppler/qt6/poppler-qt6.h>
#include <QFutureWatcher>
#include <QLocalServer>
#include <QLocalSocket>

namespace Ui {
class PdfViewer;
}

class PageWidget;
class SmartController;

class PdfViewer : public QFrame {
    Q_OBJECT

public:
    explicit PdfViewer(QString file, QWidget *parent = nullptr);
    ~PdfViewer();
    Ui::PdfViewer* getUi();
    int getCurrentPage();
    void setCurrentPage(int page);
    void sendScroll(int direction);

protected:
    void updateVisiblePages();
    void resizeEvent(QResizeEvent *event);

private:
    QString file;
    std::unique_ptr<Poppler::Document> doc;
    Ui::PdfViewer *ui;
    QImage sizeImage;
    QVBoxLayout *layout;
    QVector<PageWidget*> pageWidgets;
    SmartController *controller;
};



class PageWidget : public QWidget {
    Q_OBJECT

public:
    explicit PageWidget(PdfViewer *viewer, std::unique_ptr<Poppler::Page> page, QWidget *parent = nullptr);
    void load();
    void unload();
    bool isLoaded();
    QImage getImage();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    PdfViewer *viewer;
    std::unique_ptr<Poppler::Page> page;
    QImage image;
    bool loaded = false;
    bool loading = false;
    QFutureWatcher<QImage> watcher;
};

class SmartController : public QObject {
    Q_OBJECT

public:
    SmartController(PdfViewer *viewer, QObject *parent = nullptr);

signals:
    void sendScroll(int direction);

private:
    PdfViewer *viewer;
    QLocalServer *server;
    QLocalSocket *socket;

private slots:
    void handleNewConnection();
    void handleMessage();
};

#endif // PDFVIEWER_H

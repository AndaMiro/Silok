#include "ui_pdfviewer.h"
#include <pdfviewer.h>
#include <QFileDialog>
#include <QFrame>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QPainter>
#include <QImage>
#include <poppler/qt6/poppler-qt6.h>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QGraphicsDropShadowEffect>
#include <QLocalServer>

PdfViewer::PdfViewer(QString file, QWidget *parent)
    : QFrame(parent)
    , file(file)
    , doc(Poppler::Document::load(file))
    , ui(new Ui::PdfViewer)
{
    ui->setupUi(this);
    ui->splitter->setCollapsible(0, false);
    ui->splitter->setCollapsible(1, false);

    controller = new SmartController(this);

    if(!doc || doc->isLocked()){
        qDebug() << "Fail to load or locked";
        return;
    }

    layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    layout->setSpacing(10);
    ui->scrollAreaWidgetContents->setLayout(layout);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0; i < doc->numPages(); ++i){
        PageWidget *page = new PageWidget(this, doc->page(i));
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(page);
        shadow->setBlurRadius(10);
        shadow->setOffset(0, 0);
        page->setGraphicsEffect(shadow);
        ui->scrollAreaWidgetContents->layout()->addWidget(page);
        pageWidgets.push_back(page);
        page->load();
    }

    QTimer *updateTimer = new QTimer(this);
    updateTimer->setSingleShot(true);
    connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, [=](){
        updateTimer->start(50);
    });

    connect(updateTimer, &QTimer::timeout, this, [=](){
        updateVisiblePages();
    });

    // foreach (Poppler::OutlineItem out, doc->outline()) {
    //     qDebug() << out.name();
    // }
}

PdfViewer::~PdfViewer() {
    delete ui;
}

Ui::PdfViewer* PdfViewer::getUi() {
    return ui;
}

int PdfViewer::getCurrentPage() {
    int scrollY = ui->scrollArea->verticalScrollBar()->value();
    int accumulatedHeight = 0;

    for (int i = 0; i < pageWidgets.size(); ++i) {
        accumulatedHeight += pageWidgets[i]->getImage().height() + layout->spacing();
        if (scrollY < accumulatedHeight) {
            return i;
        }
    }
    return pageWidgets.size() - 1;
}

void PdfViewer::setCurrentPage(int page) {
    int accumulatedHeight = 0;

    for (int i = 0; i < page; ++i) accumulatedHeight += pageWidgets[i]->getImage().height() + layout->spacing();
    ui->scrollArea->verticalScrollBar()->setValue(accumulatedHeight);
}

void PdfViewer::sendScroll(int direction) {
    QScrollBar *bar = ui->scrollArea->verticalScrollBar();

    bar->setValue(bar->value() + 100 * direction);
}

void PdfViewer::updateVisiblePages() {
    int currentPage = getCurrentPage();
    int range = 5;

    qDebug() << currentPage;

    for (int i = 0; i < pageWidgets.size(); ++i) {
        if (currentPage - range <= i && i <= currentPage + range) {
            if (!pageWidgets[i]->isLoaded()) pageWidgets[i]->load();
        } else {
            if (pageWidgets[i]->isLoaded()) pageWidgets[i]->unload();
        }
    }
}

void PdfViewer::resizeEvent(QResizeEvent *event) {
    QFrame::resizeEvent(event);

    int currentPage = getCurrentPage();
    int range = 5;

    for (int i = 0; i < pageWidgets.size(); ++i) {
        if (currentPage - range <= i && i <= currentPage + range) {
            pageWidgets[i]->unload();
            pageWidgets[i]->load();
        }
    }
}













PageWidget::PageWidget(PdfViewer *viewer, std::unique_ptr<Poppler::Page> old_page, QWidget *parent)
    : QWidget(parent)
    , viewer(viewer)
    , page(std::move(old_page))
{}

void PageWidget::load() {
    if (loaded || loading || !page) return;

    loading = true;

    QFuture<QImage> future = QtConcurrent::run([=]() -> QImage {
        return page->renderToImage(150, 150).scaledToWidth(viewer->getUi()->scrollArea->width(), Qt::SmoothTransformation);
    });

    connect(&watcher, &QFutureWatcher<QImage>::finished, this, [=]() {
        image = watcher.result();
        loaded = true;
        loading = false;
        setFixedSize(image.size());
        update();
    });

    watcher.setFuture(future);
}

void PageWidget::unload() {
    loaded = false;
    update();
}

bool PageWidget::isLoaded() {
    return loaded;
}

QImage PageWidget::getImage() {
    return image;
}

void PageWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (loaded){
        painter.drawImage(0, 0, image);
    }
    else painter.fillRect(rect(), Qt::white);
}














SmartController::SmartController(PdfViewer *viewer, QObject *parent)
    : QObject(parent)
    , viewer(viewer)
{
    server = new QLocalServer(this);
    server->removeServer("scroll_pipe");
    server->listen("scroll_pipe");
    connect(server, &QLocalServer::newConnection, this, &SmartController::handleNewConnection);
    connect(this, &SmartController::sendScroll, viewer, &PdfViewer::sendScroll);
}

void SmartController::handleNewConnection() {
    socket = server->nextPendingConnection();
    connect(socket, &QLocalSocket::readyRead, this, &SmartController::handleMessage);
    qDebug() << "connnnnnect";
}

void SmartController::handleMessage() {
    qDebug() << "handleMessage() called";
    QByteArray data = socket->readAll();
    QString message(data);
    if(message.contains("up")) emit sendScroll(-1);
    else if(message.contains("down")) emit sendScroll(1);
}

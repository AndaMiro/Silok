#include "ui_pdfviewer.h"
#include <pdfviewer.h>
#include <QObject>
#include <QFileDialog>
#include <QFrame>
#include <QVBoxLayout>
#include <QMessageBox>
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

    /* Prevent UI panel from collapsing */
    ui->splitter->setCollapsible(0, false);
    ui->splitter->setCollapsible(1, false);




    /*
     * Experimental function
     * controller = new SmartController(this);
     */




    if(!doc || doc->isLocked()){
        QMessageBox::warning(this, "Alert", "Fail to load or locked!", QMessageBox::StandardButton::Close);
        return;
    }



    /* Set up a top-level layout for scrollAreaWidgetContents and insert the PDF page widget into it */
    layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    layout->setSpacing(10);
    //ui->scrollAreaWidgetContents->setLayout(layout);



    /* Prevent horizontal scroll */
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    /* Add the PDF page widget to scrollAreaWidgetContents */
    for(int i = 0; i < doc->numPages(); ++i){
        PageWidget *page = new PageWidget(this, doc->page(i));

        /* Set CSS for the PDF page widget */
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(page);
        shadow->setBlurRadius(10);
        shadow->setOffset(0, 0);
        page->setGraphicsEffect(shadow);
        page->load();

        ui->scrollAreaWidgetContents->layout()->addWidget(page);
    }

    /* Delay widget position update by 0.1 seconds after scroll */
    connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, [=](){
        QTimer::singleShot(100, this, &PdfViewer::updateVisiblePages);
    });

    /* Connect splitter movement to widget resize */
    connect(ui->splitter, &QSplitter::splitterMoved, this, [=](){
        this->resizeEvent(NULL);
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

    for (int i = 0; i < layout->count(); ++i) {
        accumulatedHeight += ((PageWidget*)layout->itemAt(i)->widget())->getImage().height() + layout->spacing();
        if (scrollY < accumulatedHeight) {
            return i;
        }
    }
    return layout->count() - 1;
}

void PdfViewer::setCurrentPage(int page) {
    int accumulatedHeight = 0;

    for (int i = 0; i < page; ++i) accumulatedHeight += ((PageWidget*)layout->itemAt(i)->widget())->getImage().height() + layout->spacing();
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

    for (int i = 0; i < layout->count(); ++i) {
        PageWidget *widget = (PageWidget*)layout->itemAt(i)->widget();
        if(!widget) break;

        if (currentPage - range <= i && i <= currentPage + range) {
            if (!widget->isLoaded()) widget->load();
        } else {
            if (widget->isLoaded()) widget->unload();
        }
    }
}

void PdfViewer::resizeEvent(QResizeEvent *event) {
    QFrame::resizeEvent(event);

    int currentPage = getCurrentPage();
    int range = 5;

    for (int i = 0; i < layout->count(); ++i) {
        if (currentPage - range <= i && i <= currentPage + range) {
            PageWidget *widget = (PageWidget*)layout->itemAt(i)->widget();
            if(widget){
                widget->unload();
                widget->load();
            }
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
    if(!loaded) return;

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

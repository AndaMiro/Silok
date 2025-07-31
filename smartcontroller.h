#ifndef SMARTCONTROLLER_H
#define SMARTCONTROLLER_H

#include <QObject>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>
#include <pdfviewer.h>

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

#endif // SMARTCONTROLLER_H

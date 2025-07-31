#include "smartcontroller.h"
#include <QObject>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>
#include <pdfviewer.h>
#include <ui_pdfviewer.h>

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
}

void SmartController::handleMessage() {
    QByteArray data = socket->readAll();
    QString message(data);
    if(message.contains("up")) emit sendScroll(-1);
    else if(message.contains("down")) emit sendScroll(1);
}

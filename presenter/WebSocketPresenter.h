#pragma once
#include <QObject>
#include "service/WebSocketService.h"
#include "parser/ProtocolParser.h"

class WebSocketPresenter : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketPresenter(WebSocketService* service, ProtocolParser* parser, QObject* parent=nullptr)
        : QObject(parent), m_service(service), m_parser(parser)
    {
        connect(m_service, &WebSocketService::dataReceived,
                this, &WebSocketPresenter::onDataReceived);
    }

signals:
    void dataReady(const QByteArray &data);

public slots:
    void start() { m_service->start(); }
    void stop() { m_service->stop(); }

private slots:
    void onDataReceived(const QByteArray &raw) {
        QByteArray parsed = m_parser->parse(raw);
        emit dataReady(parsed);
    }

private:
    WebSocketService* m_service;
    ProtocolParser* m_parser;
};
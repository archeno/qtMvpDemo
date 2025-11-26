#pragma once
#include <QObject>
#include "service/DataVisService.h"
#include "parser/ProtocolParser.h"

class DataVisPresenter : public QObject
{
    Q_OBJECT
public:
    explicit DataVisPresenter(DataVisService* service, ProtocolParser* parser, QObject* parent=nullptr)
        : QObject(parent), m_service(service), m_parser(parser)
    {
        connect(m_service, &DataVisService::dataUpdated,
                this, &DataVisPresenter::onDataUpdated);
    }

signals:
    void dataReady(const QByteArray &data);

public slots:
    void start() { m_service->start(); }
    void stop() { m_service->stop(); }

private slots:
    void onDataUpdated(const QByteArray &raw) {
        QByteArray parsed = m_parser->parse(raw);
        emit dataReady(parsed);
    }

private:
    DataVisService* m_service;
    ProtocolParser* m_parser;
};
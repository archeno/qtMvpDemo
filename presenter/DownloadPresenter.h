#pragma once
#include <QObject>
#include "service/DownloadService.h"
#include "parser/ProtocolParser.h"

class DownloadPresenter : public QObject
{
    Q_OBJECT
public:
    explicit DownloadPresenter(DownloadService* service, ProtocolParser* parser, QObject *parent=nullptr)
        : QObject(parent), m_service(service), m_parser(parser)
    {
        connect(m_service, &DownloadService::downloadFinished, this, &DownloadPresenter::onDownloadFinished);
    }

signals:
    void downloadResultReady(const QByteArray &data);

public slots:
    void startDownload() { m_service->startDownload(); }

private slots:
    void onDownloadFinished(const QByteArray &raw) {
        QByteArray parsed = m_parser->parse(raw);
        emit downloadResultReady(parsed);
    }

private:
    DownloadService* m_service;
    ProtocolParser* m_parser;
};
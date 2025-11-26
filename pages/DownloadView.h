#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "presenter/DownloadPresenter.h"
#include "service/DownloadService.h"
#include "parser/ProtocolParser.h"

class DownloadView : public QWidget
{
    Q_OBJECT
public:
    explicit DownloadView(QWidget *parent=nullptr) : QWidget(parent)
    {
        auto layout = new QVBoxLayout(this);
        m_label = new QLabel("Ready");
        layout->addWidget(m_label);

        auto btn = new QPushButton("Start Download");
        layout->addWidget(btn);

        auto btnClose = new QPushButton("Close");
        layout->addWidget(btnClose);

        m_service = new DownloadService(this);
        m_parser = new ProtocolParser(this);
        m_presenter = new DownloadPresenter(m_service, m_parser, this);

        connect(btn, &QPushButton::clicked, m_presenter, &DownloadPresenter::startDownload);
        connect(m_presenter, &DownloadPresenter::downloadResultReady, this, [this](const QByteArray &data){
            m_label->setText(QString("Result: %1").arg(QString(data)));
        });
        connect(btnClose, &QPushButton::clicked, this, [this](){ emit requestClose(); });
    }

signals:
    void requestClose();

private:
    QLabel* m_label;
    DownloadService* m_service;
    ProtocolParser* m_parser;
    DownloadPresenter* m_presenter;
};
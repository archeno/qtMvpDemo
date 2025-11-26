#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "service/WebSocketService.h"
#include "parser/ProtocolParser.h"
#include "presenter/WebSocketPresenter.h"

class WebSocketView : public QWidget
{
    Q_OBJECT
public:
    explicit WebSocketView(QWidget* parent=nullptr) : QWidget(parent)
    {
        auto layout = new QVBoxLayout(this);
        m_label = new QLabel("Waiting for data...");
        layout->addWidget(m_label);

        auto btnStart = new QPushButton("Start WebSocket");
        auto btnStop = new QPushButton("Stop WebSocket");
        auto btnClose = new QPushButton("Close Page");
        layout->addWidget(btnStart);
        layout->addWidget(btnStop);
        layout->addWidget(btnClose);

        m_service = new WebSocketService(this);
        m_parser = new ProtocolParser(this);
        m_presenter = new WebSocketPresenter(m_service, m_parser, this);

        connect(btnStart, &QPushButton::clicked, m_presenter, &WebSocketPresenter::start);
        connect(btnStop, &QPushButton::clicked, m_presenter, &WebSocketPresenter::stop);
        connect(m_presenter, &WebSocketPresenter::dataReady, this, [this](const QByteArray &data){
            m_label->setText(QString("Data: %1").arg(QString(data)));
        });
        connect(btnClose, &QPushButton::clicked, this, [this](){ emit requestClose(); });
    }

signals:
    void requestClose();

private:
    QLabel* m_label;
    WebSocketService* m_service;
    ProtocolParser* m_parser;
    WebSocketPresenter* m_presenter;
};
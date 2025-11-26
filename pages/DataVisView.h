#pragma once
#include "parser/ProtocolParser.h"
#include "presenter/DataVisPresenter.h"
#include "service/DataVisService.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class DataVisView : public QWidget {
  Q_OBJECT
public:
  explicit DataVisView(QWidget *parent = nullptr) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);
    m_label = new QLabel("Waiting for visualization data...");
    layout->addWidget(m_label);

    auto btnStart = new QPushButton("Start Visualization");
    auto btnStop = new QPushButton("Stop Visualization");
    auto btnClose = new QPushButton("Close Page");
    layout->addWidget(btnStart);
    layout->addWidget(btnStop);
    layout->addWidget(btnClose);

    m_service = new DataVisService(this);
    m_parser = new ProtocolParser(this);
    m_presenter = new DataVisPresenter(m_service, m_parser, this);

    connect(btnStart, &QPushButton::clicked, m_presenter,
            &DataVisPresenter::start);
    connect(btnStop, &QPushButton::clicked, m_presenter,
            &DataVisPresenter::stop);
    connect(m_presenter, &DataVisPresenter::dataReady, this,
            [this](const QByteArray &data) {
              m_label->setText(QString("Data: %1").arg(QString(data)));
            });
    connect(btnClose, &QPushButton::clicked, this,
            [this]() { emit requestClose(); });
  }

signals:
  void requestClose();

private:
  QLabel *m_label;
  DataVisService *m_service;
  ProtocolParser *m_parser;
  DataVisPresenter *m_presenter;
};
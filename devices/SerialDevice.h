#pragma once
#include "IDevice.h"
#include <QTimer>

class SerialDevice : public IDevice {
  Q_OBJECT
public:
  explicit SerialDevice(QObject *parent = nullptr) : IDevice(parent) {
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this,
            [this]() { emit dataReceived(QByteArray("SerialData")); });
  }

  void open() override { m_timer->start(1000); }
  void close() override { m_timer->stop(); }
  void writeData(const QByteArray &data) override { Q_UNUSED(data); }

private:
  QTimer *m_timer;
};

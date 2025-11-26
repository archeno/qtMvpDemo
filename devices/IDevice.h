#pragma once
#include <QByteArray>
#include <QObject>

class IDevice : public QObject {
  Q_OBJECT
public:
  explicit IDevice(QObject *parent = nullptr) : QObject(parent) {}
  virtual ~IDevice() {}

  virtual void open() = 0;
  virtual void close() = 0;
  virtual void writeData(const QByteArray &data) = 0;

signals:
  void dataReceived(const QByteArray &data);
};

#pragma once
#include <QObject>
#include <QByteArray>

class DeviceData : public QObject
{
    Q_OBJECT
public:
    explicit DeviceData(QObject *parent = nullptr) : QObject(parent) {}
    void appendData(const QByteArray &data) { m_data.append(data); emit dataUpdated(m_data); }
    QByteArray data() const { return m_data; }
    void clear() { m_data.clear(); }

signals:
    void dataUpdated(const QByteArray &data);

private:
    QByteArray m_data;
};
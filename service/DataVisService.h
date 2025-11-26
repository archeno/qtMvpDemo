#pragma once
#include <QObject>
#include <QTimer>

class DataVisService : public QObject
{
    Q_OBJECT
public:
    explicit DataVisService(QObject *parent=nullptr) : QObject(parent) {
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &DataVisService::simulateData);
    }

    void start() { m_timer->start(1000); }
    void stop() { m_timer->stop(); }

signals:
    void dataUpdated(const QByteArray &data);

private slots:
    void simulateData() { emit dataUpdated(QByteArray("VisData")); }

private:
    QTimer* m_timer;
};
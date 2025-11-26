#pragma once
#include <QObject>
#include <QTimer>

class WebSocketService : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketService(QObject *parent=nullptr) : QObject(parent) {
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &WebSocketService::simulateData);
    }

    void start() { m_timer->start(1000); }
    void stop() { m_timer->stop(); }

signals:
    void dataReceived(const QByteArray &data);

private slots:
    void simulateData() { emit dataReceived(QByteArray("WebSocketData")); }

private:
    QTimer* m_timer;
};
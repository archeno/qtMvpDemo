#pragma once
#include <QObject>
#include <QTimer>

class DownloadService : public QObject
{
    Q_OBJECT
public:
    explicit DownloadService(QObject *parent = nullptr) : QObject(parent) {}
    void startDownload() {
        QTimer::singleShot(2000, this, [this](){ emit downloadFinished("DownloadedData"); });
    }
signals:
    void downloadFinished(const QByteArray &data);
};
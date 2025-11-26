#pragma once
#include <QObject>
#include <QByteArray>

class ProtocolParser : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolParser(QObject *parent = nullptr) : QObject(parent) {}
    QByteArray parse(const QByteArray &raw) { return raw; } // 简单示例
};
#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QTimer>
#include <mqtt/async_client.h>
#include <QDebug>
#include "custommqttcallback.h"
#include <sstream>

class MQTTClient : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString batteryStatus READ batteryStatus NOTIFY batteryStatusChanged)
    Q_PROPERTY(int batteryPercentage READ batteryPercentage NOTIFY batteryPercentageChanged)

public:
    explicit MQTTClient(QObject *parent = nullptr);

    QString batteryStatus() const;
    int batteryPercentage() const;

    void subscribeToTopic(const QString &topic);

signals:
    void batteryStatusChanged();
    void batteryPercentageChanged();

public slots:
    void onMessageArrived(const std::string& topic, const std::string& payload);

private:
    mqtt::async_client *client;
    QString m_batteryStatus;
    int m_batteryPercentage;
};

#endif // MQTTCLIENT_H

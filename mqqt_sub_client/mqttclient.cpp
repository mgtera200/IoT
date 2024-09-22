#include <mqtt/async_client.h>
#include <mqtt/exception.h>
#include <QString>
#include <QDebug>
#include "mqttclient.h"

MQTTClient::MQTTClient(QObject *parent)
    : QObject(parent),
    client(new mqtt::async_client("tcp://192.168.1.26:1883", "battery-monitor-client"))
{
    // Connect to the MQTT server
    client->connect()->wait();

    // Subscribe to the battery topic
    subscribeToTopic("laptop/battery");
}

QString MQTTClient::batteryStatus() const
{
    return m_batteryStatus;
}

int MQTTClient::batteryPercentage() const
{
    return m_batteryPercentage;
}

void MQTTClient::subscribeToTopic(const QString &topic)
{
    auto callbackHandler = new CustomMQTTCallback([this](mqtt::const_message_ptr msg) {
        std::string payload = msg->get_payload_str();
        qDebug() << "Message received: " << QString::fromStdString(payload);
        onMessageArrived(msg->get_topic(), payload);
    });

    // Set the custom callback handler to the client
    client->set_callback(*callbackHandler);

    // Now subscribe to the topic
    client->subscribe(topic.toStdString(), 1);
}

void MQTTClient::onMessageArrived(const std::string &topic, const std::string &payload)
{
    // Split the payload into key-value pairs
    std::istringstream ss(payload);
    std::string token;
    int percentage = 0;
    std::string status;

    while (std::getline(ss, token, ',')) {
        if (token.find("percentage:") == 0) {
            percentage = std::stoi(token.substr(11)); // Extract percentage value
            m_batteryPercentage = percentage;
            emit batteryPercentageChanged(); // Emit signal for battery percentage change
        } else if (token.find("status:") == 0) {
            status = token.substr(7); // Extract status value
            m_batteryStatus = QString::fromStdString(status);
            emit batteryStatusChanged(); // Emit signal for battery status change
        }
    }

    qDebug() << "Message received on topic:" << QString::fromStdString(topic)
             << ", payload:" << QString::fromStdString(payload);
}

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "conf.h"

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
    Serial.println();
    Serial.print("Connecting to ");
    Serial.print(SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();

    Serial.println("Connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void setup_mqtt()
{
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback);
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");

        // create random client ID
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);

        // attempt to connect
        if (client.connect(clientId.c_str()))
        {
            Serial.println("connected");
            // announcement
            client.publish("outTopic", "hello world");
            client.subscribe("inTopic");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void loop_mqtt()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}

void callback(char *topic, byte *payload, unsigned int length)
{
}
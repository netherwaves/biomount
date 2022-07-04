#pragma once

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
    //client.setCallback(callback);
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");

        // create random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);

        // attempt to connect
        if (client.connect(clientId.c_str()))
        {
            Serial.println("connected");
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

void send_to_esp32(SensorPack* packet) {
    if (!client.connected()) return;

    // create payload array
    byte* payload = (byte*)malloc(16);
    // copy packet to payload
    memcpy(payload,         &packet->heart,     4);
    memcpy(payload + 4,     &packet->resp,      4);
    memcpy(payload + 8,     &packet->forehead,  4);
    memcpy(payload + 12,    &packet->neck,      4);

    // set topic
    const char* topic = "biomount/headset01";
    Serial.print("publishing to ");
    Serial.println(topic);
    
    // publish to MQTT
    client.publish(topic, payload, 16);
    free(payload);
}
#pragma once

#include <WiFi.h>
#include <PubSubClient.h>
#include "conf.h"

WiFiClient espClient;
PubSubClient client(espClient);


// headers
void callback(char *topic, byte *payload, unsigned int length);


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
            // TODO: make this dynamic per headset
            // (since there will be more than one...)
            client.subscribe("biomount/headset01");
        }
        else
        {
            if (DEBUG) {
                Serial.print("failed, rc=");
                Serial.print(client.state());
                Serial.println(" try again in 5 seconds");
            }
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
    if (strcmp(topic, "biomount/headset01") == 0) {
        float heart, resp, forehead, neck;

        if (DEBUG) {
            Serial.print("receiving from ");
            Serial.println(topic);
            Serial.print("payload length: ");
            Serial.println(length);
            Serial.println("----------------");
        }

        // copy values from payload...
        memcpy(&heart, payload, 4);
        memcpy(&resp, payload + 4, 4);
        memcpy(&forehead, payload + 8, 4);
        memcpy(&neck, payload + 12, 4);

        if (DEBUG) {
            Serial.print("heart:\t\t");
            Serial.println(heart);
            Serial.print("resp:\t\t");
            Serial.println(resp);
            Serial.print("forehead:\t");
            Serial.println(forehead);
            Serial.print("neck:\t\t");
            Serial.println(neck);
            Serial.println("----------------");
        }
    }
}
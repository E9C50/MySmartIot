package com.fuxin.iot.mqtt.sender;

import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;

@Component
@AllArgsConstructor
public class MqttMessageSender {

    private MqttGateway mqttGateway;

    public void send(String topic, String message) {
        mqttGateway.sendToMqtt(topic, message);
    }

    public void send(String topic, int qos, byte[] message) {
        mqttGateway.sendToMqtt(topic, qos, message);
    }
}
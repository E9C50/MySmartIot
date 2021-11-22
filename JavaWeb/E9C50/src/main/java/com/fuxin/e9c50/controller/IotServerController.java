package com.fuxin.e9c50.controller;

import com.fuxin.e9c50.mqtt.sender.MqttMessageSender;
import com.fuxin.e9c50.utils.DeviceStatus;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@Slf4j
@RestController
@RequestMapping("/iotServer")
public class IotServerController {

    @Value("${mqtt.topic.command}")
    private String topicPublish;

    private final DeviceStatus deviceStatus;
    private final MqttMessageSender mqttMessageSender;

    @Autowired
    public IotServerController(DeviceStatus deviceStatus, MqttMessageSender mqttMessageSender) {
        this.deviceStatus = deviceStatus;
        this.mqttMessageSender = mqttMessageSender;
    }

    @GetMapping("/publishMessage")
    public boolean publishMessage(
            @RequestParam("payload") String payload
    ) {
        mqttMessageSender.send(topicPublish, payload);
        return true;
    }

    @GetMapping("/status")
    public String getStatus() {
        return deviceStatus.getStatus();
    }
}
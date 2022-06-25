package com.fuxin.iot.mqtt.receiver;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.fuxin.iot.utils.DeviceStatus;
import lombok.AllArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.messaging.Message;
import org.springframework.messaging.MessageHandler;
import org.springframework.messaging.MessagingException;
import org.springframework.stereotype.Component;

@Slf4j
@Component
@AllArgsConstructor
public class MqttMessageReceiver implements MessageHandler {

    private final DeviceStatus deviceStatus;

    @Override
    public void handleMessage(Message<?> message) throws MessagingException {
        try {
            String payload = (String) message.getPayload();
            JSONObject parse = JSON.parseObject(payload);
            JSONObject reported = (JSONObject) parse.get("reported");
            deviceStatus.setStatusEspLed(reported.get("esp-led").equals(1));
            deviceStatus.setStatusBedroomLight(reported.get("bedroom-light").equals(1));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
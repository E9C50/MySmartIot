package com.fuxin.iot.mqtt.sender;

import com.fuxin.iot.mqtt.MqttConfiguration;
import lombok.AllArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.integration.annotation.ServiceActivator;
import org.springframework.integration.channel.DirectChannel;
import org.springframework.integration.mqtt.core.MqttPahoClientFactory;
import org.springframework.integration.mqtt.outbound.MqttPahoMessageHandler;
import org.springframework.messaging.MessageChannel;
import org.springframework.messaging.MessageHandler;

@Slf4j
@Configuration
@AllArgsConstructor
public class MqttOutboundConfiguration {

    private final MqttConfiguration mqttConfiguration;
    private final MqttPahoClientFactory factory;

    @Bean
    @ServiceActivator(inputChannel = "mqttOutboundChannel")
    public MessageHandler mqttOutbound() {
        MqttPahoMessageHandler messageHandler = new MqttPahoMessageHandler(mqttConfiguration.getClientId() + "_Outbound", factory);
        messageHandler.setDefaultTopic(mqttConfiguration.getTopicPublish());
        messageHandler.setDefaultQos(0);
        messageHandler.setAsync(true);
        return messageHandler;
    }

    @Bean(name = "mqttOutboundChannel")
    public MessageChannel mqttOutboundChannel() {
        return new DirectChannel();
    }
}

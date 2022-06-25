package com.fuxin.iot.mqtt.receiver;

import com.fuxin.iot.mqtt.MqttConfiguration;
import lombok.AllArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.integration.annotation.IntegrationComponentScan;
import org.springframework.integration.annotation.ServiceActivator;
import org.springframework.integration.channel.DirectChannel;
import org.springframework.integration.endpoint.MessageProducerSupport;
import org.springframework.integration.mqtt.core.MqttPahoClientFactory;
import org.springframework.integration.mqtt.inbound.MqttPahoMessageDrivenChannelAdapter;
import org.springframework.integration.mqtt.support.DefaultPahoMessageConverter;
import org.springframework.messaging.MessageChannel;
import org.springframework.messaging.MessageHandler;

@Slf4j
@Configuration
@AllArgsConstructor
@IntegrationComponentScan
public class MqttInboundConfiguration {

    private final MqttConfiguration mqttConfig;
    private final MqttPahoClientFactory factory;
    private final MqttMessageReceiver mqttMessageReceiver;

    @Bean("mqttInBoundChannel")
    public MessageChannel mqttInBoundChannel() {
        return new DirectChannel();
    }

    @Bean
    @ServiceActivator(inputChannel = "mqttInBoundChannel")
    public MessageHandler mqttMessageHandler() {
        return this.mqttMessageReceiver;
    }

    @Bean
    public MessageProducerSupport mqttInbound() {
        MqttPahoMessageDrivenChannelAdapter adapter = new MqttPahoMessageDrivenChannelAdapter(
                mqttConfig.getClientId() + "_Inbound", factory, mqttConfig.getTopicSubscribe());
        adapter.setConverter(new DefaultPahoMessageConverter());
        adapter.setOutputChannel(mqttInBoundChannel());
        adapter.setCompletionTimeout(60000);
        adapter.setRecoveryInterval(10000);
        adapter.setQos(0);
        return adapter;
    }

}
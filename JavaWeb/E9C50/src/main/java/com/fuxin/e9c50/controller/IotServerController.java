package com.fuxin.e9c50.controller;

import com.tencentcloudapi.common.AbstractModel;
import com.tencentcloudapi.common.Credential;
import com.tencentcloudapi.common.exception.TencentCloudSDKException;
import com.tencentcloudapi.common.profile.ClientProfile;
import com.tencentcloudapi.common.profile.HttpProfile;
import com.tencentcloudapi.iotcloud.v20180614.IotcloudClient;
import com.tencentcloudapi.iotcloud.v20180614.models.PublishMessageRequest;
import com.tencentcloudapi.iotcloud.v20180614.models.PublishMessageResponse;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@Slf4j
@RestController
@RequestMapping("/iotServer")
public class IotServerController {

    private final String productId = "3C6LX6DIXP";
    private final String domainName = "iotcloud.tencentcloudapi.com";
    private final String secretId = "AKIDnPlrhGZbMq3ze2rPggPr2wZuyqRnshFW";
    private final String secretKey = "1lEQKxKQEl10i9JEtHPGq89tOcZEcjZ8";

    @GetMapping("/publishMessage")
    public String publishMessage(
            @RequestParam("deviceName") String deviceName,
            @RequestParam("payload") String payload
    ) {
        try {
            Credential cred = new Credential(secretId, secretKey);
            HttpProfile httpProfile = new HttpProfile();
            httpProfile.setEndpoint(domainName);
            ClientProfile clientProfile = new ClientProfile();
            clientProfile.setHttpProfile(httpProfile);
            IotcloudClient client = new IotcloudClient(cred, "", clientProfile);
            PublishMessageRequest req = new PublishMessageRequest();
            req.setTopic(productId + "/" + deviceName + "/sub");
            req.setPayload(payload);
            req.setProductId(productId);
            req.setDeviceName(deviceName);
            PublishMessageResponse resp = client.PublishMessage(req);
            return AbstractModel.toJsonString(resp);
        } catch (TencentCloudSDKException exception) {
            return null;
        }
    }
}
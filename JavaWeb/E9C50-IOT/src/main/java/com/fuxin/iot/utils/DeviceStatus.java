package com.fuxin.iot.utils;

import com.alibaba.fastjson.JSON;
import lombok.Getter;
import lombok.Setter;
import org.springframework.stereotype.Component;

import java.util.HashMap;
import java.util.Map;

@Getter
@Setter
@Component
public class DeviceStatus {
    private boolean statusEspLed;
    private boolean statusBedroomLight;

    public String getStatus() {
        Map<String, Object> map = new HashMap<>();
        map.put("esp-led", statusEspLed);
        map.put("bedroom-light", statusBedroomLight);
        return JSON.toJSONString(map);
    }
}

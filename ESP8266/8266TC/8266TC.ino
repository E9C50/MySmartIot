#include <Servo.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// ****************************************************
const char *mqttServer = "3C6LX6DIXP.iotcloud.tencentdevices.com";
const char *mqttUserName = "3C6LX6DIXPNodeMCU-8266;12010126;ZKREJ;1672239330";
const char *mqttPassword = "59eb0420ef86c1fc383a23da8133e3df23cafff13e87e80e58a1938e000c1c0e;hmacsha256";
const char *mqttClientId = "3C6LX6DIXPNodeMCU-8266";
const char *mqttSubTopic = "3C6LX6DIXP/NodeMCU-8266/sub";
const char *mqttPubTopic = "3C6LX6DIXP/NodeMCU-8266/pub";
// ****************************************************

// ****************************************************
const char *WIFI_SSID = "RT-AX86U";
const char *WIFI_PASSWORD = "ziru285@room501";
// ****************************************************

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

Servo myServo;

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  myServo.attach(15);

  connectWifi();
  connectMqtt();
}

void loop()
{
  if (!client.connected())
  {
    connectMqtt();
  }
  client.loop();
}

void connectWifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void publishMsg(char *msg)
{
  Serial.print("Publish message: ");
  Serial.println(msg);
  Serial.println(client.publish(mqttPubTopic, msg));
}

void callback(char *topic, byte *payload, unsigned int length)
{
  char message[length];
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    message[i] = (char)payload[i];
  }
  message[length] = 0;
  Serial.println(message);

  if (String(message) == "OPENLED")
  {
    digitalWrite(BUILTIN_LED, LOW); // Turn the LED on
  }
  else if (String(message) == "CLOSELED")
  {
    digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off
  }
  else
  {
    myServo.write(String(message).toInt());
    delay(1000);
    myServo.write(90);
  }
}

void connectMqtt()
{
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqttClientId, mqttUserName, mqttPassword))
    {
      Serial.println("connected");
      client.subscribe(mqttSubTopic);
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
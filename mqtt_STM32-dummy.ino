#include <Wire.h>
#include <PubSubClient.h>
#include <LwIP.h>
#include <STM32Ethernet.h>
#include <SPI.h>



float val;
IPAddress ip(192, 168, 2, 226);
IPAddress server(192, 168, 2, 224);


// byte mac[]    = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xE6 };
byte mac[]    = {  0x00, 0x80, 0xE1, 0x01, 0x01, 0x01 };
// byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

EthernetClient ethClient;
PubSubClient client (ethClient);

long lastMsg = 0;
char msg[50];
int value = 0;
float Temperature = 0;
float PressureOne = 0;
float PressureTwo = 0;
float PressureThree = 0;
float PressureFour = 0;
float Compass = 0;
float Gyroscope = 0;
float Depth = 0;



 void setup() {
  Serial.begin(115200);
  Wire.begin();
  client.setServer(server, 1883);
  client.setCallback(callback);
  // client.begin(net);
  // client.onMessage(callback);
  pinMode(LED_RED, OUTPUT);
  Ethernet.begin(mac, ip);
  // connect ();
  delay(1500);
  
}


  
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageWheelOne;
  String messageWheelTwo;
  String messageClaws;
  String messageJetPump;
  String messageFlowControl;
 
  
  

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageWheelOne += (char)message[i];
    messageWheelTwo += (char)message[i];
    messageClaws += (char)message[i];
    messageJetPump += (char)message[i];
    messageFlowControl += (char)message[i];
    
    
    
    
    
  }
  Serial.println();

  //WheelOne
  if (String(topic) == "nnnnn                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        k") {
    Serial.print("Changing output to ");
    if(messageWheelOne == "on"){
      Serial.println("on");
      digitalWrite(LED_RED, HIGH);
    }
    else if(messageWheelOne == "off"){
      Serial.println("off");
      digitalWrite(LED_RED, LOW);
    }
  }

  
  if (String(topic) == "WheelLeft") {
    Serial.print("Changing output to ");
    if(messageWheelOne == "on"){
      Serial.println("on");
      digitalWrite(LED_RED, HIGH);
    }
    else if(messageWheelOne == "off"){
      Serial.println("off");
      digitalWrite(LED_RED, LOW);
    }
  }

  //WheelTwo
  if (String(topic) == "WheelForward") {
    Serial.print("Changing output to ");
    if(messageWheelTwo == "on"){
      Serial.println("on");
      digitalWrite(LED_RED, HIGH);
    }
    else if(messageWheelTwo == "off"){
      Serial.println("off");
      digitalWrite(LED_RED, LOW);
    }
  }

  if (String(topic) == "WheelStop") {
    Serial.print("Changing output to ");
    if(messageWheelTwo == "on"){
      Serial.println("on");
      digitalWrite(LED_RED, HIGH);
    }
    else if(messageWheelTwo == "off"){
      Serial.println("off");
      digitalWrite(LED_RED, LOW);
    }
  }

  //Claws
  if (String(topic) == "ClawsUp") {
    Serial.print("Changing output to ");
    if(messageClaws == "on"){
      Serial.println("on");
      digitalWrite(LED_RED, HIGH);
    }
    else if(messageClaws == "off"){
      Serial.println("off");
      digitalWrite(LED_RED, LOW);
    }
  }
   
    
    if (String(topic) == "ClawsDown") {
    Serial.print("Changing output to ");
    if(messageClaws == "on"){
      Serial.println("on");
      digitalWrite(LED_RED, HIGH);
    }
    else if(messageClaws == "off"){
      Serial.println("off");
      digitalWrite(LED_RED, LOW);
    }
  }

  //JetPump
  if (String(topic) == "JetPumpOn") {
    Serial.print("Changing output to ");
    if(messageJetPump == "on"){
      Serial.println("on");
      digitalWrite(LED_RED, HIGH);
    }
    else if(messageJetPump == "off"){
      Serial.println("off");
      digitalWrite(LED_RED, LOW);
    }
  }

  
  if (String(topic) == "JetPumpOff") {
    Serial.print("Changing output to ");
    if(messageJetPump == "on"){
      Serial.println("on");
      digitalWrite(LED_RED, HIGH);
    }
    else if(messageJetPump == "off"){
      Serial.println("off");
      digitalWrite(LED_RED, LOW);
    }
  }

  //FlowControl
   if (String(topic) == "FlowControl") {
    Serial.print("Changing output to ");
    if (messageFlowControl == "691"){
      Serial.println("691");
    }
   }
}

void reconnect() {
 while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // String clientId = "ESP8266Client";
    // String clientId = "STM32EthernetClient";
    // clientId += String(random(0xffff), HEX);
   
    if (client.connect("ControllingClient")) {
      Serial.println("connected");
      
      client.subscribe("WheelRight");
      client.subscribe("WheelLeft");
      client.subscribe("WheelForward");
      client.subscribe("WheelStop");
      client.subscribe("ClawsUp");
      client.subscribe("ClawsDown");
      client.subscribe("JetPumpOn");
      client.subscribe("JetPumpOff");
      client.subscribe("FlowControl");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
     
      delay(5000);
    }
  }
}



void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 500) {
    lastMsg = now;
    value++;
    

    Temperature = 888;
    char TempString[11];
    dtostrf(Temperature, 1, 2, TempString);
    Serial.print("Temperature: ");
    Serial.println(TempString);
    client.publish("Temperature", TempString);

    PressureOne = 666; 
    char PressureOneString[11];
    dtostrf(PressureOne, 1, 3, PressureOneString);
    Serial.print("Pressure1.1: ");
    Serial.println(PressureOneString);
    client.publish("Pressure1.1", PressureOneString);

    PressureTwo = 456; 
    char PressureTwoString[11];
    dtostrf(PressureTwo, 1, 2, PressureTwoString);
    Serial.print("Pressure1.2: ");
    Serial.println(PressureTwoString);
    client.publish("Pressure1.2", PressureTwoString);

    PressureThree = 123; 
    char PressureThreeString[12];
    dtostrf(PressureThree, 1, 4, PressureThreeString);
    Serial.print("Pressure2.1: ");
    Serial.println(PressureThreeString);
    client.publish("Pressure2.1", PressureThreeString);

    PressureFour = 678; 
    char PressureFourString[13];
    dtostrf(PressureFour, 1, 2, PressureFourString);
    Serial.print("Pressure2.2: ");
    Serial.println(PressureFourString);
    client.publish("Pressure2.2", PressureFourString);

    Compass = 856; 
    char CompassString[6];
    dtostrf(Compass, 1, 3, CompassString);
    Serial.print("Compass: ");
    Serial.println(CompassString);
    client.publish("Compass", CompassString);

    Gyroscope = 483; 
    char GyroscopeString[6];
    dtostrf(Gyroscope, 1, 4, GyroscopeString);
    Serial.print("Gyroscope: ");
    Serial.println(GyroscopeString);
    client.publish("Gyroscope", GyroscopeString);

    Depth = 785; 
    char DepthString[5];
    dtostrf(Depth, 1, 4, DepthString);
    Serial.print("Depth: ");
    Serial.println(DepthString);
    client.publish("Depth", DepthString);
  
  }
    
  
}

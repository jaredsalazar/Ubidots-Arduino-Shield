  #include <SPI.h>
  #include <Ethernet.h>

  byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  EthernetClient client;

  String temp   = "552269de762542099f320374";
  String touch  = "552269a87625420b598a63f7";
  String push   = "552269c3762542099f32036c";
  String light  = "552267cb7625420953213dba";
  String token  = "psjhDslSBTrTlzfpRi0CeMTPCYPml5ZGF1yKZHgFxF0aAu2NyLwT7HmZqHas";
 
  void setup() {
    
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
       Serial.println("Failed to configure Ethernet using DHCP");
       for(;;);
  }
  delay(1000);
  Serial.println("connecting...");
  }

  void loop() {
  int temp_data = analogRead(A0);
  int touch_data = analogRead(A1);
  int push_data = analogRead(A2);
  int light_data = analogRead(A3);
  
  
  int num=0;
  String var = "[{\"variable\": \""+temp+"\", \"value\": "+String(temp_data)+"},{\"variable\": \""+touch+"\", \"value\": "+String(touch_data)+"}]";
  num = var.length();
  
  if(client.connect("things.ubidots.com", 80)){
    client.println("POST /api/v1.6/collections/values HTTP/1.1\nContent-Type: application/json\nContent-Length: "+String(num)+"\nX-Auth-Token: "+token+"\nHost: things.ubidots.com\n\n" + var);
    Serial.println("POST /api/v1.6/collections/values HTTP/1.1\nContent-Type: application/json\nContent-Length: "+String(num)+"\nX-Auth-Token: "+token+"\nHost: things.ubidots.com\n\n" + var);
    Serial.println("Session Close, Disconnecting!");
    client.stop();
    delay(10000);
  }else{
  Serial.println("connection failed");
  
  }
  
  }

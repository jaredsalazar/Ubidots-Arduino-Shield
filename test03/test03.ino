  #include <SPI.h>
  #include <Ethernet.h>

  byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  EthernetClient client;

  String idvariable = "55224ed87625425e75dc53ca";
  String token = "psjhDslSBTrTlzfpRi0CeMTPCYPml5ZGF1yKZHgFxF0aAu2NyLwT7HmZqHas";
 
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
  int val = analogRead(A0);
  int value = map(val, 0, 1023, 0, 255);
  
  int num=0;
  String var = "{\"value\":"+ String(value) + "}";
  num = var.length();
  
  if(client.connect("things.ubidots.com", 80)){
    client.println("POST /api/v1.6/variables/"+idvariable+"/values HTTP/1.1\nContent-Type: application/json\nContent-Length: "+String(num)+"\nX-Auth-Token: "+token+"\nHost: things.ubidots.com\n\n" + var);
    Serial.println("POST /api/v1.6/variables/"+idvariable+"/values HTTP/1.1\nContent-Type: application/json\nContent-Length: "+String(num)+"\nX-Auth-Token: "+token+"\nHost: things.ubidots.com\n\n" + var);
    Serial.println("Session Close, Disconnecting!");
    client.stop();
    delay(10000);
  }else{
  Serial.println("connection failed");
  
  }
  
  }

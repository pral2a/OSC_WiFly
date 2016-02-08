#include <WiFlyHQ.h>
#include <ArdOSCForWiFlyHQ.h>

WiFly wifly;
OSCServer server(&wifly);
OSCClient client(&wifly);

const int ledPin=13;
boolean running = false;

void setup()
{ 
  configureWiFlySerialHARDWARE( // 
  9600,                   // Wi-Fi module baudRate
  "COSM Net",             // Wi-Fi Network Name (SSID)
  "1c2c3c4c5c6c7",        // Wi-Fi Network Password
  "WiFly",                // for identification in the network
  "192.168.2.205",        // IP Adress of the Wifly. if 0 (without quotes), it will use dhcp to get an ip
  8000,                   // WiFly receive port
  "255.255.255.255",      // Where to send outgoing Osc messages. "255.255.255.255" will send to all hosts in the subnet
  8001                    // outgoing port
  );

  printWiFlyInfo(); //print some debug information 

  //set callback function
  server.addCallback("/1/toggle",&func1);

  pinMode(ledPin, OUTPUT);  

}


void loop()
{
  if(server.availableCheck()>0)
  {
  }
  delay(50);
}

void func1(OSCMessage *_mes){

  float value = _mes->getArgFloat(0);

  Serial.print("Received");
  Serial.println(value);

  if(value!=1) return;

  Serial.print(value);

  running = !running;                // toggle running variable
  digitalWrite(ledPin, running);      // indicate via LED

  /*
  
   //create new osc message
   OSCMessage newMes;
   
   newMes.beginMessage("/1/toggled");
   newMes.addArgInt32(flag);
   client.send(&newMes); //send osc message
   
   */

}







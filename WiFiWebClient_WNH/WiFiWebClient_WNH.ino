



/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using the WiFi module.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 Circuit:
 * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */


#include <SPI.h>
#include <WiFiNINA.h>
#include <tinyxml2.h>
//#include <yxml.h>


#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
//char ssid[] = SECRET_SSID;        // your network SSID (name)
//char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
char ssid[] = "BT-RXAGH3";
char pass[] = "QVqQrqYp3PKfaA";

//char ssid[] = "MakeMonmouth";
//char pass[] = "WeMakeThings!1";

int keyIndex = 0;            // your network key index number (needed only for WEP)

int counter = 0;            //counting the characters read in

boolean toggle = true;     //toggle that records the fact that the data read is complete

int datadepth = 0;          //variable that holds the amount of data left to read in

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "data.bus-data.dft.gov.uk";    // name of server

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiSSLClient client;


void setup() {
  
  using namespace tinyxml2;
  XMLDocument testdoc;

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to WiFi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connectSSL(server, 443)) {
    Serial.println("connected to server");
    // Make a HTTP request:

    client.println("GET https://data.bus-data.dft.gov.uk/api/v1/datafeed/?operatorRef=SCGL&lineRef=23&api_key=e3be106391929d2f9b3f6b01077797ded90c4f45");
    client.println("Host: data.bus-data.dft.gov.uk");
    client.println("Accept: application/xmlns");
    client.println("Connection: close");
    client.println();
  }

}

void loop() {

  using namespace tinyxml2;
  XMLDocument testdoc;
  //String d;
  String c;
  char * XMLString;
  String XMLShow;
  //Serial.println(c);
  
  //int counter;
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    XMLString  += c;
    XMLShow += c;
    //Serial.println(show);
    //Serial.println(XMLString);
    //d = d + c; //building up the string of stuff...
    //const char c = client.read();
    //std::string cstr = "c";
    //std::string c(client.read())
    
    //testdoc.Parse(c);
    //testdoc.Parse((c))filedata, 0, TIXML_ENCODING_UTF8);

    //int rslt = dxml.Parse(sxml.c_str());
    
    //int rslt = testdoc.Parse((client.read()))filedata, 0, TIXML_ENCODING_UTF8);
    //int rslt = testdoc.Parse(c);
    //Serial.write(c);


    //delay(1000);

     counter++;
     Serial.println(counter);

     //if (counter==6000){
      //Serial.print(XMLString);
      //Serial.println();
      //Serial.println();
      //Serial.print(show);
      
      //Serial.println("count complete");

      //Serial.println("This is the stuff");

      
      
      //Serial.println(counter);
     }

     //serial.println(counter);

//}
 //   if(testdoc.Parse(XMLString)!= XML_SUCCESS){
 //     Serial.println("Error parsing");  
 //     return;
  //Serial.print(show);
  //Serial.println(counter);
  

  //Serial.println(client.available());

  //datadepth=client.available();
  //Serial.println(datadepth);
  //Serial.println("This is the depth");
  //}

  //Serial.print(XMLString);
  //testdoc.Parse(XMLString);

  Serial.print(toggle);

  if (toggle){

    Serial.print("length of string is...");
    //Serial.println(counter);
    //int rslt = testdoc.Parse(d);
    //testdoc.Parse(d);
    //Serial.println(XMLString);
    Serial.print(show);
    toggle = false;
  }
  }


  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }

    
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

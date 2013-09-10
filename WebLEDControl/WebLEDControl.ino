/*
  Web Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 4 Sep 2010
 by Tom Igoe
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,100, 250);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup()
{
  Serial.begin(9600);    //  open up serial port connection to PC
  pinMode(8, OUTPUT);    //  Set digital pin 8 as output
  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    String buffer = "";  //  Declare the buffer variable

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);  //  Send every character read to serial port 
        buffer+=c;        //  Assign to the buffer

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();

          if (digitalRead(8)){  //  1<-- Display LED status
            client.print(" LED is ON");
          }else{
            client.print(" LED is OFF");
          }
          client.println("<br />");
          
          // 2<-- Create a form
          client.print("<FORM action=\"http://192.168.100.250/\" >");
          client.print("<P> <INPUT type=\"radio\" name=\"status\" value=\"1\">ON");
          client.print("<P> <INPUT type=\"radio\" name=\"status\" value=\"0\">OFF");
          client.print("<P> <INPUT type=\"submit\" value=\"Submit\"> </FORM>");
            
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          buffer="";       //  Clear the buffer at end of line
        } else if (c == '\r') {            
          if(buffer.indexOf("GET /?status=1")>=0)
            digitalWrite(8,HIGH);  // Catch ON status and set LED
          
          if(buffer.indexOf("GET /?status=0")>=0)
            digitalWrite(8,LOW);  // Catch OFF status and set LED
        }
        else {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}


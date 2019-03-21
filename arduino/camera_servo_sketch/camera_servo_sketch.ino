#include <Adafruit_GPS.h>
#include <SoftwareSerial.h> // load software serial library - new serial ports on other pins
SoftwareSerial mySerial(3, 2); // Initialize the software serial port
Adafruit_GPS GPS(&mySerial); // GPS object

String NMEA1; // Variable for first NMEA sentence
String NMEA2; // Variable for second NMEA sentence
char c; // to read characters coming from the GPS
float degLat;
float degLon;
float degWhole;
float degDecimal;

void setup() {
  Serial.begin(9600); // Turn on serial monitor
  GPS.begin(9600); // Turn on GPS at 9600 baud
  GPS.sendCommand("$PGDMD,33,0*6D"); // turn off antenna update data
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ); // Set update rate to 10 hz
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // we want RMC and GGA sentences only
  delay(1000);
}

void loop() {
  readGPS();
  delay(250);
}

void readGPS() {
  clearGPS();

  while (!GPS.newNMEAreceived()) {
    c = GPS.read();
  } // drops out when we have one of the sentences

  GPS.parse(GPS.lastNMEA()); // Parse that last good NMEA sentence
  NMEA1 = GPS.lastNMEA();

  while (!GPS.newNMEAreceived()) {
    c = GPS.read();
  } // drops out when we have one of the sentences

  GPS.parse(GPS.lastNMEA()); // Parse that last good NMEA sentence
  NMEA2 = GPS.lastNMEA();

  degWhole = float(int(GPS.latitude / 100));
  degDecimal = (GPS.latitude - degWhole * 100) / 60;
  degLat = degWhole + degDecimal;

  if (GPS.lon == 'W')
    degLat = (-1) * degLat;

  degWhole = float(int(GPS.longitude / 100));
  degDecimal = (GPS.longitude - degWhole * 100) / 60;
  degLon = degWhole + degDecimal;

  if (GPS.lon == 'S')
    degLon = (-1) * degLon;

  Serial.print(degLat, 4);
  Serial.print(",");
  Serial.print(degLon, 4);
  //Serial.print(",");
  //Serial.print(GPS.altitude);
  Serial.println("");
}

void clearGPS() { // clear old and corrupted data from serial port
  while (!GPS.newNMEAreceived()) {
    c = GPS.read();
  } // drops out when we have one of the sentences
  GPS.parse(GPS.lastNMEA()); // Parse that last good NMEA

  while (!GPS.newNMEAreceived()) {
    c = GPS.read();
  } // drops out when we have one of the sentences
  GPS.parse(GPS.lastNMEA()); // Parse that last good NMEA

  while (!GPS.newNMEAreceived()) {
    c = GPS.read();
  } // drops out when we have one of the sentences
  GPS.parse(GPS.lastNMEA()); // Parse that last good NMEA
}

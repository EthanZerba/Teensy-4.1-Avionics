#include "ultimategps.h"

#include <Adafruit_GPS.h>


// what's the name of the hardware serial port?
#define GPSSerial Serial4

float latitude, longitude, altitudeGPS, speed, heading;
Adafruit_GPS GPS(&GPSSerial);

#define GPSECHO false

uint32_t timer = millis();

void initUltimateGPS() {
  // make this baud rate fast enough to we aren't waiting on it
  // wait for hardware serial to appear
  // 9600 baud is the default rate for the Ultimate GPS
    GPS.begin(9600);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  // Ask for firmware version
  GPSSerial.println(PMTK_Q_RELEASE);
  delay(1000);
}



void readUltimateGPS() {
    Serial.println(GPS.fix ? "GPS module has a fix" : "GPS module does not have a fix");
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) {
      Serial.println("Failed to parse NMEA sentence");
      return;
    }
    latitude = GPS.latitudeDegrees;
    longitude = GPS.longitudeDegrees;
    altitudeGPS = GPS.altitude;
    speed = GPS.speed;
    heading = GPS.angle;
  } else {
    Serial.println("No new NMEA sentence received");
  }
}
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

/*
 * September 30 2023
 * Ammar Bhayat
 * Arduino GPS
 */

//variable to store current page number being displayed on the OLED display
int page = 0;

//digital pin for button input. Put a resistor from this pin to ground. A wire then connects from the pin to one side of a switch. The other end of the switch goes to positive rail.
int button = 4;

//general constants 
double radius_earth = 6370;
double pi = 3.14159265358979;



/*
 * The following section is used to declare the lat and lng values for any number of locations
 * The distance from the current location recived to the locations declared below will be displayed on their own page number on the OLED
 */
//Ottawa
double ottawa_lat = 45.424721;
double ottawa_lng =  -75.695000;
double d = 0;
//North Pole
double northPole_lat = 90;
double northPole_lng =  135;
double d1 = 0;
//Madrid
double madrid_lat = 40.416775;
double madrid_lng = -3.703790;
double d2 = 0;
//New York
double CNTower_lat = 43.642227;
double CNTower_lng = -79.387108;
double d3 = 0;
//London Trafalgar Square
double london_lat = 51.507955;
double london_lng = -0.128029;
double d4 = 0;
//Paris
double paris_lat = 48.864716;
double paris_lng = 2.349014;
double d5 = 0;
//Chuck E Cheese Vaughn
double chuckECheeseVaughn_lat = 43.828250;
double chuckECheeseVaughn_lng = -79.542166;
double d6 = 0;
//MDHS
double MDHS_lat = 43.880234;
double MDHS_lng = -79.252412;
double d7 = 0;



double d8 = 0;
double input1 = 0;
double input2 = 0;
unsigned long timeNow = 0;
#define TWO_SEC     2000


//GPS Setup
//GPS pins RX/TX
//Connect to GPS TX
int RXPin = 2;
//Connect to GPS RX
int TXPin = 3;

int GPSBaud = 9600;
int GPSupdateFLAG = 1;
TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin,TXPin);

//OLED Setup
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {

  //setup button
  pinMode(button, INPUT);

  //setup serial communication to PC
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }


  //Welcome Screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(0,0);
  display.println(F("Arduino GPS"));
  display.println(F("Ammar Bhayat"));
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  
      display.clearDisplay(); 
      display.setTextSize(1);            
      display.setTextColor(SSD1306_WHITE);     
if(digitalRead(button) == 1){
  page = page + 1;
  delay(250);
  if(page == 11){
    page = 0;
  }
}
    if(page == 0){
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("POSITION DATA");
      display.print("Lat: ");
      display.println(gps.location.lat(),5);
      display.print("Lon: ");
      display.println(gps.location.lng(),5);
      display.print("Alt: ");
      display.println(gps.altitude.meters(),5);
     }
      if(page == 1){
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Speed ");
      display.println(d8,5);
     }
     if(page == 10){
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Ottawa: ");
      display.println(d,5);
     }
    if(page == 3){
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("North Pole:");
      display.println(d1,5);
    }
    if(page == 4){
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Madrid: ");
      display.println(d2,5);
     }
     if(page == 5){
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("CN Tower ");
      display.println(d3,5);
     }
     if(page == 6){
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Trafalgar Square ");
      display.println(d4,5);
     }
     if(page == 7){
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Paris ");
      display.println(d5,5);
     }
     if(page == 8){
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Chuck E Cheese ");
      display.println(d6,5);
     }
     if(page == 9){
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("MDHS ");
      display.println(d7,5);
     }
     if(page == 2){
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("DATE");
     display.print(gps.date.month());
    display.print("/");
    display.print(gps.date.day());
    display.print("/");
    display.println(gps.date.year());
    
     }
    
     
          
  display.display();

  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();
    
  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }


  }



  
 


void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());    

  d =  slaveAlgebra(ottawa_lat,ottawa_lng);
  d1 = slaveAlgebra(northPole_lat,northPole_lng);
  d2 = slaveAlgebra(madrid_lat,madrid_lng);
  d3 = slaveAlgebra(CNTower_lat,CNTower_lng);
  d4 = slaveAlgebra(london_lat,london_lng);
  d5 = slaveAlgebra(paris_lat,paris_lng);
  d6 = slaveAlgebra(chuckECheeseVaughn_lat,chuckECheeseVaughn_lng);
  d7 = slaveAlgebra(MDHS_lat, MDHS_lng);
  d8 = gps.speed.kmph();
  
      display.setCursor(90,0);
      if(GPSupdateFLAG == 1){
  display.print('*');
   GPSupdateFLAG = 0;
  }
    if(GPSupdateFLAG == 0){
  display.print(' ');
  GPSupdateFLAG = 1;
  }
  }
  else
  {
    Serial.println("Location: Not Available");
  }




  //Serial Monitor Output
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  
}










double slaveAlgebra(double lat, double lon){
  double phi1 = lat*(pi/180);
  double phi2 = gps.location.lat()*(pi/180);
  double phi3 = (gps.location.lat()-lat)*(pi/180);

  double lambda = (gps.location.lng()-lon)*(pi/180);

  double a = sin(phi3*0.5)*sin(phi3*0.5)+cos(phi1)*cos(phi2)*sin(lambda*0.5)*sin(lambda*0.5);
  double c = 2*(atan(sqrt(a)/sqrt(1-a)));
  double dog = radius_earth*c;
  return dog;
  Serial.println(dog);    
}

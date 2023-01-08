
// Include Libraries
#include "Arduino.h"
#include "LDR.h"
#include "LED.h"


// Pin Definitions
#define IROBJAVOID_1_PIN_OUT	2
#define IROBJAVOID_2_PIN_OUT	3
#define LDR_PIN_SIG	A3
#define LEDR_1_PIN_VIN	5
#define LEDR_2_PIN_VIN	6



// Global variables and defines
#define THRESHOLD_ldr   100
int ldrAverageLight;
// object initialization
LDR ldr(LDR_PIN_SIG);
LED ledR_1(LEDR_1_PIN_VIN);
LED ledR_2(LEDR_2_PIN_VIN);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    pinMode(IROBJAVOID_1_PIN_OUT, INPUT);
    pinMode(IROBJAVOID_2_PIN_OUT, INPUT);
    ldrAverageLight = ldr.readAverage();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // IR Obstacle Avoidance Sensor #1 - Test Code
    //Read IR obstacle Sensor. irObjAvoid_1Var will be '1' if an Obstacle was detected
    //Use the onboard trimmer to set the distance of alert
    bool irObjAvoid_1Var = !digitalRead(IROBJAVOID_1_PIN_OUT);
    Serial.print(F("ObjAvoid: ")); Serial.println(irObjAvoid_1Var);

    }
    else if(menuOption == '2') {
    // IR Obstacle Avoidance Sensor #2 - Test Code
    //Read IR obstacle Sensor. irObjAvoid_2Var will be '1' if an Obstacle was detected
    //Use the onboard trimmer to set the distance of alert
    bool irObjAvoid_2Var = !digitalRead(IROBJAVOID_2_PIN_OUT);
    Serial.print(F("ObjAvoid: ")); Serial.println(irObjAvoid_2Var);

    }
    else if(menuOption == '3') {
    // LDR (Mini Photocell) - Test Code
    // Get current light reading, substract the ambient value to detect light changes
    int ldrSample = ldr.read();
    int ldrDiff = abs(ldrAverageLight - ldrSample);
    Serial.print(F("Light Diff: ")); Serial.println(ldrDiff);

    }
    else if(menuOption == '4') {
    // LED - Basic Red 5mm #1 - Test Code
    // The LED will turn on and fade till it is off
    for(int i=255 ; i> 0 ; i -= 5)
    {
    ledR_1.dim(i);                      // 1. Dim Led 
    delay(15);                               // 2. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }                                          
    ledR_1.off();                        // 3. turns off
    }
    else if(menuOption == '5') {
    // LED - Basic Red 5mm #2 - Test Code
    // The LED will turn on and fade till it is off
    for(int i=255 ; i> 0 ; i -= 5)
    {
    ledR_2.dim(i);                      // 1. Dim Led 
    delay(15);                               // 2. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }                                          
    ledR_2.off();                        // 3. turns off
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) IR Obstacle Avoidance Sensor #1"));
    Serial.println(F("(2) IR Obstacle Avoidance Sensor #2"));
    Serial.println(F("(3) LDR (Mini Photocell)"));
    Serial.println(F("(4) LED - Basic Red 5mm #1"));
    Serial.println(F("(5) LED - Basic Red 5mm #2"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing IR Obstacle Avoidance Sensor #1"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing IR Obstacle Avoidance Sensor #2"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing LDR (Mini Photocell)"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing LED - Basic Red 5mm #1"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing LED - Basic Red 5mm #2"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}


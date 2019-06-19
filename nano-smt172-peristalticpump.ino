// peristalticpump control and a smt172 temperature sensor
//by nrbrt
//GPLv3 applies

#include <AccelStepper.h>
#include <SMT172.h>

//Define stepper motor connections
#define dirPin 12
#define stepPin 11

//Create stepper object
AccelStepper stepper(1,stepPin,dirPin); //motor interface type must be set to 1 when using a driver.

long last_update = 0;
long last_measured = 0;
long time_now;
float temp = 0;
String str;
int iCount, i;
String sParams[6];
bool accset = false;
bool maxset = false;

void setup() {
  Serial.begin(115200);
}


void loop() {
  time_now = millis();

  if((time_now - last_update >= 1000) && (temp != 0)){
        Serial.println(temp);
        temp = 0;
        stepper.runSpeed();
        last_update = millis();
  }

  if(time_now - last_measured >= 500){
    getTemp();
    stepper.runSpeed();
    last_measured = millis();
  }

  if(Serial.available() > 0){
     str = Serial.readStringUntil('\n');
     iCount = StringSplit(str,':',sParams,6);

     //rotate at certain speed with certain acceleration.
     if(sParams[0] == "rot"){
        if(accset && maxset){
          stepper.setSpeed(sParams[1].toFloat());        
        }
     }
     
     if(sParams[0] == "max" && sParams[1].toFloat() > 0){
        stepper.setMaxSpeed(sParams[1].toFloat());
        maxset = true;
     }

     if(sParams[0] == "acc" && sParams[1].toFloat() > 0){
        stepper.setAcceleration(sParams[1].toFloat());
        accset = true;
     }
     
  }
  stepper.runSpeed();
}


void getTemp(){
  SMT172::startTemperature(0.001);
  repeat:
  switch (SMT172::getStatus()) {
    case 0: stepper.runSpeed();goto repeat;
    case 1: 
      temp = SMT172::getTemperature();
      stepper.runSpeed();
      break;
    case 2:
      Serial.println("no sensor");
      stepper.runSpeed();
  }
}

int StringSplit(String sInput, char cDelim, String sParams[], int iMaxParams)
{
    int iParamCount = 0;
    int iPosDelim, iPosStart = 0;

    do {
        // Searching the delimiter using indexOf()
        iPosDelim = sInput.indexOf(cDelim,iPosStart);
        if (iPosDelim > (iPosStart+1)) {
            // Adding a new parameter using substring() 
            sParams[iParamCount] = sInput.substring(iPosStart,iPosDelim);
            iParamCount++;
            // Checking the number of parameters
            if (iParamCount >= iMaxParams) {
                return (iParamCount);
            }
            iPosStart = iPosDelim + 1;
        }
    } while (iPosDelim >= 0);
    if (iParamCount < iMaxParams) {
        // Adding the last parameter as the end of the line
        sParams[iParamCount] = sInput.substring(iPosStart);
        iParamCount++;
    }

    return (iParamCount);
}



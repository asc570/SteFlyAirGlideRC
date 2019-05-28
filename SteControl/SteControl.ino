// SteControl.ino
//
///////////////////////////////////////////////////////////////////
//
// This sketch will drive the RemoteControl using class BasicControl.
//
// Type of remote control device:
// 'SteFly Remote-Knueppelgriff' 
//
// From:
// Stefan Langer
//
// Link:
// https://www.stefly.aero/product/stefly-leather-remote-stick/
//
// Type of device for display :
//  AirGlide DisplayLarge
//
// from:
// AirAvionics
//
// link:
// http://www.air-store.eu/epages/AIRStore-LuftfahrtbedarfundAvionik.sf/de_DE/?ObjectPath=/Shops/AIRStore-LuftfahrtbedarfundAvionik/Products/T279
//
//////////////////////////////////////////////////////////////////////
//
// #define DEBUG

#include <Bounce2.h>
#include <Keyboard.h>
#include "SteControl.h"
#include "KeyMap.h"

#ifdef DEBUG
bool bLoop = false;
#endif
//
// stateless control
//
BasicControl Control{pKm01,intBounceIntervall};
//
////////////////////////////////////////////////////////
//
void setup() {

#ifdef DEBUG
  Serial.begin(9600);
  while(!Serial);
  Serial.println(F("Begin: setup()"));
#endif

Control.setup();
Keyboard.begin();
 
#ifdef DEBUG
  Serial.println(F("End: setup()"));
#endif
}
//
/////////////////////////////////////////////////////
//
void loop() {

#ifdef DEBUG
  if(!bLoop){
  Serial.println(F("Inside: loop()"));
    bLoop = true;
  }
#endif

  Control.loop();
}

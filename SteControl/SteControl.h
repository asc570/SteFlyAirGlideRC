// SteControl.h  
//
#ifndef STECONTROL_H
#define STECONTROL_H
////////////////////////////////////////////
//
// struct KeyMap
//
// binding: Arduino_pin -> key pressed send from keyboard
// if one key has to be hold pressed this is given by the hold_key member.
//
const uint8_t NOKEY{0x0};
//
struct KeyMap{
  KeyMap(const uint8_t p, const uint8_t k, const uint8_t h)   : pin{p},key{k},hold_key{h}       {};
  KeyMap(const uint8_t p, const uint8_t k)                    : pin{p},key{k},hold_key{NOKEY}   {};
  const uint8_t     pin;    
  const uint8_t     key; 
  const uint8_t     hold_key;
};
//
////////////////////////////////////////////////////////////////////////////////////
// 
// ************** AIR Glide Display M/L***********************************
//
// the controls on the AirGlide Display M/L from left to right:
//
// - Cursor-Rotary2, left side
// - Button-Aircraft symbol (HOME)
// - Button-Display (DSP)
// - Button-Escape (ESC)
// - Menu-Rotary1 , right side
//
//////////
//
// info from AirAvionic (Tobias Fetzer)
// AirGlide          : Keyboard
// --------------------------------
// Rotary2            : rotate ->(KEY_UP_ARROW / KEY_DOWN_ARROW) ; press -> (KEY_ESC)
// HOME               : KEY_F3
// DSP                : KEY_F2
// ESC                : KEY_F1
// Rotary1            : rotate ->(KEY_LEFT_ARROW / KEY_RIGHT_ARROW ) ; press -> (KEY_RETURN)
//
//////////////////////////////////////////////////////
//
// ************************** SteFly RemoteControl ******************************
//
// all buttons & joystic controls om the SteFly :
//
const uint8_t ButTop_09       = 9;     // top button (Fn)
const uint8_t ButRhUpper_14   = 14;    // upper LH button (M)
const uint8_t ButRhLower_15   = 15;    // lower RH button (X)  

const uint8_t JoyUp_02      = 2;    // joystick UP
const uint8_t JoyDown_04    = 4;    // joystick DOWN
const uint8_t JoyLeft_05    = 5;    // joystick LEFT
const uint8_t JoyRight_03   = 3;    // joystick RIGHT
const uint8_t JoyPress_06   = 6;    // joystick PRESS
//
//
// the SteFly RemoteControl can issue a total of 8 different commands
//
const uint8_t NUM_SteCOMMANDS {8};
//
typedef KeyMap ArrSteKeyMap_t[NUM_SteCOMMANDS];
//
/////////////////////////////////////////////////////////////
//
// class BasicControl
//
// A BasicControl object is used to:
// - read button press events from the remote control stick
// - send the mapped Keyboard.press() signal via USB
//
// The mapping button -> Keyboard key is defined in a KeyMap[] defined by a *.h file.
// - stateless mapping.
//
// Remote Control used:
// 'SteFly Remote-Knueppelgriff' 
// from Stefan Langer
// https://www.stefly.aero/product/stefly-leather-remote-stick/
//
// The board used by this controller is a Arduino Leonardo.
//
// Remark:
// class BasicControl is stateless. For each input (key pressed) there will always be the same output.
// To make it possible to derive a statefull class from class BasicControl, loop() and ButPushAction() are not declared const.
// Use a virtual ButPushAction() in the derived class to make the derived class statefull.
//
////////////////////////////////////////////////////////////////
//
 const uint16_t intBounceIntervall {25};   // debounce intervall in milliseconds
 //
class BasicControl{
public:
  BasicControl(const ArrSteKeyMap_t   pKm,  const uint16_t iBounceIv ) :  
                                                                _iBounceIv    { iBounceIv  }, 
                                                                _pKm          {pKm},
                                                                _numCommands  {NUM_SteCOMMANDS},
                                                                _pBut          {NULL} 
                                                                {}   
/////////////////////////////////////////////////////////////
//                                                                   
  virtual ~BasicControl() {
  if(_pBut != NULL)
  {
    delete _pBut;
  }
}    
/////////////////////////////////////////////////////////////
//
void setup(){
   if(_pBut == NULL){
    _pBut = new Bounce[_numCommands];
      if(_pBut != NULL){
        for (int8_t i=0; i < _numCommands;i++){
#ifdef DEBUG          
          Serial.print(F("Inside: BasicControl.setup() , Bounce.attach() button no:" ));
          Serial.println(i);
#endif          
          _pBut[i].attach(_pKm[i].pin,INPUT_PULLUP);
          _pBut[i].interval(_iBounceIv);
        }
      }
    }     
}
/////////////////////////////////////////////////////////
//
void loop(){
    if(_pBut != NULL){
      for(int8_t i = 0; i < _numCommands;i++){
        if(_pBut[i].update() && _pBut[i].fell()){
#ifdef DEBUG          
          Serial.print(F("Inside: BasicControl.loop(), pressed: "));
          Serial.println(i);
#endif            
          ButPushAction(i);
        }
      }
    }    
}  
//////////////////////////////////////////////////////////
//
protected:
//
  virtual void ButPushAction(int8_t i){
  #ifdef DEBUG          
          Serial.print(F("Inside: BasicControl.ButPushAction, key No: "));
          Serial.println(i);
  #endif  
    Keyboard.releaseAll();      
    if(_pKm[i].hold_key != NOKEY){
      Keyboard.press(_pKm[i].hold_key);
    }
    Keyboard.press(_pKm[i].key);
    Keyboard.releaseAll(); 
}
/////////////////////////////////////////////
//
  const size_t            _numCommands;
  const uint16_t          _iBounceIv;
  const KeyMap *  const   _pKm;

  Bounce *                _pBut;
};
///////////////////////////////////////////
//
#endif  // STECONTROL_H

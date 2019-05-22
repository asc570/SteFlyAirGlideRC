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
class BasicControl{
public:
  BasicControl(const KeyMap * const pKm, const size_t numBut, const uint16_t iBounceIv ) :  
                                                                _iBounceIv  { iBounceIv  }, 
                                                                _pKm        {pKm},
                                                                _numBut     {numBut},
                                                                _pBut       {NULL} 
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
    _pBut = new Bounce[_numBut];
      if(_pBut != NULL){
        for (int8_t i=0; i < _numBut;i++){
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
      for(int8_t i = 0; i < _numBut;i++){
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
  const size_t            _numBut;
  const uint16_t          _iBounceIv;
  const KeyMap *  const   _pKm;

  Bounce *                _pBut;
};
///////////////////////////////////////////
//
#endif  // STECONTROL_H

#ifndef KEYMAP_H
#define KEYMAP_H
/////////////////////////////////////////////////////////////////
// ButtonNames and PinNumbers are for the: 
// 'SteFly Remote-Knueppelgriff' 
// from Stefan Langer
// https://www.stefly.aero/product/stefly-leather-remote-stick/
//
// pin -> button layout
// button names -> pin PosSwitch_PinNumber
//
// Modifier keys as of:
// https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
// If a hold key is used, it is specified in the KeyMap ctor position no. 3.
//
/////////////////////////////////////////////////////
//
// info from AirAvionic (Tobias Fetzer)
// AirGlide          : Tastatur
// -----------------------
// ESC                : F1
// DSP                : F2
// Flugzeug           : F3
// Rotary 1 (rechts)  : rotate: Pfeil Links/Rechts; press: Enter
// Rotary 2 (links)   : rotate: Pfeil Auf/Ab;       press: ESC
//
//////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////
//                              
const KeyMap pKm01[] = {
  KeyMap {ButTop_09,        KEY_F3},
  KeyMap {ButRhUpper_14,    KEY_ESC},
  KeyMap {ButRhLower_15,    KEY_F1},
  KeyMap {JoyUp_02,         KEY_LEFT_ARROW,     KEY_RETURN},  // zoom out
  KeyMap {JoyDown_04,       KEY_RIGHT_ARROW,    KEY_RETURN},  // zoom in
  KeyMap {JoyRight_03,      KEY_RIGHT_ARROW},  
  KeyMap {JoyLeft_05,       KEY_LEFT_ARROW},
  KeyMap {JoyPress_06,      KEY_RETURN  }  
 };
//
////////////////////////////////////////////////////
//
 const uint16_t intBounceIntervall {25};   // debounce intervall in milliseconds
 #endif   // KEYMAP_H
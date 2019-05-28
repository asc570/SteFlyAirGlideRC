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
const ArrSteKeyMap_t pKm01 = {
  KeyMap {ButTop_09,        KEY_F3},
  KeyMap {ButRhUpper_14,    KEY_ESC},
  KeyMap {ButRhLower_15,    KEY_F1},
  KeyMap {JoyUp_02,         KEY_LEFT_ARROW,     KEY_RETURN},  // zoom out
  KeyMap {JoyDown_04,       KEY_RIGHT_ARROW,    KEY_RETURN},  // zoom in
  KeyMap {JoyRight_03,      KEY_RIGHT_ARROW},  
  KeyMap {JoyLeft_05,       KEY_LEFT_ARROW},
  KeyMap {JoyPress_06,      KEY_RETURN  }  
 };
////////////////////////////////////////////////////
//
 #endif   // KEYMAP_H
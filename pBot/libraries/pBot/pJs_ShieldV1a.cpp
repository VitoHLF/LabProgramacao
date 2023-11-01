#include "pJs_ShieldV1a.h"

////////////////////////////////////////////////////////////////////////////
///
/// Class JoyStickShield
///
JoyStickShield::JoyStickShield(): JoyStick(), PushButtonArray()
{
}

void JoyStickShield::begin()
{
  JoyStick::begin(X_AXIS_PIN, Y_AXIS_PIN, BT_Z_PIN);
  PushButtonArray::begin(JS_BUTTONS-1);
  addButton(BT_A_PIN, true);
  addButton(BT_B_PIN, true);
  addButton(BT_C_PIN, true);
  addButton(BT_D_PIN, true);
  addButton(BT_E_PIN, true);
  addButton(BT_F_PIN, true);
}

void JoyStickShield::axisConfig(int normalizeTo, byte tolerance, boolean zIgnoreXY)
{
  JoyStick::axisConfig(normalizeTo, tolerance, zIgnoreXY);
}

void JoyStickShield::run()
{
  JoyStick::run(); 
  PushButtonArray::run(); 
}


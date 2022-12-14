/////////////////////////////////////////////////////////////////
/*
  Button2.cpp - Arduino Library to simplify working with buttons.
  Created by Lennart Hennigs.
*/
/////////////////////////////////////////////////////////////////
#pragma once

#ifndef Button2_h
#define Button2_h

/////////////////////////////////////////////////////////////////

#include "Arduino.h"

/////////////////////////////////////////////////////////////////

#ifndef DEBOUNCE_MS
    #define DEBOUNCE_MS      40
#endif
#ifndef LONGCLICK_MS 
    #define LONGCLICK_MS    500
#endif
#ifndef DOUBLECLICK_MS
    #define DOUBLECLICK_MS  400
#endif 
#ifndef CAPACITIVE_TOUCH_THRESHOLD
    #define CAPACITIVE_TOUCH_THRESHOLD 35
#endif

#define SINGLE_CLICK      1
#define DOUBLE_CLICK      2
#define TRIPLE_CLICK      3
#define LONG_CLICK        4

/////////////////////////////////////////////////////////////////

class Button2 {
  protected:
    byte pin;
    bool capacitive = false;
    byte prev_state;
    byte state;
    byte pressed;
    byte click_count = 0;
    byte last_click_type = 0;
    unsigned long click_ms;
    unsigned long down_ms;
    unsigned int debounce_time_ms;
    unsigned int down_time_ms = 0;
    bool pressed_triggered = false;
    bool longclick_detected = false;
        
    typedef void (*CallbackFunction) (Button2&);

    CallbackFunction pressed_cb = NULL;
    CallbackFunction released_cb = NULL;
    CallbackFunction change_cb = NULL;
    CallbackFunction tap_cb = NULL;
    CallbackFunction click_cb = NULL;
    CallbackFunction long_cb = NULL;
    CallbackFunction double_cb = NULL;
    CallbackFunction triple_cb = NULL;
    
  public:
    Button2(byte attachTo, byte buttonMode = INPUT_PULLUP, boolean isCapacitive = false, boolean activeLow = true, unsigned int debounceTimeout = DEBOUNCE_MS);
    void setDebounceTime(unsigned int ms);
    void reset();
    
    void setChangedHandler(CallbackFunction f);
    void setPressedHandler(CallbackFunction f);
    void setReleasedHandler(CallbackFunction f);
    void setClickHandler(CallbackFunction f);
    void setTapHandler(CallbackFunction f);
    void setLongClickHandler(CallbackFunction f);
    void setDoubleClickHandler(CallbackFunction f);
    void setTripleClickHandler(CallbackFunction f);

    unsigned int wasPressedFor() const;
    boolean isPressed() const;
    boolean isPressedRaw() const;
    
    byte getNumberOfClicks() const;
    byte getClickType() const;
    
    bool operator==(Button2 &rhs);

    void loop();
};
/////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////

#ifndef __SELECTOR_HPP__
#define __SELECTOR_HPP__

#include <Arduino.h>
#include "stdint.h"
#include "debouncer.hpp"

#define SHORT_PRESS_TIMEOUT 1000

class Selector
{
public:
  typedef enum
  {
    CW_CB,
    CCW_CB,
    SW_SP_CB,
    SW_LP_CB,
    MAX_CB
  } CbType;

  typedef enum
  {
    PIN_STATE_LOW,
    PIN_STATE_HIGH
  } PinState;

  typedef enum
  {
    SW_STATE_INIT,
    SW_STATE_SHORT_PRESS,
    SW_STATE_LONG_PRESS,
  };

  typedef void (*Cb)();

  Selector(int clk, int dt, int sw)
  : m_clk_pin(clk), m_dt_pin(dt), m_sw_pin(sw), m_timer(SHORT_PRESS_TIMEOUT)
  {

  };
  
  void addCallback(CbType type, Cb cb)
  {
    if (type < MAX_CB)
    {
      m_cbs[type] = cb;
    }
  }

  void run()
  {
    processEncoder();
    processButton();    
  }

private:
  void callback(CbType type)
  {
    if ((type < MAX_CB) && (m_cbs[type] != nullptr))
    {
      m_cbs[type]();
    }
  }

  void processEncoder()
  {
    m_clk_curr_st = digitalRead(m_clk_pin);

    if ((m_clk_curr_st != m_clk_last_st) && (m_clk_curr_st == PIN_STATE_LOW))
    {
      if (digitalRead(m_dt_pin) != m_clk_curr_st)
      {
        callback(CCW_CB);
        Serial.print("[CCW]");
      }
      else
      {
        callback(CW_CB);
        Serial.print("[CW]");
      }
    }
    m_clk_last_st = m_clk_curr_st;
  }

  void processButton()
  {
    PinState sw_state = digitalRead(m_sw_pin);
    bool falling_edge = m_debouncer.onFallingEdge(sw_state);
    bool rising_edge = m_debouncer.onRisingEdge(sw_state);
    
    switch (m_sw_state)
    {
    case SW_STATE_INIT:
      if(falling_edge)
      {
        m_sw_state = SW_STATE_SHORT_PRESS;
        m_timer.start();
      }
      break;
    case SW_STATE_SHORT_PRESS:
      if(rising_edge)
      {
        m_sw_state = SW_STATE_INIT;
        m_timer.stop();
        callback(SW_SP_CB);
        Serial.print("[SP]");
      }

      if(m_timer.update())
      {
        m_sw_state = SW_STATE_LONG_PRESS;
        m_timer.stop();
      }
      break;
    case SW_STATE_LONG_PRESS:
      m_sw_state = SW_STATE_INIT;
      callback(SW_LP_CB);
      Serial.print("[LP]");
      break;  
    
    default:
      break;
    }
  }

  uint8_t m_clk_pin;
  uint8_t m_dt_pin;
  uint8_t m_sw_pin;
  uint8_t m_clk_curr_st = PIN_STATE_LOW;
  uint8_t m_clk_last_st = PIN_STATE_LOW;
  uint8_t m_sw_state = SW_STATE_INIT;
  Cb m_cbs[MAX_CB];
  noDelay m_timer;
  Debouncer m_debouncer;
};

#endif /* __SELECTOR_HPP__ */
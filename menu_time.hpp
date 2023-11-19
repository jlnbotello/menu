#ifndef __MENU_TIME_HPP__
#define __MENU_TIME_HPP__

#include "screen.hpp"
#include "model_time.hpp"

class TimeScreen : public Screen
{
public:  
  TimeScreen(MenuController &c, TimeModel &m);
  bool onEvent(Event event);

private:
  bool ev_cw_step();
  bool ev_ccw_step();
  bool ev_confirm_pressed();
  bool ev_cancel_pressed();

  TimeModel &timer;

  char on  = ' ';
  char off = 'x';

  uint8_t hour = 0;
  uint8_t hour_d1 = 0;
  uint8_t hour_d2 = 0;
  uint8_t min = 0;
  uint8_t min_d1 = 0;
  uint8_t min_d2 = 0;
  uint8_t sec = 0;
  uint8_t sec_d1 = 0;
  uint8_t sec_d2 = 0;
  enum
  {
    SELECT_HH,
    SELECT_MM,
    SELECT_SS,
    SELECT_ON_OFF
  };
  uint8_t selector = SELECT_HH;
};

#endif /*__MENU_TIME_HPP__*/
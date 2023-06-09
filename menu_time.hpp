#ifndef __MENU_TIME_HPP__
#define __MENU_TIME_HPP__

#include "screen.hpp"

class TimeScreen : public Screen
{
public:  
  TimeScreen(Services *s);
  ~TimeScreen() override;
  bool enter();
  bool exit();
  bool onEvent(Event event);

private:
  bool ev_cw_step();
  bool ev_ccw_step();
  bool ev_confirm_pressed();
  bool ev_cancel_pressed();

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
    SELECT_SS
  };
  uint8_t selector = SELECT_HH;
};

#endif /*__MENU_TIME_HPP__*/
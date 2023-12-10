#ifndef __MENU_WEEK_TIMER__
#define __MENU_WEEK_TIMER__

#include "screen.hpp"
#include "model_week.hpp"

class WeekUI;

class WeekTimerScreen : public Screen
{
public:  
  WeekTimerScreen(MenuController &c, WeekModel &w);
  ~WeekTimerScreen();
  bool enter();
  bool exit();
  bool onEvent(Event event);

private:
  WeekUI * ui;

  bool ev_cw_step();
  bool ev_ccw_step();
  bool ev_confirm_pressed();
  bool ev_cancel_pressed();
};

#endif /*__MENU_WEEK_TIMER__*/
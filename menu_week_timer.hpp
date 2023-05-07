#ifndef __MENU_WEEK_TIMER__
#define __MENU_WEEK_TIMER__

#include "screen.hpp"

//extern uint8_t tue;

//ScreenHandle_t *menu_week_timer(ScreenServices_t *srvs);

class WeekTimerScreen : public Screen
{
public:  
  WeekTimerScreen(Services *s);
  ~WeekTimerScreen() override;
  bool enter();
  bool exit();
  bool update();
  bool onEvent(Event event);

private:
  bool ev_cw_step();
  bool ev_ccw_step();
  bool ev_confirm_pressed();
  bool ev_cancel_pressed();
};

#endif /*__MENU_WEEK_TIMER__*/
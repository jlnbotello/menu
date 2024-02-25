#ifndef __WEEK_SCREEN_H__
#define __WEEK_SCREEN_H__

#include "screen.h"
#include "WeekModel.h"

class WeekUI;

class WeekScreen : public Screen
{
public:  
  WeekScreen(MenuController &c, WeekModel &w);
  ~WeekScreen() override;
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

#endif /*__WEEK_SCREEN_H__*/
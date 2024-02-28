#ifndef __INFO_SCREEN_H__
#define __INFO_SCREEN_H__

#include "Screen.h"

typedef uint8_t InfoModel;

class InfoScreen : public Screen
{
public:  
  InfoScreen(MenuController &c, InfoModel &m);
  ~InfoScreen() override;
  bool onEvent(Event event);

private:
  bool ev_cw_step();
  bool ev_ccw_step();
  bool ev_confirm_pressed();
  bool ev_cancel_pressed();
  bool ev_update();

  InfoModel &model;
};

#endif /*__INFO_SCREEN_H__*/
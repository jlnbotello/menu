#ifndef __TEMPLATE_SCREEN_H__
#define __TEMPLATE_SCREEN_H__

#include "Screen.h"

typedef uint8_t TemplateModel; // Create your own data model

class TemplateScreen : public Screen
{
public:  
  TemplateScreen(MenuController &c, TemplateModel &m);
  ~TemplateScreen() override;
  bool onEvent(Event event);

private:
  bool ev_cw_step();
  bool ev_ccw_step();
  bool ev_confirm_pressed();
  bool ev_cancel_pressed();
  bool ev_update();

  TemplateModel &model;
};

#endif /*__TEMPLATE_SCREEN_H__*/
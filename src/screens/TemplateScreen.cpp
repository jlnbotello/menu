/*---------------------------------[INCLUDES]---------------------------------*/
#include "TemplateScreen.h"

/*---------------------------------[PREPROCESSOR DEFS]------------------------*/

/*---------------------------------[TYPE DEFS]--------------------------------*/

/*---------------------------------[PRIVATE DATA]-----------------------------*/

/*---------------------------------[PRIVATE FUNCTIONS]------------------------*/

/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/
TemplateScreen::TemplateScreen(MenuController &c, TemplateModel &m) : model(m), Screen(c)
{

}

TemplateScreen::~TemplateScreen()
{

}

bool TemplateScreen::onEvent(Event event)
{
  switch (event)
  {
  case EV_CONFIRM_PRESSED:
    ev_confirm_pressed();
    break;

  case EV_CANCEL_PRESSED:
    ev_cancel_pressed();
    break;

  case EV_CCW_STEP:
    ev_ccw_step();
    break;

  case EV_CW_STEP:
    ev_cw_step();
    break;

  case EV_UPDATE_LOOP:
    ev_update();
    break;

  default:
    return false;
    break;
  }
  return true;
}

bool TemplateScreen::ev_cw_step()
{

  update();
  return true;
};

bool TemplateScreen::ev_ccw_step()
{

  update();
  return true;
};

bool TemplateScreen::ev_confirm_pressed()
{
  return true;
};

bool TemplateScreen::ev_cancel_pressed()
{
  m_controller.Back();
  return true;
};

bool TemplateScreen::ev_update()
{
  return true;
};
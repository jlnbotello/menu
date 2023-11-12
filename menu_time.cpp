

/*---------------------------------[INCLUDES]---------------------------------*/
#include "menu_time.hpp"

/*---------------------------------[PREPROCESSOR DEFS]------------------------*/
#define TIME_LINE_1_INIT    "Time"
#define TIME_LINE_2_INIT    "    09:30:23    "

/*---------------------------------[TYPE DEFS]--------------------------------*/

/*---------------------------------[PRIVATE DATA]-----------------------------*/


/*---------------------------------[PRIVATE FUNCTIONS]------------------------*/


/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/
TimeScreen::TimeScreen(Services *s, TimeModel *c) : Screen(s)
{

}

TimeScreen::~TimeScreen()
{
  exit();
}

bool TimeScreen::enter()
{
  m_menu = new LiquidMenu(*(m_services->pLcd));
  m_screen = new LiquidScreen();

  LiquidLine * pTitleLine = new LiquidLine(0, 0, "TIME");
  LiquidLine * pHH = new LiquidLine(4, 1, hour_d1, hour_d2, ":");
  LiquidLine * pMM = new LiquidLine(7, 1, min_d1, min_d2, ":");
  LiquidLine * pSS = new LiquidLine(10, 1, sec_d1, sec_d2);

  m_screen->add_line(*pTitleLine);
  m_screen->add_line(*pHH);
  m_screen->add_line(*pMM);
  m_screen->add_line(*pSS);

  m_menu->add_screen(*m_screen);
  m_menu->update();

  return true;
}

bool TimeScreen::exit()
{
  Screen::exit();

  return true;
}

bool TimeScreen::onEvent(Event event)
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
    update();
    break;

  default:
    return false;
    break;
  }
  return true;
}

bool TimeScreen::ev_cw_step() 
{
  switch (selector)
  {
  case SELECT_HH:
      hour = (hour == 23) ? (0) : (++hour);
      hour_d1 = hour/10;
      hour_d2 = hour%10;
    break;
  case SELECT_MM:
      min = (min == 59) ? (0) : (++min);
      min_d1 = min/10;
      min_d2 = min%10;
    break;
  case SELECT_SS:
      sec = (sec == 59) ? (0) : (++sec);
      sec_d1 = sec/10;
      sec_d2 = sec%10;
    break;

  default:
    break;
  }

  m_menu->update();
  return true;
};

bool TimeScreen::ev_ccw_step()
{
  switch (selector)
  {
  case SELECT_HH:
      hour = (hour == 0) ? (23) : (--hour);
      hour_d1 = hour/10;
      hour_d2 = hour%10;
    break;
  case SELECT_MM:
      min = (min == 0) ? (59) : (--min);
      min_d1 = min/10;
      min_d2 = min%10;
    break;
  case SELECT_SS:
      sec = (sec == 0) ? (59) : (--sec);
      sec_d1 = sec/10;
      sec_d2 = sec%10;
    break;

  default:
    break;
  }

  m_menu->update();  
  return true;
};

bool TimeScreen::ev_confirm_pressed()
{
  selector = (selector < SELECT_SS)? selector + 1 : 0;
  m_menu->update();  
  return true;
};

bool TimeScreen::ev_cancel_pressed()
{
  exit();
  
  Node<MenuNode> *node = m_services->pNavSys->navigateBack();

  if (node)
  {
    node->data->pScreen->enter();
  }

  return true;
};
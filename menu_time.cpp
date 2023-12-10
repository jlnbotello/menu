/*---------------------------------[INCLUDES]---------------------------------*/
#include "menu_time.hpp"

/*---------------------------------[PREPROCESSOR DEFS]------------------------*/

/*---------------------------------[TYPE DEFS]--------------------------------*/

/*---------------------------------[PRIVATE DATA]-----------------------------*/

/*---------------------------------[PRIVATE FUNCTIONS]------------------------*/

/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/
TimeScreen::TimeScreen(MenuController &c, TimeModel &m) : timer(m), Screen(c)
{
  LiquidLine *pTitleLine = new LiquidLine(0, 0, "TIME");
  LiquidLine *pSwitch = new LiquidLine(9, 0, "ON", on, "OFF", off);
  LiquidLine *pHH = new LiquidLine(4, 1, hour_d1, hour_d2, ":");
  LiquidLine *pMM = new LiquidLine(7, 1, min_d1, min_d2, ":");
  LiquidLine *pSS = new LiquidLine(10, 1, sec_d1, sec_d2);

  addLine(pTitleLine);
  addLine(pSwitch);
  addLine(pHH);
  addLine(pMM);
  addLine(pSS);
}

TimeScreen::~TimeScreen()
{
  Screen::~Screen(); // delete LiquidLine instances
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
    if (timer.is_enabled())
    {
      unsigned long millis = timer.getRemaining();
      //unsigned long milliss = 1000 * (3600*0 + 29*60 + 11);
      unsigned long secs = millis / 1000;
      unsigned long hh = (secs) / 3600;
      unsigned long mm = (secs - 3600 * hh) / 60;
      unsigned long ss = secs - 3600 * hh - 60 * mm;

      if (seconds != ss)
      {
        Serial.print("Time: ");
        Serial.print(hh);
        Serial.print(":");
        Serial.print(mm);
        Serial.print(":");
        Serial.println(ss);
        
        hour = hh;
        minutes = mm;
        seconds = ss;

        hour_d1 = hour / 10;
        hour_d2 = hour % 10;
        min_d1 = minutes / 10;
        min_d2 = minutes % 10;
        sec_d1 = seconds / 10;
        sec_d2 = seconds % 10;

        update();
      }
    }
    break;

  default:
    return false;
    break;
  }
  return true;
}

bool TimeScreen::ev_cw_step()
{
  char tmp;

  switch (selector)
  {
  case SELECT_HH:
    hour = (hour == 23) ? (0) : (++hour);
    hour_d1 = hour / 10;
    hour_d2 = hour % 10;
    break;
  case SELECT_MM:
    minutes = (minutes == 59) ? (0) : (++minutes);
    min_d1 = minutes / 10;
    min_d2 = minutes % 10;
    break;
  case SELECT_SS:
    seconds = (seconds == 59) ? (0) : (++seconds);
    sec_d1 = seconds / 10;
    sec_d2 = seconds % 10;
    break;
  case SELECT_ON_OFF:
    tmp = on;
    on = off;
    off = tmp;
    break;

  default:
    break;
  }

  update();
  return true;
};

bool TimeScreen::ev_ccw_step()
{
  char tmp;

  switch (selector)
  {
  case SELECT_HH:
    hour = (hour == 0) ? (23) : (--hour);
    hour_d1 = hour / 10;
    hour_d2 = hour % 10;
    break;
  case SELECT_MM:
    minutes = (minutes == 0) ? (59) : (--minutes);
    min_d1 = minutes / 10;
    min_d2 = minutes % 10;
    break;
  case SELECT_SS:
    seconds = (seconds == 0) ? (59) : (--seconds);
    sec_d1 = seconds / 10;
    sec_d2 = seconds % 10;
    break;
  case SELECT_ON_OFF:
    tmp = on;
    on = off;
    off = tmp;
    break;
  default:
    break;
  }

  update();
  return true;
};

bool TimeScreen::ev_confirm_pressed()
{
  if (selector == SELECT_ON_OFF)
  {
    if (on == 'x')
    {
      timer.start(HH_MM_SS_TO_MS(hour, minutes, seconds), nullptr);
    }
    else
    {
      timer.stop();
      timer.reset();
      hour = minutes = seconds = 0;
    }
  }
  selector = (selector < SELECT_ON_OFF) ? selector + 1 : 0;
  update();
  return true;
};

bool TimeScreen::ev_cancel_pressed()
{
  m_controller.Back();
};
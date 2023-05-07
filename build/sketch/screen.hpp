#line 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\screen.hpp"

#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include "Arduino.h"
#include <LiquidMenu.h>
#include "custom_chars.hpp"
#include "navigator.hpp"

// #define MAX_TITLE_LEN 20

// typedef struct
// {
//   char name[16+1];
//   LiquidScreen * controller;
//   EventHandler * event_handler;
// } ScreenHandle_t;

class Screen;

typedef struct
{
  const char * name;
  Screen * pScreen;
} MenuNode;

class Screen
{
public:
  typedef enum
  {
    EV_CW_STEP,
    EV_CCW_STEP,
    EV_CONFIRM_PRESSED,
    EV_CANCEL_PRESSED,
    EV_UPDATE_LOOP,
    EVENT_ID_MAX
  } Event;

  typedef struct
  {
    CustomCharManager *pCCM;
    NavigationSystem<MenuNode> *pNavSys;
    DisplayClass *pLcd;
  } Services;

  Screen(Services *s) : m_services(s){};
  virtual ~Screen() = default;

  virtual bool onEvent(Event event) = 0;    
 
  virtual bool enter() = 0;
  virtual bool exit() = 0;
  virtual bool update() {};
  

  // virtual bool ev_cw_step() {return false;};
  // virtual bool ev_ccw_step() {return false;};
  // virtual bool ev_confirm_pressed() {return false;};
  // virtual bool ev_cancel_pressed() {return false;};

  protected:
  Services *m_services;

  LiquidMenu * m_menu;
  LiquidScreen * m_screen;
  LiquidLine ** m_lines;
  int m_max_lines = 0;
};



#endif /* __SCREEN_HPP__ */

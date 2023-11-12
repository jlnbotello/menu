
#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include "Arduino.h"
#include <LiquidMenu.h>
#include "custom_chars.hpp"
#include "navigator.hpp"
#include "screen_factory.hpp"

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
  ScreenFactoryInterface * factory;
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

  Screen(Services *s) : m_services(s)
  {
    m_menu = new LiquidMenu(*(m_services->pLcd));
    m_screen = new LiquidScreen();
    m_menu->add_screen(*m_screen);
  };
  virtual ~Screen() = default;


  virtual bool onEvent(Event event) = 0;    
 
  virtual bool enter() = 0;
  virtual bool exit()
  {
    if(m_menu)
    {
      delete(m_menu);
      m_menu = nullptr;
    }
    //m_max_lines = 0;   
  }
  
  void update() 
  {
    m_menu->update();
  };
  
  void addLine(LiquidLine * line)
  {
    m_screen->add_line(*line);
  }

  // virtual bool ev_cw_step() {return false;};
  // virtual bool ev_ccw_step() {return false;};
  // virtual bool ev_confirm_pressed() {return false;};
  // virtual bool ev_cancel_pressed() {return false;};

  protected:
  Services *m_services;

  LiquidMenu * m_menu;
  private:
  LiquidScreen * m_screen;
  //LiquidLine ** m_lines;
  //int m_max_lines = 0;
};



#endif /* __SCREEN_HPP__ */

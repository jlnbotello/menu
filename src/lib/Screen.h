#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "Arduino.h"
#include <LiquidMenu.h>
#include "MenuController.h"


class Screen
{
public:
  Screen(MenuController &c) : m_controller(c)
  {
    m_menu = new LiquidMenu(*(m_controller.GetServices()->pLcd));
    m_menu->add_screen(*(new LiquidScreen()));
  };

  virtual ~Screen()
  {
    delete (m_menu);
  }

  virtual bool onEvent(Event event) = 0;

  void update()
  {
    m_menu->softUpdate();
  };

    void updateAll()
  {
    m_menu->update();
  };

  void addLine(LiquidLine *line)
  {
    m_menu->get_currentScreen()->add_line(*line);
  }

protected:
  LiquidMenu *m_menu;
  MenuController &m_controller;
  // LiquidScreen * m_screen;
};

#endif /* __SCREEN_H__ */

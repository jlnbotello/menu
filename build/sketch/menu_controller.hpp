#line 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu_controller.hpp"
#ifndef __MENU_CONTROLLER_H__
#define __MENU_CONTROLLER_H__
#include "screen.hpp"
#include "custom_char_defs.hpp"
#include "custom_chars.hpp"


#define MAX_URL_SIZE 128
#define MAX_LINES_PER_SCREEN 4

// typedef struct
// {
//   char title[MAX_TITLE_LEN];
//   LiquidLine * controller;
// } Line_t;

// typedef struct
// {
//   LiquidScreen controller;
//   Line_t lines[MAX_LINES_PER_SCREEN];
// } Screen_t;

void stub();

class ContainerScreen : public Screen
{
public:  
  ContainerScreen(Services *s);
  ~ContainerScreen() override;
  bool enter();
  bool exit();
  bool update();
  bool onEvent(Event event) override;

private:
  bool ev_cw_step() ;
  bool ev_ccw_step() ;
  bool ev_confirm_pressed() ;
  bool ev_cancel_pressed() ;
  Node<MenuNode> *m_node = nullptr;
  int8_t m_focused_line = 0;
  uint8_t m_n_of_lines = 0;
};

class MenuController
{
public:
  MenuController(DisplayClass &lcd);
  void AddScreen(const char* url, const char* name, Screen * screen);
  void AddContainer(const char* url, const char* name);
  Screen::Services * GetServices();
  bool Enter(const char* url);
  bool Back();
  void TriggerEvent(Screen::Event event);
  void Update();

private:
  // void create_default_event_handler();
  // void evh_up();
  // void evh_down();
  // void evh_enter();
  // void evh_back();

  // void draw_inactive_screen(const char* url);
  // void swap_active_screen();
  bool url_remove_last_tag(char* url, size_t maxUrlSize);

  //DisplayClass &m_lcd;
  Screen::Services m_services;
  ContainerScreen * m_container;
  // EventHandler m_evh;
  // Screen_t m_screens[2];
  // uint8_t m_active_screen = 0;
  // char m_active_url[MAX_URL_SIZE];
};

#endif /* __MENU_CONTROLLER_H__ */
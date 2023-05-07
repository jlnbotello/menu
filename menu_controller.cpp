#include "menu_controller.hpp"
#include "MemoryFree.h"


#define INACTIVE_IDX ((!m_active_screen) & (0x01))
#define ACTIVE_IDX   (( m_active_screen) & (0x01))

void stub(){};

static void printFreeMem(char * file, int line)
{
  Serial.print("["); 
  Serial.print(file);
  Serial.print(":");
  Serial.print(line);
  Serial.print("] ");    
  Serial.print("Free Memory: ");
  Serial.print(freeMemory());
  Serial.println(" bytes");
}

MenuController::MenuController(DisplayClass &lcd)
{
  // printFreeMem(__FILE__, __LINE__);
  
  // m_services.pMenu   = new LiquidMenu(m_lcd);
  // //m_services.pCCM    = new CustomCharManager(m_lcd);
  m_services.pLcd = &lcd;
  m_services.pNavSys = new NavigationSystem<MenuNode>();
  m_services.pCCM = new CustomCharManager(lcd);

  m_container = new ContainerScreen(&m_services);

  // printFreeMem(__FILE__, __LINE__);

  // create_default_event_handler();

  // printFreeMem(__FILE__, __LINE__);

  // for(uint8_t i=0; i < MAX_LINES_PER_SCREEN; i++)
  // {    
  //   strcpy(m_screens[ACTIVE_IDX].lines[i].title, "<none>");
  //   m_screens[ACTIVE_IDX].lines[i].controller = new LiquidLine(1, 0, m_screens[ACTIVE_IDX].lines[i].title);
  //   m_screens[ACTIVE_IDX].lines[i].controller->set_focusPosition(Position::LEFT);
  //   m_screens[ACTIVE_IDX].lines[i].controller->attach_function(0, stub); //make the line focusable
  //   m_screens[ACTIVE_IDX].controller.add_line(*m_screens[ACTIVE_IDX].lines[i].controller);
    
  //   strcpy(m_screens[INACTIVE_IDX].lines[i].title, "<none inac>");
  //   m_screens[INACTIVE_IDX].lines[i].controller = new LiquidLine(1, 0, m_screens[INACTIVE_IDX].lines[i].title);
  //   m_screens[INACTIVE_IDX].lines[i].controller->set_focusPosition(Position::LEFT);
  //   m_screens[INACTIVE_IDX].lines[i].controller->attach_function(0, stub);
  //   m_screens[INACTIVE_IDX].controller.add_line(*m_screens[INACTIVE_IDX].lines[i].controller);
  // }

  // printFreeMem(__FILE__, __LINE__);

  // m_screens[ACTIVE_IDX].controller.set_displayLineCount(2);
  // m_screens[INACTIVE_IDX].controller.set_displayLineCount(2);
   
  // m_services.pMenu->add_screen(m_screens[ACTIVE_IDX].controller);
  // m_services.pMenu->add_screen(m_screens[INACTIVE_IDX].controller);

  // printFreeMem(__FILE__, __LINE__);

  m_services.pLcd->begin();
  m_services.pLcd->backlight();
  // m_services.pMenu->init();

  // printFreeMem(__FILE__, __LINE__);
  //m_services.pMenu->update();
}

void MenuController::AddScreen(const char* url, const char* name, Screen * screen)
{
  // if(!screen)
  // {
  //   screen = calloc(1, sizeof(ScreenHandle_t));

  //   if(!screen)
  //   {
  //     Serial.print("Run out of memory");
  //     return;
  //   }
  //   screen->controller = NULL; 
  //   screen->event_handler = &m_evh;
  // }

  //strncpy(screen->name, name, MAX_TITLE_LEN);

  if(url && name && screen)
  {
    MenuNode * pNode = calloc(1, sizeof(MenuNode));
    if(pNode)
    {
      pNode->name = name;
      pNode->pScreen = screen;
      m_services.pNavSys->addNode(url, pNode);
    }
  }

  // m_services.pNavSys->addNode(url, screen);
  // Serial.print("added");
  // Serial.println(name);
}

void MenuController::AddContainer(const char* url, const char* name)
{
  if(url && name)
  {
    MenuNode * pNode = calloc(1, sizeof(MenuNode));
    if(pNode)
    {
      pNode->name = name;
      pNode->pScreen = m_container;
      m_services.pNavSys->addNode(url, pNode);
    }
  }
}

Screen::Services * MenuController::GetServices()
{
  return &m_services;
}

bool MenuController::Enter(const char* url)
{
  //node->data->exit();
  
  Node<MenuNode> * node = m_services.pNavSys->navigateAbsoluteUrl(url);
  
  Serial.print("url: ");
  Serial.println(url);
  if((!node) || (!node->data) || (!node->data->pScreen))
  {
    Serial.println("node null");
    return false;
  }

  node->data->pScreen->enter();

  // ScreenHandle_t * screen_h = node->value;
  // LiquidScreen * pScreenController = nullptr;
  
  // if(screen_h->controller)
  // {
  //   // custom screen
  //   Serial.println("custom");
  //   pScreenController = screen_h->controller;
  // }
  // else
  // {
  //   // list screen
  //    Serial.println("list");
  //   draw_inactive_screen(url);
  //   swap_active_screen();
  //   pScreenController = &m_screens[ACTIVE_IDX].controller;
  // }

  // if(!pScreenController)
  // {
  //   Serial.println("no controller");
  //   return false;
  // }

  // if(m_services.pMenu->change_screen(pScreenController))
  // {
  //   strcpy(m_active_url, url);
  //   m_services.pMenu->set_focusedLine(0);
  //   Serial.println("change screen ok");
  //   return true;
  // }

  // Serial.println("change screen failed");
  return true;  
}

bool MenuController::Back()
{
  // char prev_screen_url[MAX_URL_SIZE];
  // strncpy(prev_screen_url, m_active_url, MAX_URL_SIZE);
  
  // if(url_remove_last_tag(prev_screen_url, MAX_URL_SIZE))
  // {
  //   if (Enter(prev_screen_url))
  //   {
  //     strncpy(m_active_url, prev_screen_url, MAX_URL_SIZE);
  //     return true;
  //   }
  // }

  return false;  
}

void MenuController::TriggerEvent(Screen::Event event)
{
  //Serial.println(event);
  Node<MenuNode> * active_node = m_services.pNavSys->getCurrentNode();
  
  if(active_node && active_node->data && active_node->data->pScreen)
  {
    active_node->data->pScreen->onEvent(event);
  }
  // Serial.println(active_node->value->name);
  // active_node->value->event_handler->trigger(ev_id);
}

void MenuController::Update()
{
  //m_services.pMenu->update();
}

// void MenuController::create_default_event_handler()
// {
//   static EventHandler::cb_t<MenuController> ev_cb_up = [](MenuController* obj) 
//   {
//     obj->evh_up();
//   };

//   static EventHandler::cb_t<MenuController> ev_cb_down = [](MenuController* obj) 
//   {
//     obj->evh_down();
//   };

//   static EventHandler::cb_t<MenuController> ev_cb_confirm = [](MenuController* obj) 
//   {
//     obj->evh_enter();
//   };

//   static EventHandler::cb_t<MenuController> ev_cb_back = [](MenuController* obj) 
//   {
//     obj->evh_back();
//   };

//   m_evh.add(EventHandler::EV_CW_STEP, ev_cb_up, this);
//   m_evh.add(EventHandler::EV_CCW_STEP, ev_cb_down, this);
//   m_evh.add(EventHandler::EV_CONFIRM_PRESSED, ev_cb_confirm, this);
//   m_evh.add(EventHandler::EV_CANCEL_PRESSED, ev_cb_back, this);
// }

// void MenuController::evh_up()
// {
//   //Serial.println("Up");
//   m_services.pMenu->switch_focus(true);
// ;}

// void MenuController::evh_down()
// {
//   //Serial.println("Down");
//   m_services.pMenu->switch_focus(false);
// }

// void MenuController::evh_enter()
// {
//  uint8_t index = m_services.pMenu->get_focusedLine();

//  Serial.println("Enter");

//  Node<ScreenHandle_t> * active_node = m_services.pNavSys->navigate(m_active_url);

//  if(index < active_node->numChildren)
//  {
//    char next_url[MAX_URL_SIZE];
//    strncpy(next_url, m_active_url, MAX_URL_SIZE);
//    strcat(next_url,"/");
//    strncat(next_url, active_node->children[index]->tag, MAX_URL_SIZE);
   
//    Enter(next_url);
//  }
// }

// void MenuController::evh_back()
// {
//    LiquidScreen * prev_screen; //get__prev_screen()
//   m_services.pMenu->change_screen(prev_screen);
// }

// void MenuController::draw_inactive_screen(const char* url)
// {
//   Node<ScreenHandle_t> * node = m_services.pNavSys->navigate(url);

//   Serial.println(url);
  
//   if(node && node->value)
//   {
//     if(!node->value->controller) //no controller -> create children list
//     {
//       for(uint8_t i = 0; i < node->numChildren ; i++)
//       {
//         Serial.println(node->children[i]->value->name);
//         strncpy(m_screens[INACTIVE_IDX].lines[i].title,
//                 node->children[i]->value->name,                
//                  MAX_TITLE_LEN);
//       }
//     }
//   }  
// }

// void MenuController::swap_active_screen()
// {
//   m_active_screen = INACTIVE_IDX;
// }

bool MenuController::url_remove_last_tag(char* url, size_t maxUrlSize) {
    if (url == nullptr || maxUrlSize == 0) {
        return false;
    }
    // Find the position of the last slash
    char* lastSlash = nullptr;
    for (char* p = url; *p != '\0' && p < url + maxUrlSize; ++p) {
        if (*p == '/') {
            lastSlash = p;
        }
    }
    if (lastSlash != nullptr) {
        // Remove the last component
        *lastSlash = '\0';
    }
    // Remove the trailing slash if it exists
    size_t len = 0;
    for (char* p = url; *p != '\0' && p < url + maxUrlSize; ++p) {
        ++len;
    }
    if (len > 0 && url[len-1] == '/') {
        url[len-1] = '\0';
    }
    return true;
}

ContainerScreen::ContainerScreen(Services *s) : 
Screen(s)
{

}

ContainerScreen::~ContainerScreen()
{
  exit();
}


bool ContainerScreen::enter()
{
  if(m_node)
  {
    Serial.println("Node already in use");
    return false;
  }

  m_node = m_services->pNavSys->getCurrentNode();
  
  if(!m_node)
  {
    Serial.println("Node not found");
    return false;
  }

  m_menu = new LiquidMenu(*(m_services->pLcd));
  m_screen = new LiquidScreen();
  m_n_of_lines = m_node->numChildren;

  for(uint8_t i=0 ; i < m_n_of_lines; i++)
  {
    Node<MenuNode> * child = m_node->children[i];
    if(child)
    {
      Serial.println("Add line");
      LiquidLine * line = new LiquidLine(1,i%2,(const char (&)[1])(*child->data->name));
      line->set_asProgmem(1);
      line->attach_function(1, stub);
      m_screen->add_line(*line);      
    }
    else{
      
    }
  }

  
  // m_max_lines = 3;
  // m_lines = new LiquidLine * [m_max_lines]; 

  // for(int i = 0; i < m_max_lines; i++)
  // {
  //   m_lines[i] = new LiquidLine(0,0);
  //   m_screen->add_line(*(m_lines[i]));
  // }

  // m_lines[0]->add_variable("LINE 0");
  // m_lines[1]->add_variable("LINE 1");
  // m_lines[2]->add_variable("LINE 2");

  m_screen->set_displayLineCount(2);
  m_screen->set_focusPosition(Position::LEFT);

  m_menu->add_screen(*m_screen);
  m_menu->set_focusedLine(m_focused_line);
  m_menu->update();
  return true;
}

bool ContainerScreen::exit()
{
  if(m_menu)
  {
    delete(m_menu); // also deletes added screens
    m_menu = nullptr;
    m_screen = nullptr;
  }

  m_node = nullptr;
  m_focused_line = 0;
  m_n_of_lines = 0;

  return true;
}

bool ContainerScreen::update()
{
  return true;
}

bool ContainerScreen::onEvent(Event event)
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

  default:
    return false;
    break;
  }
  return true;
}

bool ContainerScreen::ev_cw_step() 
{
  m_menu->switch_focus(true);

  if(m_focused_line < (m_n_of_lines - 1))
  {
    m_focused_line++;
  }
  else
  {
    m_focused_line = 0;
  }
  
  //Serial.print("Focused line: ");
  //Serial.println(m_focused_line);
  return true;
};

bool ContainerScreen::ev_ccw_step()
{
  m_menu->switch_focus(false);

  if(m_focused_line > 0)
  {
    m_focused_line--;
  }
  else
  {
    m_focused_line = (m_n_of_lines - 1);
  }

  //Serial.print("Focused line: ");
  //Serial.println(m_focused_line);
  return true;
};

bool ContainerScreen::ev_confirm_pressed()
{
  const char * tag = nullptr;
  
  if(m_focused_line < m_n_of_lines)
  {
    tag = m_node->children[m_focused_line]->tag;
  }
   
  exit();

  if (tag)
  {
    Node<MenuNode> *node = m_services->pNavSys->navigateRelativeUrl(tag);

    if (node)
    {
      node->data->pScreen->enter();
    }
  }
  return true;
};

bool ContainerScreen::ev_cancel_pressed()
{
  exit();
  
  Node<MenuNode> *node = m_services->pNavSys->navigateBack();

  if (node)
  {
    node->data->pScreen->enter();
  }
  return true;
};

#include "menu_controller.hpp"
#include "screen_factory.hpp"
#include "MemoryFree.h"


#define INACTIVE_IDX ((!m_active_screen) & (0x01))
#define ACTIVE_IDX   (( m_active_screen) & (0x01))

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
  m_services.pLcd = &lcd;
  m_services.pNavSys = new NavigationSystem<MenuNode>();
  m_services.pCCM = new CustomCharManager(lcd);

  m_services.pLcd->begin();
  m_services.pLcd->backlight();

  ScreenFactory<void> * sf = new ScreenFactory<void> (nullptr);
  m_container_sfi = sf->factory();
}

void MenuController::AddScreen(const char* url, const char* name, ScreenFactoryInterface * sfi)
{
  if(url && name && sfi)
  {
    MenuNode * pNode = (MenuNode *) calloc(1, sizeof(MenuNode));
    if(pNode)
    {
      pNode->name = name;
      pNode->factory = sfi;
      m_services.pNavSys->addNode(url, pNode);
    }
  }
}

void MenuController::AddContainer(const char* url, const char* name)
{
  if(url && name)
  {
    MenuNode * pNode = (MenuNode *) calloc(1, sizeof(MenuNode));
    if(pNode)
    {
      pNode->name = name;
      pNode->factory = m_container_sfi;
      m_services.pNavSys->addNode(url, pNode);
    }
  }
}

Services * MenuController::GetServices()
{
  return &m_services;
}

bool MenuController::Enter(const char* url)
{
  Node<MenuNode> * node = m_services.pNavSys->navigateAbsoluteUrl(url);
  
  if((!node) || (!node->data) || (!node->data->factory))
  {
    Serial.println("node null");
    return false;
  }

  if(m_current_screen)
  {
    delete(m_current_screen);
    m_current_screen = nullptr;
  }

  m_current_screen = node->data->factory->createScreen(*this);

  if(m_current_screen)
  {
    //Serial.println("update screen");
    m_current_screen->updateAll();
  } 
  else{
    Serial.println("no screen");
  }

  return true;  
}

bool MenuController::EnterChild(const char* tag)
{
  Node<MenuNode> * node = m_services.pNavSys->navigateRelativeUrl(tag);

  if((!node) || (!node->data) || (!node->data->factory))
  {
    Serial.println("node null");
    return false;
  }

  if(m_current_screen)
  {
    delete(m_current_screen);
    m_current_screen = nullptr;
  }

  m_current_screen = node->data->factory->createScreen(*this);

  if(m_current_screen)
  {
    m_current_screen->updateAll();
  }  
}

bool MenuController::Back()
{
  Node<MenuNode> * node = m_services.pNavSys->navigateBack();

  if((!node) || (!node->data) || (!node->data->factory))
  {
    Serial.println("error back");
    return false;
  }

  if(m_current_screen)
  {
    delete(m_current_screen);
    m_current_screen = nullptr;
  }

  m_current_screen = node->data->factory->createScreen(*this);

  if(m_current_screen)
  {
    m_current_screen->updateAll();
  }

  return false;  
}

void MenuController::TriggerEvent(Event event)
{
  m_current_screen->onEvent(event);
}


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

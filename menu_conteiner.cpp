#include "menu_container.hpp"

void stub(){};

ContainerScreen::ContainerScreen(MenuController &c) : 
Screen(c)
{

  Node<MenuNode> * node = c.GetServices()->pNavSys->getCurrentNode();
  
  if(!node)
  {
    Serial.println("Node not found");
    return;
  }

  m_n_of_lines = node->numChildren;
  Serial.print("Nlines:");
  Serial.println(m_n_of_lines);

  for(uint8_t i=0 ; i < m_n_of_lines; i++)
  {
    Node<MenuNode> * child = node->children[i];
    if(child)
    {
      Serial.println("Add line");
      LiquidLine * line = new LiquidLine(1,i%2,(const char (&)[1])(*child->data->name));
      line->set_asProgmem(1);
      line->attach_function(1, stub);
      addLine(line);      
    }
    else{
      Serial.println("Null child");
    }
  }

  m_menu->get_currentScreen()->set_displayLineCount(2);
  m_menu->get_currentScreen()->set_focusPosition(Position::LEFT);
  m_menu->set_focusedLine(m_focused_line);
  update();

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

  Node<MenuNode> * node = m_controller.GetServices()->pNavSys->currentNode;
  
  if(m_focused_line < m_n_of_lines)
  {
    tag = node->children[m_focused_line]->tag;
  }
   
  if (tag)
  {
    Serial.print("tag:");
    Serial.print(tag);
    m_controller.EnterChild(tag);
  }

  return true;
};

bool ContainerScreen::ev_cancel_pressed()
{
  m_controller.Back();
};
#line 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\custom_chars.hpp"
#ifndef __CUSTOM_CHARS_H__
#define __CUSTOM_CHARS_H__

#include <LiquidMenu.h>
#include "custom_char_defs.hpp"

/* The LCD support 8 custom char (max)
   But LiquidMenu use the last 3 slot
   See LiquidMenu::init()
   Default CCM_MAX_SLOTS 5
*/
#define CCM_MAX_SLOTS 5

#define SET_CCHAR_SLOT(slot, cchar) slot ? slot->SetChar(cchar) : ' '

class CustomCharManager;

class CCSlot{

public:
  CCSlot(DisplayClass &lcd, uint8_t idx);

  uint8_t SetChar(cchar_t buf);
  void Unlock();
  bool IsUnlocked();

private:
  void Lock();
  DisplayClass &m_lcd;  
  const uint8_t m_idx;
  bool m_locked = false;
  friend class CustomCharManager;
};

class CustomCharManager
{
public:
  CustomCharManager(DisplayClass &lcd);
  ~CustomCharManager();
  CCSlot * LockSlot();

private:
  DisplayClass &m_lcd;
  CCSlot * m_slots[CCM_MAX_SLOTS];
};

#endif /*__CUSTOM_CHARS_H__*/
#line 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\back_up\\custom_chars.hpp"
#ifndef __CUSTOM_CHARS_H__
#define __CUSTOM_CHARS_H__

#include <LiquidMenu.h>
#include "custom_char_defs.hpp"

#define CCM_MAX_SLOTS MAX_VARIABLES

#define CC_ID_PARSER(id, data) id,

typedef enum 
{
  CC_DEFS(CC_ID_PARSER)
  CC_MAX_DEFS
} cc_id_t;

typedef uint8_t cc_buf_t[8];

class CustomCharManager;

class CCSlot{

public:
  CCSlot(DisplayClass &lcd, uint8_t idx);

  uint8_t SetChar(cc_id_t id);
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
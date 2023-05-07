#line 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\custom_chars.cpp"
#include "custom_chars.hpp"

CCSlot::CCSlot(DisplayClass &lcd, uint8_t idx):m_lcd{lcd},m_idx{idx}
{
  
};

uint8_t CCSlot::SetChar(cchar_t cchar)
{
  uint8_t buf[sizeof(cchar_t)]; // temp non-const buffer
  memcpy(buf, cchar, sizeof(buf));
  m_lcd.createChar(m_idx, buf);
  return m_idx;
}

void CCSlot::Unlock()
{
  m_locked = false;
}

void CCSlot::Lock()
{
  m_locked = true;
}

bool CCSlot::IsUnlocked()
{
  return !m_locked;
}

CustomCharManager::CustomCharManager(DisplayClass &lcd)
:m_lcd{lcd}
{
    for(uint8_t i=0; i < CCM_MAX_SLOTS; i++)
    {
      m_slots[i] = new CCSlot(lcd, i);
    }  
}

CustomCharManager::~CustomCharManager()
{
    for(uint8_t i=0; i < CCM_MAX_SLOTS; i++)
    {
      delete(m_slots[i]);
    }  
}

CCSlot *  CustomCharManager::LockSlot()
{
    for(uint8_t i=0; i < CCM_MAX_SLOTS; i++)
    {
      if(m_slots[i]->IsUnlocked())
      {
        m_slots[i]->Lock();
        return m_slots[i];
      }
    }

    return nullptr;
}

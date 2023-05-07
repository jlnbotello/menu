#line 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\back_up\\custom_chars.cpp"
#include "custom_chars.hpp"

#define CC_DATA_PARSER(id, data) data,

static const cc_buf_t _ccpool[] = {
  CC_DEFS(CC_DATA_PARSER)
};


CCSlot::CCSlot(DisplayClass &lcd, uint8_t idx):m_lcd{lcd},m_idx{idx}
{
  
};

uint8_t CCSlot::SetChar(cc_id_t id)
{
  if(id<CC_MAX_DEFS && m_locked)
  {
    cc_buf_t buf; // temp non-const buffer
    memcpy(buf, _ccpool[id], sizeof(buf));
    m_lcd.createChar(m_idx, buf);
  }
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

/*---------------------------------[INCLUDES]---------------------------------*/
#include "InfoScreen.h"
#include "CustomChars.h"

/*---------------------------------[PREPROCESSOR DEFS]------------------------*/

/*---------------------------------[TYPE DEFS]--------------------------------*/

/*---------------------------------[PRIVATE DATA]-----------------------------*/
static CCSlot * s0 = nullptr;
static CCSlot * s1 = nullptr;

static uint8_t cc_fan1;
static uint8_t cc_fan2;

static uint8_t cc_fan;
/*---------------------------------[PRIVATE FUNCTIONS]------------------------*/
static void stub(void){};
/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/
InfoScreen::InfoScreen(MenuController &c, InfoModel &m) : model(m), Screen(c)
{
  LiquidLine *pData   = new LiquidLine(1, 0, "DATE 29-02-2024");
  LiquidLine *pTime   = new LiquidLine(1, 1, "TIME 14:08:23");
  LiquidLine *pTemp   = new LiquidLine(1, 2, "TEMP 32 C");
  LiquidLine *pStatus = new LiquidLine(1, 3, "STATUS OK");
  LiquidLine *pFan    = new LiquidLine(1, 4, "FAN ", cc_fan);

  pData->attach_function(1, stub);
  pTime->attach_function(1, stub);
  pTemp->attach_function(1, stub);
  pStatus->attach_function(1, stub);
  pFan->attach_function(1, stub);

  addLine(pData);
  addLine(pTime);
  addLine(pTemp);
  addLine(pStatus);
  addLine(pFan);

  m_menu->get_currentScreen()->set_displayLineCount(2);
  m_menu->get_currentScreen()->set_focusPosition(Position::LEFT);
  m_menu->set_focusedLine(0);
  
  s0 = c.GetServices()->pCCM->LockSlot();
  s1 = c.GetServices()->pCCM->LockSlot();

  cc_fan1 = SET_CCHAR_SLOT(s0, CC_FAN1);
  cc_fan2 = SET_CCHAR_SLOT(s1, CC_FAN2);
  
  cc_fan = cc_fan1;

  pFan->set_asGlyph(2);

  update();
}

InfoScreen::~InfoScreen()
{
  if(s0) s0->Unlock();
  if(s1) s1->Unlock();
}

bool InfoScreen::onEvent(Event event)
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

  case EV_UPDATE_LOOP:
    ev_update();
    break;

  default:
    return false;
    break;
  }
  return true;
}

bool InfoScreen::ev_cw_step()
{
  m_menu->switch_focus(true);
  update();
  return true;
};

bool InfoScreen::ev_ccw_step()
{
  m_menu->switch_focus(false);
  return true;
};

bool InfoScreen::ev_confirm_pressed()
{
  cc_fan = cc_fan == cc_fan1 ? cc_fan2 : cc_fan1;
  update();
  return true;
};

bool InfoScreen::ev_cancel_pressed()
{
  m_controller.Back();
  return true;
};

bool InfoScreen::ev_update()
{
  return true;
};
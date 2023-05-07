#line 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\back_up\\menu_week_timer_back_up.cpp"

/*---------------------------------[INCLUDES]---------------------------------*/
#include "menu_week_timer.hpp"
#include "Arduino.h"
#include "custom_chars.hpp"
#include "MemoryFree.h"
#include "menu_controller.hpp"

/*---------------------------------[PREPROCESSOR DEFS]------------------------*/
#define WEEK_CFG_TAG        "week_cfg"
#define WEEK_LINE_1_INIT    "Week"
#define WEEK_LINE_2_INIT    "M T W T F S S A"
#define WEEK_MAX_OPTIONS    8
#define WEEK_FIRST_INDEX    0
#define WEEK_LAST_INDEX     (WEEK_MAX_OPTIONS - 1)

#define WEEK_MON_DAY_POS    0
#define WEEK_TUE_DAY_POS    1 
#define WEEK_WED_DAY_POS    2
#define WEEK_THU_DAY_POS    3
#define WEEK_FRI_DAY_POS    4
#define WEEK_SAT_DAY_POS    5
#define WEEK_SUN_DAY_POS    6
#define WEEK_ALL_DAYS_POS   7

/*---------------------------------[TYPE DEFS]--------------------------------*/
typedef union
{
  struct
  {
    uint8_t monday: 1;
    uint8_t tuesday: 1;
    uint8_t wednesday: 1;
    uint8_t thursday: 1;
    uint8_t friday: 1;
    uint8_t saturday: 1;
    uint8_t sunday: 1;
    uint8_t all: 1;
  }day;
  uint8_t mask;
}week_t;

typedef union
{
  struct
  {
    uint8_t monday;
    uint8_t tuesday;
    uint8_t wednesday;
    uint8_t thursday;
    uint8_t friday;
    uint8_t saturday;
    uint8_t sunday;
    uint8_t all;
  }day;
  uint8_t table[8];
}ui_options_t;



/*---------------------------------[PRIVATE DATA]-----------------------------*/
//static week_t week;
static ui_options_t ui_options;

#define WEEK_EMPTY_CHAR     ' '


static uint8_t cc_check = WEEK_EMPTY_CHAR;
static uint8_t cc_alien = WEEK_EMPTY_CHAR;

#define WEEK_SELEC_CHAR     cc_check
#define WEEK_CURSOR_CHAR    cc_alien

CCSlot * s0 = nullptr;
CCSlot * s1 = nullptr;

#if 0
static const char screen_tag[] = WEEK_CFG_TAG;
static char week_cfg_buf1[20] = WEEK_LINE_1_INIT;
static char week_cfg_buf2[20] = WEEK_LINE_2_INIT;

static EventHandler evh;
static LiquidScreen screen;

static ScreenHandle_t this_handle = {
  .name = {0},
  .controller = &screen,
  .event_handler = &evh  
};

static ScreenServices_t * services;

static week_t week;
static ui_options_t ui_options;
static uint8_t pos = 0;
static uint8_t last_pos = 0;

#define WEEK_EMPTY_CHAR     ' '


static uint8_t cc_check = WEEK_EMPTY_CHAR;
static uint8_t c1 = WEEK_EMPTY_CHAR; 
static uint8_t cc_alien = WEEK_EMPTY_CHAR;
static uint8_t c3 = WEEK_EMPTY_CHAR;
static uint8_t c4 = WEEK_EMPTY_CHAR;

#define WEEK_SELEC_CHAR     cc_check
#define WEEK_CURSOR_CHAR    cc_alien


/*---------------------------------[PRIVATE FUNCTIONS]------------------------*/
static void set_day(uint8_t pos)
{
  if(pos > WEEK_LAST_INDEX) return;

  if(pos == WEEK_ALL_DAYS_POS)
  {
    week.mask = 0xFF; // set all bits
  }
  else
  {
    week.mask |= (uint8_t)(0x01<<pos);
  }
}

static void clr_day(uint8_t pos)
{
  if(pos > WEEK_LAST_INDEX) return;

  if(pos == WEEK_ALL_DAYS_POS)
  {
    week.mask = 0x00; //clear all bits
  }
  else
  {
    week.mask &= (uint8_t)~(0x01<<pos);
  }
  
}

static bool is_day_selected(uint8_t pos)
{
  if (pos > WEEK_LAST_INDEX) return false;

  return week.mask & (0x01<<pos);
}

static void tog_day(uint8_t pos)
{
  if(is_day_selected(pos)){
    clr_day(pos);
  }
  else{
    set_day(pos);
  }
}

static void ui_update_week_options()
{
  for (size_t i = 0; i < WEEK_MAX_OPTIONS; i++) 
  {
#if 0    
    uint8_t option_pos = 2*i + 1;
    week_cfg_buf2[option_pos] = WEEK_EMPTY_CHAR;

    if(is_day_selected(i))
    {      
      week_cfg_buf2[option_pos] = WEEK_SELEC_CHAR;
    }
#else
    ui_options.table[i] = WEEK_EMPTY_CHAR;
    
    if(is_day_selected(i))
    {      
      ui_options.table[i] = WEEK_SELEC_CHAR; //
    }
  
#endif    
  }
}

static void increment_option_position()
{
  last_pos = pos;
  pos = (pos < WEEK_LAST_INDEX) ? (pos+1) : WEEK_FIRST_INDEX;
}

static void decrement_option_position()
{
  last_pos = pos;
  pos = (pos > WEEK_FIRST_INDEX) ? (pos-1) : WEEK_LAST_INDEX;
}

void evh_cc_step(void * obj)
{
  increment_option_position();
  
  //uint8_t cursor = 2*pos + 1;
  //uint8_t last_cursor = 2*last_pos + 1;

  //week_cfg_buf2[cursor] = WEEK_CURSOR_CHAR;
  ui_options.table[pos] = WEEK_CURSOR_CHAR;
  
  if(is_day_selected(last_pos))
  {    
    ui_options.table[last_pos] = WEEK_SELEC_CHAR;    
  }
  else
  {    
    ui_options.table[last_pos] = WEEK_EMPTY_CHAR;    
  }

  
}

 void evh_ccw_step(void * obj)
{
  decrement_option_position();
  
  //uint8_t cursor = 2*pos + 1;
  //uint8_t last_cursor = 2*last_pos + 1;

  //week_cfg_buf2[cursor] = WEEK_CURSOR_CHAR;
  ui_options.table[pos] = WEEK_CURSOR_CHAR;

  if(is_day_selected(last_pos))
  {    
    ui_options.table[last_pos] = WEEK_SELEC_CHAR;    
  }
  else
  {    
    ui_options.table[last_pos] = WEEK_EMPTY_CHAR;    
  }  
}

void evh_confirm_pressed(void * obj)
{
  tog_day(pos);
  ui_update_week_options();  
}

void evh_cancel_pressed(void * obj)
{
  
}

/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/

ScreenHandle_t * menu_week_timer(ScreenServices_t * srvs)
{
  //Serial.println("start week timer menu");
  services = srvs;
  LiquidLine * pLine1 = new LiquidLine(0, 0, week_cfg_buf1);

  // CCSlot * s0 = srvs->pCCM->LockSlot();
  // CCSlot * s1 = srvs->pCCM->LockSlot();
  // CCSlot * s2 = srvs->pCCM->LockSlot();
  //CCSlot * s3 = srvs->pCCM->LockSlot();
  //CCSlot * s4 = srvs->pCCM->LockSlot();

  //TODO: unlock slots on screen exit.

  // cc_check = SET_CCHAR_SLOT(s0, CC_CHECK);
  // c1 = SET_CCHAR_SLOT(s1, CC_BELL);
  // cc_alien = SET_CCHAR_SLOT(s2, CC_ALIEN);
  //c3 = SET_CCHAR_SLOT(s3, CC_HEART);
  //c4 = SET_CCHAR_SLOT(s4, CC_SPEAKER);
  

  // ui_options.day.monday = WEEK_CURSOR_CHAR; // <--- CURSOR START
  // ui_options.day.tuesday = WEEK_EMPTY_CHAR;
  // ui_options.day.wednesday = WEEK_EMPTY_CHAR;
  // ui_options.day.thursday = WEEK_EMPTY_CHAR;
  // ui_options.day.friday = WEEK_EMPTY_CHAR;
  // ui_options.day.saturday = WEEK_EMPTY_CHAR;
  // ui_options.day.sunday = WEEK_EMPTY_CHAR;
  // ui_options.day.all = WEEK_EMPTY_CHAR;

  //LiquidLine * pMonLine = new LiquidLine( 0, 1, "M", ui_options.day.monday);
  //LiquidLine * pTueLine = new LiquidLine( 2, 1, "T", ui_options.day.tuesday);
  // LiquidLine * pWedLine = new LiquidLine( 4, 1, "W", ui_options.day.wednesday);
  // LiquidLine * pThuLine = new LiquidLine( 6, 1, "T", ui_options.day.thursday);
  // LiquidLine * pFriLine = new LiquidLine( 8, 1, "F", ui_options.day.friday);
  // LiquidLine * pSatLine = new LiquidLine(10, 1, "S", ui_options.day.saturday);
  // LiquidLine * pSunLine = new LiquidLine(12, 1, "S", ui_options.day.sunday);
  // LiquidLine * pAllLine = new LiquidLine(14, 1, "A", ui_options.day.all);

  // pMonLine->set_asGlyph(2);
  // pTueLine->set_asGlyph(2);
  // pWedLine->set_asGlyph(2);
  // pThuLine->set_asGlyph(2);
  // pFriLine->set_asGlyph(2);
  // pSatLine->set_asGlyph(2);
  // pSunLine->set_asGlyph(2);
  // pSatLine->set_asGlyph(2);
  // pAllLine->set_asGlyph(2);

 Serial.println("add line");

  
  screen.add_line(*pLine1);
  // screen.add_line(*pMonLine);
  // screen.add_line(*pTueLine);
  //screen.add_line(*pWedLine);
#if 0
  screen.add_line(*pThuLine);
  screen.add_line(*pFriLine);
  screen.add_line(*pSatLine);
  screen.add_line(*pSunLine);
  screen.add_line(*pSatLine);
  screen.add_line(*pAllLine);
#endif
  Serial.println("add screen");

  Serial.print("Free Memory: ");
  Serial.print(freeMemory());
  Serial.println(" bytes");
  
  if(&screen != NULL)
  {
    srvs->pMenu->add_screen(screen);
  }


  Serial.println("screen added");
  
  // evh.add(EventHandler::EV_CW_STEP, evh_cc_step, (void*)0);
  // evh.add(EventHandler::EV_CCW_STEP, evh_ccw_step, (void*)0);
  // evh.add(EventHandler::EV_CONFIRM_PRESSED, evh_confirm_pressed, (void*)0);
  // evh.add(EventHandler::EV_CANCEL_PRESSED, evh_cancel_pressed, (void*)0);

  Serial.println("end week timer menu");

  return &this_handle;
}
#else

WeekTimerScreen::WeekTimerScreen(Services *s) : Screen(s)
{

}

WeekTimerScreen::~WeekTimerScreen()
{
  exit();
}

bool WeekTimerScreen::enter()
{
  m_menu = new LiquidMenu(*(m_services->pLcd));
  m_screen = new LiquidScreen();
#if 0  
  m_max_lines = 3;
  m_lines = new LiquidLine * [m_max_lines]; 

  for(int i = 0; i < m_max_lines; i++)
  {
    m_lines[i] = new LiquidLine(1,0);
    m_lines[i]->attach_function(1,stub);
    m_screen->add_line(*(m_lines[i]));
  }

  m_lines[0]->add_variable("LINE 0");
  m_lines[1]->add_variable("LINE 1");
  m_lines[2]->add_variable("LINE 2");
#else
  
  s0 = m_services->pCCM->LockSlot();
  s1 = m_services->pCCM->LockSlot();
  cc_check = SET_CCHAR_SLOT(s0, CC_CHECK);
  cc_alien = SET_CCHAR_SLOT(s1, CC_ALIEN);

  ui_options.day.monday = WEEK_CURSOR_CHAR; // <--- CURSOR START
  ui_options.day.tuesday = WEEK_EMPTY_CHAR;
  ui_options.day.wednesday = WEEK_EMPTY_CHAR;
  ui_options.day.thursday = WEEK_EMPTY_CHAR;
  ui_options.day.friday = WEEK_EMPTY_CHAR;
  ui_options.day.saturday = WEEK_EMPTY_CHAR;
  ui_options.day.sunday = WEEK_EMPTY_CHAR;
  ui_options.day.all = WEEK_EMPTY_CHAR;

  LiquidLine * pTitleLine = new LiquidLine(0, 0, "WEEK DAY");

  LiquidLine * pMonLine = new LiquidLine( 0, 1, "M", ui_options.day.monday);
  LiquidLine * pTueLine = new LiquidLine( 2, 1, "T", ui_options.day.tuesday);
  LiquidLine * pWedLine = new LiquidLine( 4, 1, "W", ui_options.day.wednesday);
  LiquidLine * pThuLine = new LiquidLine( 6, 1, "T", ui_options.day.thursday);
  LiquidLine * pFriLine = new LiquidLine( 8, 1, "F", ui_options.day.friday);
  LiquidLine * pSatLine = new LiquidLine(10, 1, "S", ui_options.day.saturday);
  LiquidLine * pSunLine = new LiquidLine(12, 1, "S", ui_options.day.sunday);
  LiquidLine * pAllLine = new LiquidLine(14, 1, "A", ui_options.day.all);

  pMonLine->set_asGlyph(2);
  pTueLine->set_asGlyph(2);
  pWedLine->set_asGlyph(2);
  pThuLine->set_asGlyph(2);
  pFriLine->set_asGlyph(2);
  pSatLine->set_asGlyph(2);
  pSunLine->set_asGlyph(2);
  pAllLine->set_asGlyph(2);
  
  m_screen->add_line(*pTitleLine);
  m_screen->add_line(*pMonLine);
  m_screen->add_line(*pTueLine);
  m_screen->add_line(*pWedLine);
  m_screen->add_line(*pThuLine);
  m_screen->add_line(*pFriLine);
  m_screen->add_line(*pSatLine);  
  m_screen->add_line(*pSunLine);
  m_screen->add_line(*pAllLine);
#endif

  //m_screen->set_displayLineCount(2);
  //m_screen->set_focusPosition(Position::LEFT);

  m_menu->add_screen(*m_screen);
 //m_menu->set_focusedLine(0);
  m_menu->update();
  return true;
}

bool WeekTimerScreen::exit()
{
  if(s0) s0->Unlock();
  if(s1) s1->Unlock();

  if(m_menu)
  {
    delete(m_menu);
    m_menu = nullptr;
    m_screen = nullptr;
  }

  m_max_lines = 0;  

  return true;
}

bool WeekTimerScreen::update()
{
  return true;
}

bool WeekTimerScreen::onEvent(Event event)
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

bool WeekTimerScreen::ev_cw_step() 
{
  Serial.println("CW STEP EVENT");
  m_menu->switch_focus(true);
  return true;
};

bool WeekTimerScreen::ev_ccw_step()
{
  Serial.println("CCW STEP EVENT");
  m_menu->switch_focus(false);
  return true;
};

bool WeekTimerScreen::ev_confirm_pressed()
{
  Serial.println("CONFIRM PRESSED EVENT");
  return true;
};

bool WeekTimerScreen::ev_cancel_pressed()
{
  exit();
  
  Node<MenuNode> *node = m_services->pNavSys->navigateBack();

  if (node)
  {
    node->data->pScreen->enter();
  }

  return true;
};

#endif
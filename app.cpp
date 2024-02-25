/*---------------------------------[INCLUDES]---------------------------------*/

#include "app.hpp"

// Arduino
#include "MemoryFree.h"

// App
#include "menu_controller.hpp"
#include "selector.hpp"
#include "screen_factory.hpp"

/*---------------------------------[PREPROCESSOR DEFS]------------------------*/

#define LCD_ADDRESS 0x3F
#define LCD_COLUMNS 16
#define LCD_ROWS 2

#define CLK_PIN 2
#define DT_PIN 3
#define SW_PIN 4

/*---------------------------------[TYPE DEFS]--------------------------------*/

/*---------------------------------[PRIVATE DATA]-----------------------------*/

static LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
static MenuController *menu;

static Selector selector(CLK_PIN, DT_PIN, SW_PIN);

static TimeModel timer1(10, 55);
static TimeModel timer2(90, 10);
static WeekModel weekModel;

static ScreenFactory<TimeModel> t1sf(&timer1);
static ScreenFactory<TimeModel> t2sf(&timer2);
static ScreenFactory<WeekModel> weeksf(&weekModel);

CREATE_SCREEN(screen_home   , "HOME"    , NULL);
CREATE_SCREEN(screen_t1     , "TIMER 1" , &t1sf);
CREATE_SCREEN(screen_t2     , "TIMER 2" , &t2sf);
CREATE_SCREEN(screen_week   , "WEEK"    , &weeksf);

/*---------------------------------[PRIVATE FUNCTIONS]------------------------*/

static void ccw_event_cb()
{
    menu->TriggerEvent(Event::EV_CCW_STEP);
}

static void cw_event_cb()
{
    menu->TriggerEvent(Event::EV_CW_STEP);
}

static void sw_sp_event_cb()
{
    menu->TriggerEvent(Event::EV_CONFIRM_PRESSED);
    App_printFreeMemory();
}

static void sw_lp_event_cb()
{
    menu->TriggerEvent(Event::EV_CANCEL_PRESSED);
    App_printFreeMemory();
}


/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/

void App_setup()
{
    Serial.println("### APP INIT ###");

    App_printFreeMemory();

    selector.addCallback(Selector::CbType::CCW_CB, ccw_event_cb);
    selector.addCallback(Selector::CbType::CW_CB, cw_event_cb);
    selector.addCallback(Selector::CbType::SW_SP_CB, sw_sp_event_cb);
    selector.addCallback(Selector::CbType::SW_LP_CB, sw_lp_event_cb);

    menu = new MenuController(lcd);

    menu->AddScreen("/home"         , screen_home);
    menu->AddScreen("/home/t1"      , screen_t1);
    menu->AddScreen("/home/t2"      , screen_t2);
    menu->AddScreen("/home/week"    , screen_week);    

    menu->Enter("/home");
    
    App_printFreeMemory();
}

void App_loop()
{
    selector.run();
    timer1.update();
    timer2.update();
    menu->TriggerEvent(Event::EV_UPDATE_LOOP);
}

void App_printFreeMemory()
{
    Serial.print("Free Memory: ");
    Serial.print(freeMemory());
    Serial.println(" bytes");
}
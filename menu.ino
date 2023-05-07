#include <Arduino.h>
#include <avr/pgmspace.h>
#include "menu_controller.hpp"
#include "selector.hpp"

#include "menu_week_timer.hpp"
#include "menu_time.hpp"
#include "MemoryFree.h"


#define LCD_ADDRESS   0x3F
#define LCD_COLUMNS   16
#define LCD_ROWS      2

#define CLK_PIN           2
#define DT_PIN            3
#define SW_PIN            4

static LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
static MenuController * menu;

static Selector selector(CLK_PIN, DT_PIN, SW_PIN);

const char home_fstr[] PROGMEM = "HOME";
const char week_fstr[] PROGMEM = "WEEK";
const char time_fstr[] PROGMEM = "TIME";

void ccw_event_cb();
void cw_event_cb();
void sw_sp_event_cb();
void sw_lp_event_cb();
void print_free_memory()
{
  Serial.print("Free Memory: ");
  Serial.print(freeMemory());
  Serial.println(" bytes");
}

void setup() {

  
  // Setup Serial Monitor
  Serial.begin(115200);
  while(!Serial);
  Serial.println("### INIT ###");

  print_free_memory();

  // Set encoder pins as inputs
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);

  selector.addCallback(Selector::CbType::CCW_CB, ccw_event_cb); 
  selector.addCallback(Selector::CbType::CW_CB, cw_event_cb); 
  selector.addCallback(Selector::CbType::SW_SP_CB, sw_sp_event_cb); 
  selector.addCallback(Selector::CbType::SW_LP_CB, sw_lp_event_cb); 

  menu = new MenuController(lcd);

  print_free_memory(); 

  Screen::Services * services = menu->GetServices();

  menu->AddContainer("/home", home_fstr);
  menu->AddScreen("/home/week", week_fstr, new WeekTimerScreen(services));
  menu->AddScreen("/home/time", time_fstr, new TimeScreen(services));  
  menu->Enter("/home");
}

void loop()
{
  selector.run();
  menu->TriggerEvent(Screen::EV_UPDATE_LOOP);
}

void ccw_event_cb()
{
  menu->TriggerEvent(Screen::EV_CCW_STEP);
}

void cw_event_cb()
{
  menu->TriggerEvent(Screen::EV_CW_STEP);
}

void sw_sp_event_cb()
{
  menu->TriggerEvent(Screen::EV_CONFIRM_PRESSED);
  print_free_memory();
}

void sw_lp_event_cb()
{
  menu->TriggerEvent(Screen::EV_CANCEL_PRESSED);
  print_free_memory();
}

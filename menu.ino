#include <Arduino.h>
#include <avr/pgmspace.h>
#include "MemoryFree.h"

#include "menu_controller.hpp"
#include "selector.hpp"
#include "screen_factory.hpp"


#define LCD_ADDRESS   0x3F
#define LCD_COLUMNS   16
#define LCD_ROWS      2

#define CLK_PIN           2
#define DT_PIN            3
#define SW_PIN            4

static LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
static MenuController * menu;

static Selector selector(CLK_PIN, DT_PIN, SW_PIN);


TimeModel timer1(10, 55);
//TimeModel timer2(90, 10);

ScreenFactory<TimeModel> t1sf(&timer1);
//ScreenFactory<TimeModel> t2sf(&timer2);


const char home_fstr[] PROGMEM = "HOME";
const char week_fstr[] PROGMEM = "WEEK";
const char time_fstr[] PROGMEM = "TIME";
const char timer1_fstr[] PROGMEM = "TIMER 1";
const char timer2_fstr[] PROGMEM = "TIMER 2";

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

  menu->AddContainer("/home", home_fstr);
  //menu->AddContainer("/home/t1", timer1_fstr);
  //menu->AddScreen("/home/t1/week", week_fstr, new WeekTimerScreen(services));
  menu->AddScreen("/home/t1", timer1_fstr, t1sf.factory());
  //menu->AddContainer("/home/t2", timer2_fstr);  
  //menu->AddScreen("/home/t2/week", week_fstr, new WeekTimerScreen(services));
  //menu->AddScreen("/home/t2", timer2_fstr, t2sf.factory()); 

  print_free_memory(); 


  menu->Enter("/home");
  print_free_memory(); 
}

void loop()
{
  selector.run();
  timer1.update();
  menu->TriggerEvent(Event::EV_UPDATE_LOOP);
}

void ccw_event_cb()
{
  menu->TriggerEvent(Event::EV_CCW_STEP);
}

void cw_event_cb()
{
  menu->TriggerEvent(Event::EV_CW_STEP);
}

void sw_sp_event_cb()
{
  print_free_memory();
  menu->TriggerEvent(Event::EV_CONFIRM_PRESSED);  
}

void sw_lp_event_cb()
{
  print_free_memory();
  menu->TriggerEvent(Event::EV_CANCEL_PRESSED);  
}

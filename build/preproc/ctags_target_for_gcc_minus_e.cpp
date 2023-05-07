# 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino"
# 2 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino" 2
# 3 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino" 2
# 4 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino" 2
# 5 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino" 2

# 7 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino" 2
# 8 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino" 2
# 9 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino" 2
# 19 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino"
static LiquidCrystal_I2C lcd(0x3F, 16, 2);
static MenuController * menu;

static Selector selector(2, 3, 4);

const char home_fstr[] 
# 24 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino" 3
                      __attribute__((__progmem__)) 
# 24 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino"
                              = "HOME";
const char week_fstr[] 
# 25 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino" 3
                      __attribute__((__progmem__)) 
# 25 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino"
                              = "WEEK";
const char time_fstr[] 
# 26 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino" 3
                      __attribute__((__progmem__)) 
# 26 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu6.ino"
                              = "TIME";

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
  pinMode(2, 0x0);
  pinMode(3, 0x0);
  pinMode(4, 0x2);

  selector.addCallback(Selector::CbType::CCW_CB, ccw_event_cb);
  selector.addCallback(Selector::CbType::CW_CB, cw_event_cb);
  selector.addCallback(Selector::CbType::SW_SP_CB, sw_sp_event_cb);
  selector.addCallback(Selector::CbType::SW_LP_CB, sw_lp_event_cb);

  menu = new MenuController(lcd);

  print_free_memory();

  Screen::Services * services = menu->GetServices();

  menu->AddContainer("/home", home_fstr);
  menu->AddScreen("/home/week", week_fstr, new WeekTimerScreen(services));
  menu->AddScreen("/home/time", time_fstr, new WeekTimerScreen(services));
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

#line 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\menu_time.cpp"


/*---------------------------------[INCLUDES]---------------------------------*/
#include "menu_time.hpp"
# if 0
/*---------------------------------[PREPROCESSOR DEFS]------------------------*/
#define TIME_LINE_1_INIT    "Time"
#define TIME_LINE_2_INIT    "    09:30:23    "

/*---------------------------------[TYPE DEFS]--------------------------------*/

/*---------------------------------[PRIVATE DATA]-----------------------------*/
static char buffer_line1[20] = TIME_LINE_1_INIT;
static char buffer_line2[20] = TIME_LINE_2_INIT;

static uint8_t hour = 0;
static uint8_t min = 0;
static uint8_t sec = 0;


static EventHandler evh;
static LiquidScreen screen;

static ScreenHandle_t this_handle = {
  .name = {0},
  .controller = &screen,
  .event_handler = &evh
};

static ScreenServices_t * services;

/*---------------------------------[PRIVATE FUNCTIONS]------------------------*/
void ev_cw_step(void * obj)
{
  hour = (hour == 23) ? (0) : (++hour);
};

void ev_ccw_step(void * obj)
{
  hour = (hour == 0) ? (23) : (--hour);
};


/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/
ScreenHandle_t * menu_time(ScreenServices_t * srvs)
{
  services = srvs;

  //LiquidLine * pLine1 = new LiquidLine(0, 0, buffer_line1);
  LiquidLine * pLine2 = new LiquidLine(4, 1, hour, ":", min);

  evh.add(EventHandler::EV_CW_STEP, ev_cw_step, (void*)0);
  evh.add(EventHandler::EV_CCW_STEP, ev_ccw_step, (void*)0);

  return &this_handle;
}

#endif
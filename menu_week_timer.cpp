/*---------------------------------[INCLUDES]---------------------------------*/
#include "menu_week_timer.hpp"
#include "NoDelay.h"
#include "MemoryFree.h"

/*---------------------------------[MACROS]-----------------------------------*/
#define WEEK_EMPTY_CHAR     ' '
#define WEEK_OPTIONS        8
#define WEEK_FIRST_INDEX    0
#define WEEK_LAST_INDEX     WEEK_OPTIONS-1


/*---------------------------------[PRIVATE]----------------------------------*/
class WeekUI {
public:
    WeekUI(Services* s, WeekModel& w, int cursor = 0);

    using Options = union {
        struct {
            uint8_t monday;
            uint8_t tuesday;
            uint8_t wednesday;
            uint8_t thursday;
            uint8_t friday;
            uint8_t saturday;
            uint8_t sunday;
            uint8_t all;
        } day;
        uint8_t table[WEEK_OPTIONS];
    };

    void setSelectedDay();
    void clearSelectedDay();
    void toggleSelectedDay();
    bool isSelectedDaySet() const;
    void incrementCursor();
    void decrementCursor();
    bool blinkCursor();
    const Options& getOptions() const;

private:
    WeekModel& weekModel;
    int cursor;
    int lastCursor;
    noDelay blinkTimer;

    uint8_t selectChar;
    uint8_t cursorChar;
    CCSlot * s0;
    CCSlot * s1;

    Options options;
};

WeekUI::WeekUI(Service* s, WeekModel& week, int cursor) : weekModel(week), cursor(cursor), lastCursor(0) {
    selectChar = SET_CCHAR_SLOT(s0, CC_CHECK);
    cursorChar = SET_CCHAR_SLOT(s1, CC_ALIEN);
}

void WeekUI::setSelectedDay() {
    weekModel.setDay(static_cast<WeekModel::Day>(cursor));
}

void WeekUI::clearSelectedDay() {
    weekModel.clearDay(static_cast<WeekModel::Day>(cursor));
}

void WeekUI::toggleSelectedDay() {
    weekModel.toggleDay(static_cast<WeekModel::Day>(cursor));
}

bool WeekUI::isSelectedDaySet() const {
    return weekModel.isDaySelected(static_cast<WeekModel::Day>(cursor));
}

void WeekUI::incrementCursor() {
    lastCursor = cursor;
    cursor = (cursor < WEEK_LAST_INDEX) ? (cursor + 1) : WEEK_FIRST_INDEX;
}

void WeekUI::decrementCursor() {
    lastCursor = cursor;
    cursor = (cursor > WEEK_FIRST_INDEX) ? (cursor - 1) : WEEK_LAST_INDEX;
}

bool WeekUI::blinkCursor() {
    static bool on_init = true;
    static bool show_cursor = true;

    if (on_init) {
        blinkTimer.start();
        on_init = false;
    }

    if (blinkTimer.update()) {
        if (show_cursor) {
            options.table[cursor] = cursorChar;
        } else {
            if (isSelectedDaySet()) {
                options.table[cursor] = selectChar;
            } else {
                options.table[cursor] = WEEK_EMPTY_CHAR;
            }
        }

        show_cursor = !show_cursor;
        blinkTimer.start();
        return true;
    }
    return false;
}

const WeekUI::Options& WeekUI::getOptions() const {
    return options;
}

/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/

WeekTimerScreen::WeekTimerScreen(Services *s, WeekModel *w) : Screen(s)
{
  ui = new WeekUI(w, s, 0);
  WeekUI::Options opt = ui->getOptions();

  LiquidLine * pTitleLine = new LiquidLine(0, 0, "WEEK");

  LiquidLine * pMonLine = new LiquidLine( 0, 1, "M", opt.day.monday);
  LiquidLine * pTueLine = new LiquidLine( 2, 1, "T", opt.day.tuesday);
  LiquidLine * pWedLine = new LiquidLine( 4, 1, "W", opt.day.wednesday);
  LiquidLine * pThuLine = new LiquidLine( 6, 1, "T", opt.day.thursday);
  LiquidLine * pFriLine = new LiquidLine( 8, 1, "F", opt.day.friday);
  LiquidLine * pSatLine = new LiquidLine(10, 1, "S", opt.day.saturday);
  LiquidLine * pSunLine = new LiquidLine(12, 1, "S", opt.day.sunday);
  LiquidLine * pAllLine = new LiquidLine(14, 1, "A", opt.day.all);

  pMonLine->set_asGlyph(2);
  pTueLine->set_asGlyph(2);
  pWedLine->set_asGlyph(2);
  pThuLine->set_asGlyph(2);
  pFriLine->set_asGlyph(2);
  pSatLine->set_asGlyph(2);
  pSunLine->set_asGlyph(2);
  pAllLine->set_asGlyph(2);
  
  addLine(pTitleLine);
  addLine(pMonLine);
  addLine(pTueLine);
  addLine(pWedLine);
  addLine(pThuLine);
  addLine(pFriLine);
  addLine(pSatLine);  
  addLine(pSunLine);
  addLine(pAllLine);

  update();
}

WeekTimerScreen::~WeekTimerScreen()
{
  delete(ui);
}

bool WeekTimerScreen::onEvent(Event event)
{
  switch (event)
  {
  case EV_CONFIRM_PRESSED:
    //ev_confirm_pressed();
    ui->toggleSelectedDay();
    break;

  case EV_CANCEL_PRESSED:
    Node<MenuNode> *node = m_services->pNavSys->navigateBack();
    //TODO: implement back
    break;

  case EV_CCW_STEP:
    //ev_ccw_step();
    ui->decrementCursor();
    break;

  case EV_CW_STEP:
    //ev_cw_step();
    ui->incrementCursor();
    break;

  case EV_UPDATE_LOOP:
    update();
    break;

  default:
    return false;
    break;
  }
  return true;
}
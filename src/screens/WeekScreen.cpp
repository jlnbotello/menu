/*---------------------------------[INCLUDES]---------------------------------*/
#include "WeekScreen.h"
#include "NoDelay.h"
#include "MemoryFree.h"

/*---------------------------------[MACROS]-----------------------------------*/
#define WEEK_EMPTY_CHAR ' '
#define WEEK_OPTIONS 8
#define WEEK_FIRST_INDEX 0
#define WEEK_LAST_INDEX WEEK_OPTIONS - 1

/*---------------------------------[PRIVATE]----------------------------------*/
class WeekUI
{
public:
    WeekUI(Services &s, WeekModel &w, int cursor = 0);
    ~WeekUI();

    using Options = union
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
        } day;
        uint8_t table[WEEK_OPTIONS];
    };

    void setSelectedDay();
    void clearSelectedDay();
    void toggleSelectedDay();
    bool isSelectedDaySet();
    bool isLastSelectedDaySet();
    void incrementCursor();
    void decrementCursor();
    bool blinkCursor();
    Options &getOptions();
    void update();

private:
    WeekModel &weekModel;
    int cursor;
    int lastCursor;
    noDelay blinkTimer;

    uint8_t selectChar;
    uint8_t cursorChar;
    CCSlot *s0;
    CCSlot *s1;

    Options options = {0};
    Services &services;

    bool on_init = true;
    bool show_cursor = true;
};

WeekUI::WeekUI(Services &s, WeekModel &week, int cursor) : services(s), weekModel(week), cursor(cursor), lastCursor(cursor)
{
    blinkTimer = noDelay(500);

    s0 = services.pCCM->LockSlot();
    s1 = services.pCCM->LockSlot();

    selectChar = SET_CCHAR_SLOT(s0, CC_CHECK);
    cursorChar = SET_CCHAR_SLOT(s1, CC_ALIEN);

    update();
}

WeekUI::~WeekUI()
{
    s0->Unlock();
    s1->Unlock();
}

void WeekUI::setSelectedDay()
{
    weekModel.setDay(static_cast<WeekModel::Day>(cursor));
}

void WeekUI::clearSelectedDay()
{
    weekModel.clearDay(static_cast<WeekModel::Day>(cursor));
}

void WeekUI::toggleSelectedDay()
{
    weekModel.toggleDay(static_cast<WeekModel::Day>(cursor));
    update();
}

bool WeekUI::isSelectedDaySet()
{
    return weekModel.isDaySelected(static_cast<WeekModel::Day>(cursor));
}

bool WeekUI::isLastSelectedDaySet()
{
    return weekModel.isDaySelected(static_cast<WeekModel::Day>(lastCursor));
}

void WeekUI::incrementCursor()
{
    lastCursor = cursor;
    cursor = (cursor < WEEK_LAST_INDEX) ? (cursor + 1) : WEEK_FIRST_INDEX;
    update();
}

void WeekUI::decrementCursor()
{
    lastCursor = cursor;
    cursor = (cursor > WEEK_FIRST_INDEX) ? (cursor - 1) : WEEK_LAST_INDEX;
    update();
}

bool WeekUI::blinkCursor()
{
    if (on_init)
    {
        blinkTimer.start();
        on_init = false;
    }

    if (blinkTimer.update())
    {
        if (show_cursor)
        {
            options.table[cursor] = cursorChar;
        }
        else
        {
            if (isSelectedDaySet())
            {
                options.table[cursor] = selectChar;
            }
            else
            {
                options.table[cursor] = WEEK_EMPTY_CHAR;
            }
        }

        show_cursor = !show_cursor;
        blinkTimer.start();
        return true;
    }
    return false;
}

WeekUI::Options &WeekUI::getOptions()
{
    return options;
}

void WeekUI::update()
{
    for (size_t i = 0; i < WEEK_OPTIONS; i++)
    {
        if (weekModel.isDaySelected(static_cast<WeekModel::Day>(i)))
        {
            options.table[i] = selectChar;
        }
        else
        {
            options.table[i] = WEEK_EMPTY_CHAR;
        }
    }
}

/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/

WeekScreen::WeekScreen(MenuController &c, WeekModel &w) : Screen(c)
{
    ui = new WeekUI(*c.GetServices(), w);
    WeekUI::Options opt = ui->getOptions();

    LiquidLine *pTitleLine = new LiquidLine(0, 0, "WEEK");

    LiquidLine *pMonLine = new LiquidLine(0, 1, "M", ui->getOptions().day.monday);
    LiquidLine *pTueLine = new LiquidLine(2, 1, "T", ui->getOptions().day.tuesday);
    LiquidLine *pWedLine = new LiquidLine(4, 1, "W", ui->getOptions().day.wednesday);
    LiquidLine *pThuLine = new LiquidLine(6, 1, "T", ui->getOptions().day.thursday);
    LiquidLine *pFriLine = new LiquidLine(8, 1, "F", ui->getOptions().day.friday);
    LiquidLine *pSatLine = new LiquidLine(10, 1, "S", ui->getOptions().day.saturday);
    LiquidLine *pSunLine = new LiquidLine(12, 1, "S", ui->getOptions().day.sunday);
    LiquidLine *pAllLine = new LiquidLine(14, 1, "A", ui->getOptions().day.all);

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
}

WeekScreen::~WeekScreen()
{
    delete (ui);
}

bool WeekScreen::onEvent(Event event)
{
    switch (event)
    {
    case EV_CONFIRM_PRESSED:
        ui->toggleSelectedDay();
        update();
        break;

    case EV_CANCEL_PRESSED:
        m_controller.Back();
        break;

    case EV_CCW_STEP:
        ui->decrementCursor();
        update();
        break;

    case EV_CW_STEP:
        ui->incrementCursor();
        update();
        break;

    case EV_UPDATE_LOOP:
        if (ui->blinkCursor())
        {
            update();
        }

        break;

    default:
        return false;
        break;
    }
    return true;
}
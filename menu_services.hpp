#ifndef __MENU_SERVICES_HPP__
#define __MENU_SERVICES_HPP__

#include "custom_chars.hpp"
#include "navigator.hpp"

class ScreenFactoryInterface;

typedef struct
{
    const char *name;
    ScreenFactoryInterface *factory;
} MenuNode;

typedef struct
{
    CustomCharManager *pCCM;
    NavigationSystem<MenuNode> *pNavSys;
    DisplayClass *pLcd;
} Services;

typedef enum
{
EV_CW_STEP,
EV_CCW_STEP,
EV_CONFIRM_PRESSED,
EV_CANCEL_PRESSED,
EV_UPDATE_LOOP,
EVENT_ID_MAX
} Event;

#endif /* __MENU_SERVICES_HPP__ */
#ifndef __MENU_SERVICES_H__
#define __MENU_SERVICES_H__

#include "CustomChars.h"
#include "Navigator.h"

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

#endif /* __MENU_SERVICES_H__ */
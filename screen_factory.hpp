#ifndef __SCREEN_FACTORY_HPP__
#define __SCREEN_FACTORY_HPP__

#include "menu_time.hpp"
#include "menu_week.hpp"
#include "menu_container.hpp"



class ScreenWrapper {
    Screen* screen;

public:
    ScreenWrapper(MenuController &c, void* controller) {
        screen = new ContainerScreen(c);
    }

    ScreenWrapper(MenuController &c, WeekModel* m) {
        screen = new WeekTimerScreen(c, *m);
    }

    ScreenWrapper(MenuController &c, TimeModel *m) {
        screen = new TimeScreen(c, *m);
    }

    /* Add more constuctor here */

    Screen* getScreen() {
        return screen;
    }
};

class ScreenFactoryInterface
{
public:
    virtual Screen* createScreen(MenuController &c) = 0;
};

template <typename T>
class ScreenFactory: public ScreenFactoryInterface{
    T* model = nullptr;
public:
    ScreenFactory(T * m): model(m){};
    
    Screen* createScreen(MenuController &c) override 
    {
        ScreenWrapper wrapper(c, model);
        return wrapper.getScreen();
    }

    ScreenFactoryInterface * factory()
    {
        return (ScreenFactoryInterface *) this;
    }
};

struct ScreenHandlerStruct
{
  const char * title;  
  ScreenFactoryInterface * factory;
};

typedef struct ScreenHandlerStruct ScreenHandler;

#define CREATE_SCREEN(VarName, title, factory) \
static const char VarName ## _Title[] PROGMEM = title; \
static const ScreenHandler VarName = {VarName ## _Title, (ScreenFactoryInterface *) factory}

#endif /* __SCREEN_FACTORY_HPP__ */
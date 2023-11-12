#include "screen.hpp"
#include "menu_week_timer.hpp"
#include "menu_time.hpp"

class ScreenWrapper {
    Screen* screen;

public:
    ScreenWrapper(Screen::Services* services, WeekModel* controller) {
        screen = new WeekTimerScreen(services, controller);
    }

    ScreenWrapper(Screen::Services* services, TimeModel* controller) {
        screen = new TimeScreen(services, controller); //FIXME: Modify constructor
    }

    /* Add more constuctor here */

    Screen* getScreen() {
        return screen;
    }
};

class ScreenFactoryInterface
{
public:
    virtual Screen* createScreen(Screen::Services * services) = 0;
};

template <typename T>
class ScreenFactory: public ScreenFactoryInterface{
    T* controller;
public:
    ScreenFactory(T * c): controller(c){};
    
    Screen* createScreen(Screen::Services * services) override {
        T* dependency = static_cast<T*>(controller);
        ScreenWrapper screenWrapper(services, controller);
        return screenWrapper.getScreen();
    }
};
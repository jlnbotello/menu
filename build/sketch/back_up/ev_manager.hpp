#line 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\back_up\\ev_manager.hpp"
#include "Arduino.h"
#define STL_AVAILABLE 0
#if STL_AVAILABLE
#include <map>
#include <functional>
#include <string>
#else
#include "map.hh"
#endif

class EventHandler
{
public:
  // typedef enum
  // {
  //   EV_CW_STEP,
  //   EV_CCW_STEP,
  //   EV_CONFIRM_PRESSED,
  //   EV_CANCEL_PRESSED,
  //   EV_500MS_TICK,
  //   __EV_TABLE_LENGTH
  // } Id_t;

  template<typename T>
  using cb_t = void (*)(T*);

  template<typename T>
  struct callback_data_t {
      int id;
      void (*callback)(void*);
      T* obj;
      callback_data_t* next;
  };
  
  EventHandler();
#if STL_AVAILABLE  
  bool add(Id_t id, std::function<void(void)> handler);
#else
  ~EventHandler();
  template<typename T>
  bool add(int id, cb_t<T> callback, T* obj);
#endif 
  bool trigger(int id);
 

private:
#if STL_AVAILABLE  
  std::function<void(void)> handler_table[__EV_TABLE_LENGTH];
#else
  callback_data_t<void>* m_callbacks = nullptr;
#endif  
};

class EventRouter
{
public:
  EventRouter();
  bool add(String url, EventHandler * evm);
  bool route(String url, EventHandler::Id_t ev);
  
private:
#if STL_AVAILABLE
  std::map<std::string, EventHandler *> map;
#else
  Map<EventHandler *> map;
#endif
};

#include "ev_manager_inl.hpp"
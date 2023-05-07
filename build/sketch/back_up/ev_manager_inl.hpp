#line 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\back_up\\ev_manager_inl.hpp"
template<typename T> 
bool EventHandler::add(int id, cb_t<T> callback, T* obj)
{
  if(!callback) return false;
  callback_data_t<T>* data = new callback_data_t<T>;
  data->id = id;
  data->callback = reinterpret_cast<void (*)(void*)>(callback);
  data->obj = obj;
  data->next = nullptr;
  if (!m_callbacks) {
      m_callbacks = reinterpret_cast<callback_data_t<void>*>(data);
  } else {
      callback_data_t<void>* last = reinterpret_cast<callback_data_t<void>*>(m_callbacks);
      while (last->next) {
          last = last->next;
      }
      last->next = reinterpret_cast<callback_data_t<void>*>(data);
  }
  return true;
};
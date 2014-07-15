//
//  EventHandler.h
//  EventManager
//
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <cassert>

#include "Event.h"

template <typename T>
class EventHandler
  : public EventBase
{
  typedef void (T::*TCallback)(EventParams& args);

  T*        m_pClassInst;
  TCallback m_pCallbackFunc;
public:

  // Constructor which stores a pointer to a class instance, and the callback function
  EventHandler(T* pClassInst, TCallback cbFunction)
    : m_pClassInst(pClassInst)
    , m_pCallbackFunc(cbFunction)
  {
    assert(m_pClassInst);
  }

  // Destructor
  virtual ~EventHandler()
  {
	  m_pClassInst = nullptr;
	  m_pCallbackFunc = nullptr;
  }

  // Search helper to find a specific pointer
  virtual bool IsEvent(void* pInst) const
  {
	  return (T*)pInst == m_pClassInst;
  }

  // Call the callback function
  virtual void Fire(EventParams& args)
  {
    if (m_pClassInst) {
      (m_pClassInst->*m_pCallbackFunc)(args);
    }
  }
};

#endif

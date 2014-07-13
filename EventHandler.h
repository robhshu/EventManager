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

  // Construct a new handler to store a class instance and target function
  EventHandler(T* pClassInst, TCallback cbFunction)
    : m_pClassInst(pClassInst)
    , m_pCallbackFunc(cbFunction)
  { }

  // Override the Run function in EventBase to call to the class function
  virtual void Run(EventParams& args)
  {
    assert(m_pClassInst);

    (m_pClassInst->*m_pCallbackFunc)(args);
  }
};

#endif

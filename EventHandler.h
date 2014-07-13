//
//  EventHandler.h
//  EventManager
//
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <cassert>
#include <memory>

#include "Event.h"

template <typename T>
class EventHandler
  : public EventBase
{
  typedef void (T::*TCallback)(EventParams& args);

  std::shared_ptr<T>  m_classInst;
  TCallback           m_pCallbackFunc;

public:

  // Construct a new handler to store a class instance and target function
  EventHandler(std::shared_ptr<T>& rClassInst, TCallback cbFunction)
    : m_classInst(rClassInst)
    , m_pCallbackFunc(cbFunction)
  {
    assert(m_classInst);
  }

  // Override the Run function in EventBase to call to the class function
  virtual void Run(EventParams& args)
  {
    assert(m_classInst); // object may have been deleted?

    if (m_classInst) {

      (m_classInst.get()->*m_pCallbackFunc)(args);
    }
  }
};

#endif

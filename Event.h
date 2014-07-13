//
//  Event.h
//  EventManager
//
#ifndef EVENT_H
#define EVENT_H

#include <cassert>

#include <vector>
#include <memory>

#include "EventParams.h"
#include "EventHandler.h"

class EventBase
{
public:
  // Abstract call overriden by each listener object (which wraps EventHandler)
  virtual void Run(EventParams& args) = 0;
};

class Event
{
  typedef std::shared_ptr<EventBase>  EventHandle;
  typedef std::vector<EventHandle>    EventHandleVec;

  EventHandleVec m_callbackVec;
public:

  // Add a callback for this event
  template <typename T>
  void AddListener(std::shared_ptr<T>& spInst, void(T::*func)(EventParams& args))
  {
    EventHandle handle(new EventHandler<T>(spInst, func));
    m_callbackVec.push_back(handle);
  }

  // Run this event over all associated listeners
  void operator()(EventParams& args);
};

#endif

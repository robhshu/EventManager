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
  // Abstract call to trigger the event
  virtual void Fire(EventParams& args) = 0;
  virtual bool IsEvent(void* pInst) const = 0;
  virtual ~EventBase() {} 
};

class Event
{
  typedef std::vector<EventBase* > EventHandleVec;

  // List of abstract event handlers
  EventHandleVec m_callbackVec;
public:

  // Cleanup our event handlers
  ~Event();

  // Create an event handler for this callback
  template <typename T>
  void AddListener(T* spInst, void(T::*func)(EventParams& args))
  {
    EventHandler<T>* handle(new EventHandler<T>(spInst, func));
    m_callbackVec.push_back(handle);
  }

  // Remove references to a specific callback instance
  void RemoveListener(void* pInst);

  // Number of callbacks for this event
  size_t Count() const { return m_callbackVec.size(); }

  // Functor to trigger the event callbacks
  void operator()(EventParams& args);
};

#endif

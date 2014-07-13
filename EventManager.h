//
//  EventManager.h
//  EventManager
//
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <cassert>

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "EventParams.h"
#include "Event.h"
#include "EventHandler.h"

template<typename T>
class EventManager
{
  typedef std::map<T, Event> MappedEvents;
  MappedEvents m_events;

protected:
  EventManager(){ }

public:

  // Fetch an instance of the EventManager of this type
  static EventManager& Get()
  {
    static EventManager sManager;
    return sManager;
  }

  // Check that there is an event of this type registered
  bool HasEvent(const T& rEventKey) const
  {
    return m_events.find(rEventKey) != m_events.end();
  }

  // Triggers an event determined by the key
  void OnEvent(const T& rEventKey, EventParams& args)
  {
    MappedEvents::iterator itResult = m_events.find(rEventKey);

    // Event should already exist
    if (itResult != m_events.end()) {
      (*itResult).second(args);
    }
  }

  // Register a new listener based on a class instance (static or dynamic)
  template <typename EventT>
  void RegisterEvent(const T& rEventKey, std::shared_ptr<EventT>& spInst, void (EventT::*func)(EventParams& args))
  {
    assert(spInst);

    // Our map will automatically add a non-existant key
    m_events[rEventKey].AddListener<EventT>(spInst, func);
  }
};

#endif

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

  // Create a new event
  void CreateEvent(const T& rEventKey)
  {
    if (!HasEvent(rEventKey)) {

      // Constructs a new event automatically
      m_events[rEventKey];
    }
  }

  // Triggers an event determined by the key (the event must exist)
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
  bool RegisterEvent(const T& rEventKey, std::shared_ptr<EventT>& spInst, void (EventT::*func)(EventParams& args))
  {
    if (!spInst) {
      return false;
    }

    MappedEvents::iterator itResult = m_events.find(rEventKey);

    // Event should already exist
    if (itResult != m_events.end())
    {
      (*itResult).second.AddListener<EventT>(spInst, func);
      return true;
    }

    return false;
  }
};

#endif

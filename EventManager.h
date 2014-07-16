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

// An EventManager can store event keys in a specific type
template<typename T = std::string>
class EventManager
{
  typedef std::map<T, Event> MappedEvents;
  MappedEvents m_events;

  static EventManager sManagerInstance;

protected:
  EventManager(){ }

public:
  // Fetch an instance of the EventManager
  static EventManager& Get()
  {
    return sManagerInstance;
  }

  // Check that there is an event of this type registered
  bool HasEvent(const T& rEventKey) const
  {
    return m_events.find(rEventKey) != m_events.end();
  }

  // Trigger an event determined by the key (no params)
  void OnEvent(const T& rEventKey)
  {
	  EventParams no_params;
	  OnEvent(rEventKey, no_params);
  }

  // Triggers an event determined by the key
  void OnEvent(const T& rEventKey, EventParams& args)
  {
    MappedEvents::iterator itResult = m_events.find(rEventKey);

    // Checking the event exists as an early-out condition
    if (itResult != m_events.end()) {
      (*itResult).second(args);
    }
  }

  // Register a new listener based on a class instance (static or dynamic)
  template <typename EventT>
  void RegisterEvent(const T& rEventKey, EventT* spInst, void (EventT::*func)(EventParams& args))
  {
    assert(spInst);

    // Our map will automatically add a non-existent key
    m_events[rEventKey].AddListener<EventT>(spInst, func);
  }

  // Unregister a listener from all registered callbacks (optionally clear empty events)
  template <typename EventT>
  void UnregisterInstance(EventT* pInst, bool bClearOldEvents = true)
  {
	  MappedEvents::iterator it = m_events.begin();

    while( it != m_events.end() ) {
      (*it).second.RemoveListener(pInst);

      // If there are no callbacks registered, clear the event
      if( bClearOldEvents && (*it).second.Count() == 0 ) {
        it = m_events.erase(it);
      } else {
        ++it;
      }
    }
  }

};

template<typename T>
EventManager<T> EventManager<T>::sManagerInstance;

#endif

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
template<class KeyType>
class EventManager
{
  typedef typename std::map<KeyType, Event> MappedEvents;
  typedef typename MappedEvents::iterator MappedEventsIt;
  MappedEvents m_events;

public:
  // Check that there is an event of this type registered
  bool HasEvent(const KeyType& rEventKey) const
  {
    return m_events.find(rEventKey) != m_events.end();
  }

  // Trigger an event determined by the key (no params)
  void OnEvent(const KeyType& rEventKey)
  {
	  EventParams no_params;
	  OnEvent(rEventKey, no_params);
  }

  // Triggers an event determined by the key
  void OnEvent(const KeyType& rEventKey, EventParams& args)
  {
    MappedEventsIt itResult(m_events.find(rEventKey));

    // Checking the event exists as an early-out condition
    if (itResult != m_events.end()) {
      (*itResult).second(args);
    }
  }

  // Register a new listener based on a class instance (static or dynamic)
  template <class EventT>
  void RegisterEvent(const KeyType& rEventKey, EventT* spInst, void (EventT::*func)(EventParams& args))
  {
    assert(spInst);

    // Our map will automatically add a non-existent key
    m_events[rEventKey].template AddListener<EventT>(spInst, func);
  }

  // Unregister a listener from all registered callbacks (optionally clear empty events)
  template <class EventT>
  void UnregisterInstance(EventT* pInst, bool bClearOldEvents = true)
  {
	  MappedEventsIt it(m_events.begin());

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

#endif

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
  static EventManager& Get()
  {
    static EventManager sManager;
    return sManager;
  }

  bool HasEvent(const T& rEventKey) const
  {
    return m_events.find(rEventKey) != m_events.end();
  }

  void CreateEvent(const T& rEventKey)
  {
    if (HasEvent(rEventKey))
    {
      assert(false);
      return;
    }

    // constructs an event automatically
    m_events[rEventKey];
  }

  void OnEvent(const T& rEventKey, EventParams& args)
  {
    MappedEvents::iterator itResult = m_events.find(rEventKey);

    // event should already exist
    assert(itResult != m_events.end());

    if (itResult != m_events.end())
    {
      (*itResult).second(args);
    }
  }

  template <typename EventT>
  bool RegisterEvent(const T& rEventKey, EventT* pInst, void (EventT::*func)(EventParams& args))
  {
    // ensure that an instance of T has been given
    assert(pInst);

    if (!pInst)
    {
      return false;
    }

    // ensure that this event has already been created
    assert(HasEvent(rEventKey));

    // todo: create event internal, returning iterator

    MappedEvents::iterator itResult = m_events.find(rEventKey);
    // event should already exist
    assert(itResult != m_events.end());
    if (itResult != m_events.end())
    {
      (*itResult).second.AddListener<EventT>(pInst, func);
      return true;
    }

    return false;
  }
};

#endif

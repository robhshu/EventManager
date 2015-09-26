//
//  EventBase.h
//  EventBase
//
#ifndef EVENTBASE_H
#define EVENTBASE_H

#include "EventParams.h"

class EventBase
{
public:
  // Abstract call to trigger the event
  virtual void Fire(EventParams& args) = 0;
  virtual bool IsEvent(void* pInst) const = 0;
  virtual ~EventBase() {} 
};

#endif

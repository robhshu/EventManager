//
//  Event.cpp
//  EventManager
//

#include "Event.h"

void Event::operator()(EventParams& args)
{
  EventHandleVec::iterator it = m_callbackVec.begin();

  while (it != m_callbackVec.end())
  {
    (*it)->Run(args);
    ++it;
  }
}

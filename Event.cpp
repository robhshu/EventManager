//
//  Event.cpp
//  EventManager
//

#include "Event.h"

Event::~Event()
{
	EventHandleVec::iterator it = m_callbackVec.begin();

	while (it != m_callbackVec.end()) {
		delete (*it);
		++it;
	}

	m_callbackVec.clear();
}

void Event::operator()(EventParams& args)
{
  EventHandleVec::iterator it = m_callbackVec.begin();

  while (it != m_callbackVec.end()) {
    (*it)->Fire(args);
    ++it;
  }
}

void Event::RemoveListener(void* pInst)
{
	EventHandleVec::iterator it = m_callbackVec.begin();

	while (it != m_callbackVec.end())
	{
		if( (*it)->IsEvent(pInst) ) {
			delete (*it);
			it = m_callbackVec.erase(it);
		} else {
			++it;
		}
	}
}
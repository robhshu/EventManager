//
//  EventParams.cpp
//  EventManager
//

#include "EventParams.h"

bool EventParams::Find(const std::string& szParamName) const
{
  return m_params.find(szParamName) != m_params.end();
}

int EventParams::Count() const
{
  return m_params.size();
}

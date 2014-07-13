//
//  EventParams.h
//  EventManager
//
#ifndef EVENTPARAMS_H
#define EVENTPARAMS_H

#include <cassert>

#include <map>
#include <string>

class EventParams
{
  std::map<std::string, void*> m_params;

public:
  bool Find(const std::string& szParamName) const;

  int Count() const;

  template<class T>
  void Set(const std::string& szParamName, T& ptrValue)
  {
    m_params[szParamName] = (void*)ptrValue;
  }

  template<class T>
  T& Get(const std::string& szParamName)
  {
    assert(HasParam(szParamName));

    return (T&)m_params[szParamName];
  }
};

#endif

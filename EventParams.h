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
  typedef std::map<std::string, void*> MappedParams;
  MappedParams m_params;

public:
  // Check a specific parameter exists
  bool Find(const std::string& szParamName) const;

  // Count the number of parameters that exist
  int Count() const;

  // Set a parameter value
  template<class T>
  void Set(const std::string& szParamName, T& ptrValue)
  {
    assert(!HasParam(szParamName));

    if (!HasParam(szParamName)) {
      m_params[szParamName] = (void*)ptrValue;
    }
  }

  // Remove a parameter if it exists, returning the reference
  template<class T>
  bool Remove(const std::string& szParamName, T& ptrValue)
  {
    MappedParams it = m_params.find(szParamName);

    if( it = m_params.end() ) {
      return false;
    } else {
      ptrValue = (T&)m_params[szParamName];
      m_params.erase(it);
      return true;
    }
  }

  // Return the parameter value reference of known type
  template<class T>
  T& Get(const std::string& szParamName)
  {
    assert(HasParam(szParamName));

    return (T&)m_params[szParamName];
  }
};

#endif

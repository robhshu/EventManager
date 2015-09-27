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
  typedef MappedParams::iterator MappedParamsIt;
  MappedParams m_params;

public:
  // Check a specific parameter exists
  bool Find(const std::string& szParamName) const;

  // Count the number of parameters that exist
  size_t Count() const;

  // Set a parameter value
  template<class T>
  void Set(const std::string& szParamName, T& ptrValue)
  {
    m_params[szParamName] = reinterpret_cast<void*>(ptrValue);
  }

  template<class T>
  void Set(const std::string& szParamName, T* ptrValue)
  {
	  m_params[szParamName] = ptrValue;
  }

  // Remove a parameter if it exists, returning the reference
  template<class T>
  bool Remove(const std::string& szParamName, T& ptrValue)
  {
    MappedParamsIt it(m_params.find(szParamName));

    if( it = m_params.end() ) {
      return false;
    } else {
      ptrValue = reinterpret_cast<T&>(m_params[szParamName]);
      m_params.erase(it);
      return true;
    }
  }

  // Return the parameter value reference of known type
  template<class T>
  T& Get(const std::string& szParamName)
  {
    return reinterpret_cast<T&>(m_params[szParamName]);
  }

  // Return the parameter value as a pointer of known type
  template<class T>
  T* GetPtr(const std::string& szParamName)
  {
    return reinterpret_cast<T*>(m_params[szParamName]);
  }
};

#endif

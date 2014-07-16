# EventManager-Cpp

## Description

A barebone event manager written in C++, updated to use the right standard containers, and extended to support different key types


## Sample Usage

```cpp
#include "EventManager.h"

class A
{
public:
  void SomeEvent(EventParams& args)
  {
    args.Count();
  }
};

class B
  : public A
{
public:
  void SomeEvent2(EventParams& args)
  {
    args.Count();
  }
};

int main(int, char**)
{
  EventManager<> man(EventManager<>::Get());

  B bInst;

  man.RegisterEvent<B>("event1", &bInst, &B::SomeEvent);

  // trigger event with class registered
  man.OnEvent("event1");

  // unregister and trigger event (which won't fire)
  man.UnregisterInstance(&bInst);
  man.OnEvent("event1");

  // and again
  man.RegisterEvent<B>("event2", &bInst, &B::SomeEvent2);
  man.OnEvent("event2");

  return 0;
}
```

## License

This code has been placed in the public domain so you can do what you like with it

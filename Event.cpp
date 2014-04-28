#include "Event.h"
#include <iostream>

Event::Event(void)
{
}
/*-----------------------------------------------*/
Event::Event(EventType et) : type(et)
{
   
}
/*-----------------------------------------------*/
Event::Event(EventType et, std::string key, std::string value)
{
   type = et;
   strParams.emplace(make_pair(key,value));
}
/*-----------------------------------------------*/
Event::Event(EventType et, std::string key, float value)
{
   type = et;
   numParams.emplace(make_pair(key,value));
}
/*-----------------------------------------------*/
Event::~Event(void)
{
}

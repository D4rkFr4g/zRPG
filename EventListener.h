#pragma once
#include "Event.h"

class EventListener
{
public:
   
   virtual ~EventListener(void){};
   virtual void notify(Event* event) = 0;

protected:
   EventListener(void){};
};
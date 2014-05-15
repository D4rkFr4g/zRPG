#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <iostream>
#include "Event.h"
#include "EventListener.h"


class EventQueue
{
public:
   // Constructors
   EventQueue(void);
   ~EventQueue(void);

   // Functions
   void queueEvent(Event event);
   void updateEventQueue(void);
   void notifyListeners(Event* event);
   void addEventListener(Event::EventType, EventListener* listener);
   void removeEventListener(EventListener* listener);

private:
   // Variables
   std::vector<Event> eventQueue;
   std::unordered_map<Event::EventType, std::vector<EventListener*>> listeners;
};


#include "EventQueue.h"

using std::unordered_map;
using std::vector;
using std::find;
#define DEBUG_EVENT 0

/*-----------------------------------------------*/
EventQueue::EventQueue(void)
{
   /* PURPOSE:		Sets up and initializes the EventQueue 
		RECEIVES:	
		RETURNS:		
		REMARKS:    Reserves 16 spaces to start with
	*/
   
   eventQueue.reserve(16);
}
/*-----------------------------------------------*/
EventQueue::~EventQueue(void)
{
   eventQueue.clear();
   
   unordered_map<Event::EventType, std::vector<EventListener*>>::iterator itr;
   for (itr = listeners.begin(); itr != listeners.end(); itr++)
      itr->second.clear();
   listeners.erase(listeners.begin(), listeners.end());
}
/*-----------------------------------------------*/
void EventQueue::queueEvent(Event ev)
{
   /* PURPOSE:		Adds event to the queue to be processed later 
		RECEIVES:	ev - Event object to be processed
		RETURNS:		
		REMARKS:		 
	*/
   
   if (DEBUG_EVENT)
   {
      std::cout << "===============================================" << std::endl;
      std::cout << "Event Queued: " << ev.type << std::endl;
      for (auto itr = ev.strParams.begin(); itr != ev.strParams.end(); itr++)
         std::cout << itr->first << " : " << itr->second << std::endl;
      for (auto itr = ev.numParams.begin(); itr != ev.numParams.end(); itr++)
         std::cout << itr->first << " : " << itr->second << std::endl;
      std::cout << "===============================================" << std::endl << std::endl;
   }

   eventQueue.push_back(ev);
}
/*-----------------------------------------------*/
void EventQueue::updateEventQueue(void)
{
   /* PURPOSE:		Processes all queued events 
		RECEIVES:	
		RETURNS:		
		REMARKS:    First in First out
	*/

   for( int i = 0; i < (int) eventQueue.size(); i++ ) 
      notifyListeners(&eventQueue[i]);
   
   eventQueue.clear();
}
/*-----------------------------------------------*/
void EventQueue::notifyListeners(Event* ev)
{
   /* PURPOSE:		Notifies all listeners of the event type 
		RECEIVES:	ev - The event to be sent to listeners
		RETURNS:		
		REMARKS:		 
	*/

   vector<EventListener*>* vec = &listeners[ev->type];
   vector<EventListener*>::iterator itr;
   for (itr = vec->begin(); itr != vec->end(); itr++)
      (*itr)->notify(ev);
}
/*-----------------------------------------------*/
void EventQueue::addEventListener(Event::EventType eventType, EventListener* listener)
{
   /* PURPOSE:		Adds an event listener to the listener map 
		RECEIVES:	eventType - The type of event to listen for
                  listener - pointer to listener to be notified
		RETURNS:		
		REMARKS:		 
	*/

   listeners[eventType].push_back(listener);
}
/*-----------------------------------------------*/
void EventQueue::removeEventListener(EventListener* listener)
{
   /* PURPOSE:		Finds and removes all listener references
      RECEIVES:	listener - pointer to listener to be removed
      RETURNS:
      REMARKS:
      */

   unordered_map<Event::EventType, std::vector<EventListener*>>::iterator itr;
   if (listeners.size() > 0)
   {
      for (itr = listeners.begin(); itr != listeners.end(); itr++)
      {
         if (itr->second.size() > 0)
            itr->second.erase(remove(itr->second.begin(), itr->second.end()-1, listener));
      }
   }
}
/*-----------------------------------------------*/
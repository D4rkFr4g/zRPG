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
/*-----------------------------------------------*/
bool Event::checkStrParam(std::string key, std::string value)
{
   /* PURPOSE:    Safe function to lookup string parameters of the event
      RECEIVES:   key - key value to search for
                  value - value to check against
      RETURNS:    true if key value pair is found otherwise false
      REMARKS:
   */

   std::unordered_map<std::string, std::string>::iterator itr;
   std::unordered_map<std::string, std::string>::iterator end = strParams.end();
   
   itr = strParams.find(key);
   if (itr != end && itr->second == value)
      return true;
   else
      return false;
}
/*-----------------------------------------------*/
bool Event::checkNumParam(std::string key, float value)
{
   /* PURPOSE:    Safe function to lookup number parameters of the event
      RECEIVES:   key - key value to search for
                  value - value to check against
      RETURNS:    true if key value pair is found otherwise false
      REMARKS:
   */

   std::unordered_map<std::string, float>::iterator itr;
   std::unordered_map<std::string, float>::iterator end = numParams.end();

   itr = numParams.find(key);
   if (itr != end && itr->second == value)
      return true;
   else
      return false;
}
/*-----------------------------------------------*/
bool Event::checkStrKey(std::string key)
{
   /* PURPOSE:    Safe function to lookup if string parameters exists
      RECEIVES:   key - key value to search for
      RETURNS:    true if key is found otherwise false
      REMARKS:
   */
   std::unordered_map<std::string, std::string>::iterator itr;
   std::unordered_map<std::string, std::string>::iterator end = strParams.end();

   itr = strParams.find(key);
   if (itr != end)
      return true;
   else
      return false;
}
/*-----------------------------------------------*/
bool Event::checkNumKey(std::string key)
{
   /* PURPOSE:    Safe function to lookup if number parameters exists
      RECEIVES:   key - key value to search for
      RETURNS:    true if key is found otherwise false
      REMARKS:
   */
   std::unordered_map<std::string, float>::iterator itr;
   std::unordered_map<std::string, float>::iterator end = numParams.end();

   itr = numParams.find(key);
   if (itr != end)
      return true;
   else
      return false;
}
/*-----------------------------------------------*/
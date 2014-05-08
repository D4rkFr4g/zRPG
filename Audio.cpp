#include "Audio.h"
#include <iostream>

using namespace FMOD;

/*-----------------------------------------------*/
Audio::Audio()
{
}
/*-----------------------------------------------*/
Audio::Audio(System* fmodSystem, ChannelGroup* channelMusic, ChannelGroup* channelEffects)
{
   this->fmodSystem = fmodSystem;
   this->channelMusic = channelMusic;
   this->channelEffects = channelEffects;

   result = fmodSystem->createSound("Audio/Music/overworld.mp3", FMOD_DEFAULT, 0, &music["overworld"]);
   result = fmodSystem->createSound("Audio/SoundFX/link_dying.wav", FMOD_DEFAULT, 0, &soundFX["link_dying"]);
}
/*-----------------------------------------------*/
Audio::~Audio(void)
{
}
/*-----------------------------------------------*/
void Audio::notify(Event* event)
{
   /* PURPOSE: EventListener callback function
      RECEIVES: event - Event from the eventQueue
      RETURNS:
      REMARKS:
   */

   if (event->type == Event::ET_LEVEL_BEGIN)
   {
      if (event->checkStrParam("level", "overworld"))
      {
         Channel* channel;
         fmodSystem->playSound(music["overworld"], channelMusic, false, &channel);
      }
   }
   if (event->type == Event::ET_DEATH)
   {
      if (event->checkStrParam("subject", "player"))
      {
         Channel* channel;
         fmodSystem->playSound(soundFX["link_dying"], channelEffects, false, &channel);
      }
   }
}
/*-----------------------------------------------*/
void Audio::registerListeners(EventQueue* eventQueue)
{
   /* PURPOSE: Registers all relevant Audio related listeners with the eventQueue
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   eventQueue->addEventListener(Event::ET_LEVEL_BEGIN, this);
   eventQueue->addEventListener(Event::ET_DEATH, this);
}
/*-----------------------------------------------*/
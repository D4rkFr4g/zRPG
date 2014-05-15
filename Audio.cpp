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

   // Load Music
   result = fmodSystem->createStream("Audio/Music/overworld.mp3", FMOD_DEFAULT, 0, &music["overworld"]);
   result = fmodSystem->createStream("Audio/Music/title.mp3", FMOD_DEFAULT, 0, &music["title"]);
   result = fmodSystem->createStream("Audio/Music/select_screen.mp3", FMOD_DEFAULT, 0, &music["pause"]);

   // Load SoundFX
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

   if (event->type == Event::ET_TITLE_SCREEN)
   {
      stopAllMusic();
      Channel* channel;
      fmodSystem->playSound(music["title"], channelMusic, false, &channel);
   }

   if (event->type == Event::ET_LEVEL_LOAD)
   {
      if (event->checkStrParam("level", "overworld"))
      {
         stopAllMusic();
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

   if (event->type == Event::ET_PAUSED)
   {
      stopAllMusic();
      Channel* channel;
      fmodSystem->playSound(music["pause"], channelMusic, false, &channel);
   }

   if (event->type == Event::ET_LEVEL_MUSIC)
   {
      if (event->checkStrKey("level"))
      {
         std::string levelName = event->strParams.find("level")->second;

         stopAllMusic();
         Channel* channel;
         fmodSystem->playSound(music[levelName], channelMusic, false, &channel);
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

   eventQueue->addEventListener(Event::ET_LEVEL_MUSIC, this);
   eventQueue->addEventListener(Event::ET_PAUSED, this);
   eventQueue->addEventListener(Event::ET_LEVEL_LOAD, this);
   eventQueue->addEventListener(Event::ET_LEVEL_BEGIN, this);
   eventQueue->addEventListener(Event::ET_DEATH, this);
   eventQueue->addEventListener(Event::ET_TITLE_SCREEN, this);
}
/*-----------------------------------------------*/
void Audio::stopAllMusic()
{
   channelMusic->stop();
}
/*-----------------------------------------------*/
void Audio::stopAllSoundFX()
{
   channelEffects->stop();
}
/*-----------------------------------------------*/
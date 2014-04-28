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
   // Do stuff
   if (event->type == Event::ET_LEVEL_BEGIN && event->numParams.find("level")->second == 0)
   {
      Channel* channel;
      fmodSystem->playSound(music["overworld"], channelMusic, false, &channel);
   }
   if (event->type == Event::ET_DEATH && event->strParams["subject"].compare("player") == 0)
   {
      Channel* channel;
      fmodSystem->playSound(soundFX["link_dying"], channelEffects, false, &channel);
   }
}
/*-----------------------------------------------*/
void Audio::registerListeners(EventQueue* eventQueue)
{
   eventQueue->addEventListener(Event::ET_LEVEL_BEGIN, this);
   eventQueue->addEventListener(Event::ET_DEATH, this);
}
/*-----------------------------------------------*/
#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "fmod_studio.hpp"
#include "fmod_errors.h"
#include "EventListener.h"
#include "EventQueue.h"

class Audio : public EventListener
{
public:
   Audio();
   Audio(FMOD::System* fmodSystem, FMOD::ChannelGroup* channelMusic, FMOD::ChannelGroup* channelEffects);
   ~Audio(void);
   virtual void notify(Event* event) override;
   void registerListeners(EventQueue* eventQueue);
   void stopAllMusic();
   void stopAllSoundFX();
   void updateAudio();
   void quit();

   // Variables
   FMOD_RESULT result;
   FMOD::System* fmodSystem;
   FMOD::ChannelGroup* channelMusic;
   FMOD::ChannelGroup* channelEffects;
   std::unordered_map<std::string, FMOD::Sound*> music;
   std::unordered_map<std::string, FMOD::Sound*> soundFX;
   std::string currentMusic;
   FMOD::Channel* currentChannel;
   std::vector<FMOD::Channel*> channels;
   FMOD::ChannelGroup* masterGroup;
};
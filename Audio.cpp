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
   fmodSystem->getMasterChannelGroup(&masterGroup);
   masterGroup->addGroup(channelMusic);
   masterGroup->addGroup(channelEffects);

   std::vector<std::string> musicNames;
   musicNames.reserve(20);

   musicNames.push_back("overworld");
   musicNames.push_back("title");
   musicNames.push_back("pause");
   musicNames.push_back("dungeon");
   musicNames.push_back("battle");
   musicNames.push_back("battle_ganon");
   musicNames.push_back("boss_clear_fanfare");
   musicNames.push_back("ending");
   musicNames.push_back("princess_zeldas_rescue");

   std::vector<std::string> soundNames;
   soundNames.reserve(20);

   soundNames.push_back("boss_hit");
   soundNames.push_back("boss_kill");
   soundNames.push_back("chest_open");
   soundNames.push_back("enemy_hit");
   soundNames.push_back("enemy_kill");
   soundNames.push_back("error");
   soundNames.push_back("grass_walk");
   soundNames.push_back("item");
   soundNames.push_back("item_fanfare");
   soundNames.push_back("link_dash");
   soundNames.push_back("link_dying");
   soundNames.push_back("link_fall");
   soundNames.push_back("link_hurt");
   soundNames.push_back("link_jump");
   soundNames.push_back("link_land");
   soundNames.push_back("link_pickup");
   soundNames.push_back("link_push");
   soundNames.push_back("link_shock");
   soundNames.push_back("link_shock_fast");
   soundNames.push_back("link_throw");
   soundNames.push_back("low_health");
   soundNames.push_back("menu_cursor");
   soundNames.push_back("menu_select");
   soundNames.push_back("menu_back");
   soundNames.push_back("quit");
   soundNames.push_back("refill_health");
   soundNames.push_back("rupee");
   soundNames.push_back("rupee_register");
   soundNames.push_back("secret");
   soundNames.push_back("shield");
   soundNames.push_back("sword");
   soundNames.push_back("sword_spin");
   soundNames.push_back("cucco");
   soundNames.push_back("cucco_hit");
   soundNames.push_back("enemy_skitter");
   soundNames.push_back("ganon_crash");
   soundNames.push_back("deflect");
   soundNames.push_back("magic");
   

   // Load Music
   for (int i = 0; i < (int)musicNames.size(); i++)
   {

      std::string name = musicNames[i];
      std::string filename = "Audio/Music/" + name + ".mp3";
      result = fmodSystem->createStream(filename.c_str(), FMOD_DEFAULT, 0, &(music[name]));
   }

   // Load SoundFX
   for (int i = 0; i < (int)soundNames.size(); i++)
   {
      std::string name = soundNames[i];
      std::string filename = "Audio/SoundFX/" + name + ".wav";
      result = fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &soundFX[name]);
   }
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
      //Channel* channel;
      fmodSystem->playSound(music["title"], channelMusic, false, &currentChannel);
   }

   if (event->type == Event::ET_LEVEL_LOAD)
   {
      if (event->checkStrParam("level", "overworld"))
      {
         stopAllMusic();
         currentMusic = "overworld";
         fmodSystem->playSound(music["overworld"], channelMusic, false, &currentChannel);
         currentChannel->setChannelGroup(channelMusic);
      }
      else if (event->checkStrParam("level", "dungeon_1"))
      {
         stopAllMusic();
         currentMusic = "dungeon";
         fmodSystem->playSound(music[currentMusic], channelMusic, false, &currentChannel);
         currentChannel->setChannelGroup(channelMusic);
      }
      else if (event->checkStrParam("level", "battle_easy") ||
         event->checkStrParam("level", "battle_medium") ||
         event->checkStrParam("level", "battle_hard"))
      {
         stopAllMusic();
         currentMusic = "battle";
         fmodSystem->playSound(music[currentMusic], channelMusic, false, &currentChannel);
         currentChannel->setChannelGroup(channelMusic);
      }
   }
   if (event->type == Event::ET_DEATH)
   {
      if (event->checkStrParam("subject", "Link"))
      {
         Channel* channel;
         fmodSystem->playSound(soundFX["link_dying"], channelEffects, false, &channel);
      }
      else if (event->checkStrParam("subject", "Ganon"))
      {
         Channel* channel;
         fmodSystem->playSound(soundFX["boss_kill"], channelEffects, false, &channel);
      }
      else
      {
         Channel* channel;
         fmodSystem->playSound(soundFX["enemy_kill"], channelEffects, false, &channel);
      }
   }

   if (event->type == Event::ET_PAUSED)
   {
      stopAllMusic();
      Channel* channel;
      fmodSystem->playSound(music["pause"], channelMusic, false, &channel);
      channel->setChannelGroup(channelMusic);
   }

   if (event->type == Event::ET_LEVEL_MUSIC)
   {
      if (event->checkStrKey("level"))
      {
         std::string levelName = event->strParams.find("level")->second;

         stopAllMusic();
         Channel* channel;
         fmodSystem->playSound(music[levelName], channelMusic, false, &channel);
         channel->setChannelGroup(channelMusic);
      }
   }

   if (event->type == Event::ET_BATTLE_WIN)
   {
      stopAllMusic();
      Channel* channel;
      fmodSystem->playSound(music["boss_clear_fanfare"], channelMusic, false, &channel);
      channel->setChannelGroup(channelMusic);
   }

   if (event->type == Event::ET_DAMAGE)
   {
      if (event->checkStrKey("name"))
      {
         std::string name = event->strParams.find("name")->second;

         Channel* channel;
         std::string sound = "";

         if (name.compare("link") == 0)
            sound = "link_hurt";
         else if (name.compare("guard") == 0 || name.compare("knight") == 0)
            sound = "enemy_hit";
         else if (name.compare("cucco") == 0)
            sound = "cucco_hit";
         else if (name.compare("Ganon") == 0)
            sound = "boss_hit";

         fmodSystem->playSound(soundFX[sound], channelEffects, false, &channel);
      }
   }

   if (event->type == Event::ET_ATTACK)
   {
      if (event->checkStrKey("name"))
      {
         std::string name = event->strParams.find("name")->second;

         Channel* channel;
         std::string sound = "";

         if (name.compare("Link") == 0)
            sound = "sword";
         else if (name.compare("guard") == 0 || name.compare("knight") == 0)
            sound = "enemy_skitter";
         else if (name.compare("cucco") == 0)
            sound = "cucco";
         else if (name.compare("Ganon") == 0)
            sound = "ganon_crash";

         fmodSystem->playSound(soundFX[sound], channelEffects, false, &channel);
      }
   }

   if (event->type == Event::ET_SOUND)
   {
      if (event->checkStrKey("soundFX"))
      {
         std::string name = event->strParams.find("soundFX")->second;
         Channel* channel;
         fmodSystem->playSound(soundFX[name], channelEffects, false, &channel);
      }
      else if (event->checkStrKey("music"))
      {
         stopAllMusic();
         std::string name = event->strParams.find("music")->second;
         Channel* channel;
         fmodSystem->playSound(music[name], channelMusic, false, &channel);
      }
   }

   if (event->type == Event::ET_ITEM)
   {
      Channel* channel;
      fmodSystem->playSound(soundFX["item_fanfare"], channelEffects, false, &channel);
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
   eventQueue->addEventListener(Event::ET_SOUND, this);
   eventQueue->addEventListener(Event::ET_DAMAGE, this);
   eventQueue->addEventListener(Event::ET_ATTACK, this);
   eventQueue->addEventListener(Event::ET_BATTLE_WIN, this);
   eventQueue->addEventListener(Event::ET_ITEM, this);
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
void Audio::updateAudio()
{
   if (currentMusic.compare("overworld") == 0)
   {
      bool isPlaying;
      channelMusic->isPlaying(&isPlaying);
      if (!isPlaying)
      {
         fmodSystem->playSound(music["overworld"], channelMusic, false, &currentChannel);
         currentChannel->setChannelGroup(channelMusic);
         currentChannel->setPosition(6980, FMOD_TIMEUNIT_MS);
      }
   }
   //channel->setPosition(7034, FMOD_TIMEUNIT_MS);
   //channelMusic->;
}
/*-----------------------------------------------*/
void Audio::quit()
{
   channelMusic->release();
   channelEffects->release();

   fmodSystem->close();
   fmodSystem->release();
}
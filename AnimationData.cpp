#include "AnimationData.h"

AnimationData::AnimationData(void)
{
}
/*-----------------------------------------------*/
AnimationData::AnimationData(Animation def, int timeToNextFrame, bool isRepeating)
{
	this->def = def;
	this->timeToNextFrame = timeToNextFrame;
	this->elapsedTime = 0;
	this->currentFrame = 0;
	this->isRepeating = isRepeating;
   this->eventFrame = 0;
   this->isFinished = false;
}
/*-----------------------------------------------*/
AnimationData::~AnimationData(void)
{
}
/*-----------------------------------------------*/
void AnimationData::resetElapsedTime()
{
	/* PURPOSE:		Reset the elapsed time counter 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		 
	*/

	elapsedTime = 0;
}
/*-----------------------------------------------*/
void AnimationData::updateTime(int ms)
{
	/* PURPOSE:		Update counters used for animation timing 
		RECEIVES:	ms - time in milliseconds since last frame 
		RETURNS:		 
		REMARKS:		 
	*/

	elapsedTime += ms;

 	if (elapsedTime > timeToNextFrame)
	{
		resetElapsedTime();
		advanceFrame();
	}
}
/*-----------------------------------------------*/
void AnimationData::advanceFrame()
{
   /* PURPOSE:		Updates current frame of animation
      RECEIVES:
      RETURNS:
      REMARKS:		Resets to 0 if isRepeating == true otherwise stops at last frame

      */

   if (!isFinished)
   {
      currentFrame++;
      if (currentFrame >= def.numFrames)
      {
         if (isRepeating)
            currentFrame = 0;
         else
         {
            currentFrame = def.numFrames - 1;
            isFinished = true;
         }
      }
   }
}
/*-----------------------------------------------*/
bool AnimationData::timeToSendEvent()
{
   /* PURPOSE:		Checks whether it is time to send Event
      RECEIVES:
      RETURNS:    true if it is ok to send event otherwise false
      REMARKS:		Default is 0 unless set beforehand
   */

   return (currentFrame == eventFrame);
}
/*-----------------------------------------------*/
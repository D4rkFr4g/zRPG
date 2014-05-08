#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <SDL.h>
#include "DialogBox.h"
#include "Font.h"
#include "EventQueue.h"
#include "EventListener.h"


class DialogManager : public EventListener
{
protected:

private:
   // Functions
   void loadDialogQueue(std::vector<DialogBox> dialogSequence);
   void center(int* x, int* y, int rows, int cols);
   void centerX(int* x, int rows, int cols);
   void centerY(int* y, int rows, int cols);

public:
   DialogManager();
   ~DialogManager();

   // Functions
   void initDialogs();
   void dialogKeyboard(const unsigned char* kbState, unsigned char* kbPrevState);
   virtual void notify(Event* event) override;
   void registerListeners(EventQueue* eventQueue);

   // Variables
   static int* screenWidth;
   static int* screenHeight;
   static std::vector<DialogBox>* dialogQueue;
   std::unordered_map<std::string, std::vector<DialogBox>> dialogs;   
};


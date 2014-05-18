#include "DialogManager.h"


std::vector<DialogContainer>* DialogManager::dialogQueue;
int* DialogManager::screenWidth;
int* DialogManager::screenHeight;
EventQueue* DialogManager::eventQueue;

/*-----------------------------------------------*/
DialogManager::DialogManager()
{
}
/*-----------------------------------------------*/
DialogManager::~DialogManager()
{
}
/*-----------------------------------------------*/
void DialogManager::initDialogs()
{
   /* PURPOSE:		Loads all the dialog to be used in the game
   RECEIVES:
   RETURNS:
   REMARKS:
   */

   int stdCols = (int)floor(*screenWidth / DialogContainer::texture->cellWidth);
   int stdRows = 12;
   int cols = stdCols;
   int rows = stdRows;
   int stdX = 0;
   int stdY = *screenHeight - (rows * DialogContainer::texture->cellHeight);
   int x = stdX;
   int y = stdY;

   DialogContainer dBox;
   std::vector<DialogContainer> dBoxes;

   /*============================================================================*/
   std::string text = "In a stunning turn of original events, the Princess Zelda of Hyrule has been captured by a Dark Lord (surprising, I know).";
   text += "\nLink must set out on a quest to rescue the Princess from the evil clutches of this vile enemy to restore…";

   dBox = DialogContainer(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);

   text = "the Princess to her throne, thereby saving the land of Hyrule once again.";
   text += " Shall Link restore balance to the peaceful land of Hyrule as a fierce warrior with a vengeance?";
   text += " Or shall he burn his foes to a crisp as a fireball - slinging mage?";
   text += " The playstyle…";

   dBox = DialogContainer(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);

   text = "is up to you to decide. But it is a given that this quest will not be an easy one…";
   dBox = DialogContainer(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);

   dialogs["intro"] = dBoxes;
   /*============================================================================*/
   dBoxes.clear();

   sizeDialogBox(&rows, &cols, 2, "\bRETURN OF GANON");
   center(&x, &y, rows, cols);

   text = "\t\bGAME OVER \n\bRETURN OF GANON";

   dBox = DialogContainer(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);

   dialogs["death"] = dBoxes;
   /*============================================================================*/

   dBoxes.clear();
   sizeDialogBox(&rows, &cols, 1, "Paused");
   center(&x, &y, rows, cols);

   text = "\b\bPaused";
   
   dBox = DialogContainer(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);
   dialogs["pause"] = dBoxes;
   /*============================================================================*/
   
   dBoxes.clear();
   text = "It's Dangerous to Go alone!";
   sizeDialogBox(&rows, &cols, 1, text);
   center(&x, &y, rows, cols);

   dBox = DialogContainer(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);
   dialogs["guard_dangerous"] = dBoxes;
   /*============================================================================*/

   dBoxes.clear();
   text = "Are you sure your strong enough yet?       ";
   sizeDialogBox(&rows, &cols, 2, text);
   center(&x, &y, rows, cols);

   text += "\nDon't come crying to me if you get hurt!";

   dBox = DialogContainer(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);
   dialogs["guard_weak"] = dBoxes;
   /*============================================================================*/
   
   dBoxes.clear();
   text = "You have found the Master Sword!";
   sizeDialogBox(&rows, &cols, 1, text);
   center(&x, &y, rows, cols);

   dBox = DialogContainer(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);
   dialogs["chest_sword"] = dBoxes;
   /*============================================================================*/

   //dialogQueue->push_back(DialogContainer(x, y, rows, cols, "abcdedfghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ\n!\"~$&'(),-.^…0123456789:;<=>?@", true, false));

   /*dBoxes.clear();
   rows = stdRows;
   cols = stdCols;
   x = stdX;
   y = stdY;

   text = "";
   text += "";

   dBox = DialogContainer(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);

   dialogs[""] = dBoxes;*/
}
/*-----------------------------------------------*/
void DialogManager::dialogKeyboard(const unsigned char* kbState, unsigned char* kbPrevState)
{
   /* PURPOSE:		Process keyboard commands as they relate to dialog boxes
   RECEIVES:	kbState - current state of the keyboard
   kbPrevState - Previous frame state of the keyboard
   RETURNS:
   REMARKS:
   */

   static bool isPaused = false;

   // Pause DialogContainer
   if (kbState[SDL_SCANCODE_P] && !kbPrevState[SDL_SCANCODE_P])
   {
      if (!isPaused)
      {
         loadDialogQueue(dialogs["pause"], true);
         isPaused = true;
         eventQueue->queueEvent(Event(Event::ET_PAUSED));
      }
      else
      {
         eventQueue->queueEvent(Event(Event::ET_LEVEL_MUSIC));
         dialogQueue->pop_back();
         isPaused = false;
      }
   }

   /*if (kbState[SDL_SCANCODE_0] && !kbPrevState[SDL_SCANCODE_0])
   {
   loadDialogQueue(dialogs["intro"]);
   }*/

   // Handle clickable dialog boxes
   if (kbState[SDL_SCANCODE_J] && !kbPrevState[SDL_SCANCODE_J] && !isPaused)
   {
      if (dialogQueue->size() > 0 && dialogQueue->back().isInputNeeded == true)
         dialogQueue->pop_back();
   }
}
/*-----------------------------------------------*/
void DialogManager::center(int* x, int* y, int rows, int cols)
{
   /* PURPOSE:		calculates x and y coordinate to center dialog box on screen
   RECEIVES:   x - x screen coordinate
   y - y screen coordinate
   rows - number of Rows in DialogContainer
   cols - number of columns in DialogContainer
   RETURNS:
   REMARKS:
   */

   int cellWidth = DialogContainer::texture->cellWidth;
   int cellHeight = DialogContainer::texture->cellHeight;

   int screenCenterX = (int)floor(*screenWidth / 2.0);
   int screenCenterY = (int)floor(*screenHeight / 2.0);

   int halfTexWidth = (int)floor((cols * cellWidth) / 2.0);
   int halfTexHeight = (int)floor((rows * cellHeight) / 2.0);

   *x = screenCenterX - halfTexWidth;
   *y = screenCenterY - halfTexHeight;
}
/*-----------------------------------------------*/
void DialogManager::centerX(int* x, int rows, int cols)
{
   /* PURPOSE:		calculates x coordinate to center dialog box on screen
   RECEIVES:   x - x screen coordinate
   y - y screen coordinate
   rows - number of Rows in DialogContainer
   cols - number of columns in DialogContainer

   RETURNS:
   REMARKS:
   */

   int y = 0;
   center(x, &y, rows, cols);
}
/*-----------------------------------------------*/
void DialogManager::centerY(int* y, int rows, int cols)
{
   /* PURPOSE:		calculates y coordinate to center dialog box on screen
   RECEIVES:   x - x screen coordinate
   y - y screen coordinate
   rows - number of Rows in DialogContainer
   cols - number of columns in DialogContainer

   RETURNS:
   REMARKS:
   */

   int x = 0;
   center(&x, y, rows, cols);
}
/*-----------------------------------------------*/
void DialogManager::loadDialogQueue(std::vector<DialogContainer> dialogSequence, bool reverse)
{
   /* PURPOSE:		Loads dialogSequence into the dialogQueue
   RECEIVES:   dialogSequence - a vector of dialog boxes
   RETURNS:
   REMARKS:    Loads the sequence backwards
   */

   if (reverse)
   {
      for (int i = dialogSequence.size() - 1; i >= 0; i--)
      {
         dialogQueue->push_back(dialogSequence[i]);
      }
   }
   else
   {
      for (int i = 0; i < dialogSequence.size(); i++)
      {
         dialogQueue->push_back(dialogSequence[i]);
      }
   }
}
/*-----------------------------------------------*/
void DialogManager::sizeDialogBox(int* rows, int* cols, int linesOfText, std::string maxRowOfText)
{
   /* PURPOSE:    Sets the row and col sizes needed for the given input
   RECEIVES:   rows - number of rows in the dialog box to be set
   cols - number of cols in the dialog box to be set
   linesOfText - number of lines needed for all text in dialog box
   maxRowOfText - One line of text that will be the widest line in dialog box
   RETURNS:
   REMARKS:
   */

   int rowOffset = 2;
   int colOffset = 5;

   *cols = (int)(floor(Font::stringWidth(maxRowOfText) / DialogContainer::texture->cellWidth) + colOffset);
   *rows = (int)(floor(((Font::maxFontHeight + Font::padding) * linesOfText) / DialogContainer::texture->cellHeight) + rowOffset);
}
/*-----------------------------------------------*/
void DialogManager::notify(Event* event)
{
   /* PURPOSE: EventListener callback function
   RECEIVES: event - Event from the eventQueue
   RETURNS:
   REMARKS:
   */

   if (event->type == Event::ET_LEVEL_LOAD)
   {
      if (event->checkStrParam("level", "overworld") && event->checkStrParam("newGame", "true"))
         loadDialogQueue(dialogs["intro"], true);
   }

   if (event->type == Event::ET_DEATH)
      loadDialogQueue(dialogs["death"], true);
   if (event->type == Event::ET_RESTART)
      dialogQueue->clear();
   if (event->type == Event::ET_COLLISION_START)
   {
      int x = 0;
      int y = 0;
      int padding = 10;

      if (event->checkNumKey("x"))
         x = event->numParams.find("x")->second;
      
      if (event->checkNumKey("y"))
         y = event->numParams.find("x")->second;

      if (event->checkStrKey("dialog"))
      {
         std::string dialog = event->strParams.find("dialog")->second;

         std::vector<DialogContainer> dBoxes = dialogs[dialog];

         // Set dialog box over position
         for (int i = 0; i < (int)dBoxes.size(); i++)
         {
            dBoxes[i].x = x - (int)floor(dBoxes[i].width / 2);
            dBoxes[i].y = y - dBoxes[i].height - padding;
         }
         loadDialogQueue(dBoxes, true);
      }
      else if (event->checkStrKey("name"))
      {
         std::string name = event->strParams.find("name")->second;

         if (name.compare("Steve") == 0)
         {
            std::vector<DialogContainer> dBoxes = dialogs["guard_dangerous"];
            
            // Set dialog box over position
            for (int i = 0; i < (int)dBoxes.size(); i++)
            {
               dBoxes[i].x = x - (int) floor(dBoxes[i].width / 2);
               dBoxes[i].y = y - dBoxes[i].height - padding;
            }
            loadDialogQueue(dBoxes, true);
         }
      }
   }

   if (event->type == Event::ET_ITEM)
   {
      if (event->checkStrKey("name"))
      {
         std::string name = event->strParams.find("name")->second;

         std::unordered_map<std::string, std::vector<DialogContainer>>::iterator itr = dialogs.find(name);
         std::unordered_map<std::string, std::vector<DialogContainer>>::iterator end = dialogs.end();

         if (itr != end)
            loadDialogQueue(dialogs[name], true);
      }
   }
}
/*-----------------------------------------------*/
void DialogManager::registerListeners(EventQueue* eventQueue)
{
   /* PURPOSE: Registers all relevant Dialog related listeners with the eventQueue
   RECEIVES:
   RETURNS:
   REMARKS:
   */

   eventQueue->addEventListener(Event::ET_LEVEL_BEGIN, this);
   eventQueue->addEventListener(Event::ET_DEATH, this);
   eventQueue->addEventListener(Event::ET_RESTART, this);
   eventQueue->addEventListener(Event::ET_COLLISION_START, this);
}
/*-----------------------------------------------*/
void DialogManager::initBattleDialog(std::vector<BattleSprite*>* battleSprites)
{
   /* PURPOSE:    Initializes all menus for Battle
   RECEIVES:   battleSprites - all sprites involved in battle
   RETURNS:
   REMARKS:
   */

   battlePlayer = (*battleSprites)[0];
   for (int i = 1; i < (int)battleSprites->size(); i++)
      this->enemies.push_back((*battleSprites)[i]);

   // Setup player strings
   playerStrings["name"] = battlePlayer->name;
   playerStrings["health"] = "" + battlePlayer->health;
   playerStrings["maxHealth"] = "" + battlePlayer->maxHealth;
   playerStrings["magic"] = "" + battlePlayer->magic;

   // Setup Action strings
   actionStrings.push_back("Fight");
   actionStrings.push_back("Defend");
   actionStrings.push_back("Items");
   actionStrings.push_back("Flee");

   // Setup enemy strings
   enemyStrings.reserve(3);
   for (int i = 0; i < (int)enemies.size(); i++)
      enemyStrings.push_back(enemies[i]->name);

   // Setup item strings
   std::unordered_map<std::string, int>::iterator itr = battlePlayer->items.begin();
   std::unordered_map<std::string, int>::iterator end = battlePlayer->items.end();
   for (itr; itr != end; itr++)
   {
      std::string qty = " " + itr->second;
      itemStrings.push_back(itr->first + " x" + qty);
   }

   // Setup dialogBoxes
   battleBoxes["player"] = DialogContainer(192, 320, 10, 28, "", true, true);
   battleBoxes["action"] = DialogContainer(150, 320, 10, 12, "", true, true);
   battleBoxes["enemy"] = DialogContainer(0, 320, 10, 12, "", true, true);
   battleBoxes["item"] = DialogContainer(192, 320, 10, 28, "", true, true);
   playerText = &battleBoxes["player"].text;
   actionText = &battleBoxes["action"].text;
   enemyText = &battleBoxes["enemy"].text;
   itemText = &battleBoxes["item"].text;

   dialogQueue->push_back(battleBoxes["player"]);
   dialogQueue->push_back(battleBoxes["enemy"]);
}
/*-----------------------------------------------*/
void DialogManager::updateBattleDialog(BattleMenu battleMenu)
{
   /* PURPOSE:    Updates Battle dialogs based on user input
   RECEIVES:   input - keyboard command issued by user
   RETURNS:
   REMARKS:
   */
   dialogQueue->clear();

   // Setup player box
   // Format:   \t> Link \t\t100 / 100 \t\t10
   *playerText = "";

   playerStrings["name"] = battlePlayer->name;
   playerStrings["health"] = std::to_string(battlePlayer->health);
   playerStrings["maxHealth"] = std::to_string(battlePlayer->maxHealth);
   playerStrings["magic"] = std::to_string(battlePlayer->magic);

   if (battleMenu.isActive("player"))
      *playerText += "\t> ";
   else
      *playerText += "\t";

   *playerText += playerStrings["name"] + "\t\t" + playerStrings["health"] +
      "\b/\b" + playerStrings["maxHealth"] + "\t\t" + playerStrings["magic"];

   battleBoxes["player"].loadFontSprites();
   dialogQueue->push_back(battleBoxes["player"]);

   // Setup enemy box
   
   // Check for killed enemies
   for (int i = 0; i < (int)enemies.size(); i++)
   {
      if (enemies[i]->isRemovable)
         enemies.erase(remove(enemies.begin(), enemies.end(), enemies[i]));
   }

   *enemyText = "";

   enemyStrings.clear();
   for (int i = 0; i < (int)enemies.size(); i++)
      enemyStrings.push_back(enemies[i]->name);

   int selection = battleMenu.getSelectedEnemy();
   if (battleMenu.isActive("enemy"))
   {
      enemyStrings[selection] = "> " + enemyStrings[selection];
   }

   for (int i = 0; i < (int)enemyStrings.size(); i++)
   {
      if (!battleMenu.isActive("enemy") || i != selection)
         *enemyText += "\t";
      *enemyText += enemyStrings[i] + "\n";
   }

   battleBoxes["enemy"].loadFontSprites();
   dialogQueue->push_back(battleBoxes["enemy"]);

   // Setup Enemy Highlights
   if (battleMenu.isActive("enemy"))
   {
      BattleSprite* enemy = enemies[battleMenu.getSelectedEnemy()];

      int rows = 2;
      int cols = 5;
      int xOffset = DialogContainer::texture->cellWidth * (cols - 1);
      int yOffset = DialogContainer::texture->cellHeight * (rows - 1);
      int x = enemy->x + enemy->width - xOffset;
      int y = enemy->y - yOffset;

       dialogQueue->push_back(DialogContainer(x, y, rows, cols, "^", false , false));
   }

   // Setup action box
   if (battleMenu.isActive("action"))
   {
      *actionText = "";
      actionStrings.clear();
      actionStrings.push_back("Fight");
      actionStrings.push_back("Defend");
      actionStrings.push_back("Items");
      actionStrings.push_back("Flee");

      int selection = battleMenu.getSelectedAction();
      actionStrings[selection] = "> " + actionStrings[selection];

      for (int i = 0; i < (int)actionStrings.size(); i++)
      {
         if (i != selection)
            *actionText += "\t";
         *actionText += actionStrings[i] + "\n";
      }

      battleBoxes["action"].loadFontSprites();
      dialogQueue->push_back(battleBoxes["action"]);
   }

   // Setup item box
   // Setup item strings
   if (battleMenu.isActive("item"))
   {
      *itemText = "";
      itemStrings.clear();
      std::unordered_map<std::string, int>::iterator itr = battlePlayer->items.begin();
      std::unordered_map<std::string, int>::iterator end = battlePlayer->items.end();
      for (itr; itr != end; itr++)
         itemStrings.push_back(itr->first + " x" + std::to_string(itr->second));

      int selection = battleMenu.getSelectedItem();
      itemStrings[selection] = "> " + itemStrings[selection];

      for (int i = 0; i < (int)itemStrings.size(); i += 2)
      {
         if (i != selection)
            *itemText += "\b\b";

         *itemText += itemStrings[i] + "\t\t";

         bool isSecond = i + 1 < (int)itemStrings.size();
         if (isSecond && i + 1 != selection)
            *itemText += "\b\b";

         if (isSecond)
            *itemText += itemStrings[i + 1] + "\n";
      }

      battleBoxes["item"].loadFontSprites();
      dialogQueue->push_back(battleBoxes["item"]);
   }
}
/*-----------------------------------------------*/
void DialogManager::battleRewards(std::vector<std::string> loot)
{
   /* PURPOSE:    Displays all rewards from the battle through dialogboxes
   RECEIVES:   loot - a list of all the rewards to be displayed
   RETURNS:
   REMARKS:
   */

   battleResetDialog();
   
   int x = 0;
   int y = 0;
   int rows = 0;
   int cols = 0;

   sizeDialogBox(&rows, &cols, 1, "Found Green Potion x10000");
   center(&x, &y, rows, cols);
   std::string text = "";
   std::vector<DialogContainer> dBoxes;

   for (int i = 0; i < (int)loot.size(); i++)
   {
      text = loot[i];
      dBoxes.push_back(DialogContainer(x, y, rows, cols, text, true, true));
   }

   loadDialogQueue(dBoxes, false);
}
/*-----------------------------------------------*/
void DialogManager::battleCleanup()
{
   /* PURPOSE:    Reset all data used in battle to ready for next
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   actionStrings.clear();
   enemyStrings.clear();
   itemStrings.clear();
   enemies.clear();
   dialogQueue->clear();
}
/*-----------------------------------------------*/
void DialogManager::battleResetDialog()
{
   if (dialogQueue->size() > 2)
      dialogQueue->pop_back();
}

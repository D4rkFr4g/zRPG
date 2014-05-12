#pragma once
#include <string>
#include <rpc.h>

class uuidManager
{
protected:
   uuidManager();

public:
   ~uuidManager();

   // Functions
   static std::string newUUID();

};


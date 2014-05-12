#include "uuidManager.h"


uuidManager::uuidManager()
{
}


uuidManager::~uuidManager()
{
}

std::string uuidManager::newUUID()
{
   /* PURPOSE: Creates a unique id
      RECEIVES:
      RETURNS: string that is unique
      REMARKS:
   */

   UUID uuid;
   UuidCreate(&uuid);

   unsigned char * str;
   UuidToStringA(&uuid, &str);

   std::string s((char*)str);

   RpcStringFreeA(&str);

   return s;
}

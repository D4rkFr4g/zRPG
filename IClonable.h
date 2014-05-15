#pragma once


class IClonable
{
public:
   virtual ~IClonable(){};

   // Functions
   virtual IClonable* clone() const = 0;
};


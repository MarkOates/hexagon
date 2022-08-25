#pragma once


#include <string>


namespace Hexagon
{
   namespace Daemus
   {
      namespace Builds
      {
         class Base
         {
         private:
            std::string type;
            std::string status;

         public:
            Base(std::string type="Base");
            virtual ~Base();

            std::string get_type() const;
            std::string get_status() const;
            virtual void initiate();
         };
      }
   }
}




#pragma once


#include <Hexagon/Action.hpp>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class SendMessageToDaemusToBuild : public ::Action
         {
         private:

         protected:


         public:
            SendMessageToDaemusToBuild();
            virtual ~SendMessageToDaemusToBuild();

            virtual bool execute() override;
         };
      }
   }
}




#pragma once


#include <Hexagon/StageInterface.hpp>
#include <string>


namespace Hexagon
{
   class RerunOutputWatcher : public StageInterface
   {
   private:

   public:
      RerunOutputWatcher();
      ~RerunOutputWatcher();


   std::string run();
   };
}




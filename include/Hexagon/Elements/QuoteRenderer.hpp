#pragma once


#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class QuoteRenderer
      {
      private:
         std::string quote;

      public:
         QuoteRenderer();
         ~QuoteRenderer();


      void render();
      };
   }
}




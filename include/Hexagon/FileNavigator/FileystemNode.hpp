#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace FileNavigator
   {
      class FileystemNode
      {
      private:
         ALLEGRO_FS_ENTRY* entry;

      public:
         FileystemNode(ALLEGRO_FS_ENTRY* entry=nullptr);
         ~FileystemNode();


      std::string run();
      };
   }
}




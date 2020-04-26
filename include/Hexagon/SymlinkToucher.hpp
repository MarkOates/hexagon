#pragma once


#include <string>


namespace Hexagon
{
   class SymlinkToucher
   {
   private:
      std::string filename;

   public:
      SymlinkToucher(std::string filename="file.txt");
      ~SymlinkToucher();


   void touch_if_symlink();
   };
}




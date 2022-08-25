#pragma once


#include <string>


namespace Hexagon
{
   class Marker
   {
   private:
      std::string filename;
      int line_num;

   public:
      Marker();
      ~Marker();

      std::string get_filename() const;
      int get_line_num() const;
   };
}




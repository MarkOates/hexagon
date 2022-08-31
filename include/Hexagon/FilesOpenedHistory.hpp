#pragma once


#include <string>
#include <vector>


namespace Hexagon
{
   class FilesOpenedHistory
   {
   private:
      std::vector<std::string> files;

   protected:


   public:
      FilesOpenedHistory(std::vector<std::string> files={});
      ~FilesOpenedHistory();

      std::vector<std::string> get_files() const;
      std::string run();
   };
}




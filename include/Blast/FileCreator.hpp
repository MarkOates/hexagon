#pragma once


#include <string>


namespace Blast
{
   class FileCreator
   {
   private:
      std::string filename;
      std::string initial_content;

   protected:


   public:
      FileCreator(std::string filename="undefined_file.txt", std::string initial_content="");
      ~FileCreator();

      void create_if_not_exists();
      void create_or_overwrite();
   };
}




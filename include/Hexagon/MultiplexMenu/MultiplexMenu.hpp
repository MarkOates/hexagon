#pragma once


#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class MultiplexMenu
      {
      private:
         std::vector<std::tuple<std::string, std::string, std::string, std::string>> items;

      public:
         MultiplexMenu(std::vector<std::tuple<std::string, std::string, std::string, std::string>> items={});
         ~MultiplexMenu();

         std::vector<std::tuple<std::string, std::string, std::string, std::string>> &get_items_ref();
      };
   }
}




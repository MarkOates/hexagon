#pragma once


#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace BuildStageRenderers
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"Base";

         private:
            std::string type;

         protected:


         public:
            Base(std::string type=TYPE);
            virtual ~Base();

            std::string get_type() const;
            bool is_type(std::string possible_type="");
            virtual std::string render_text();
         };
      }
   }
}




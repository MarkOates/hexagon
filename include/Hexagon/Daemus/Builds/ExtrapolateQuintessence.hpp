#pragma once


#include <Hexagon/Daemus/Builds/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace Daemus
   {
      namespace Builds
      {
         class ExtrapolateQuintessence : public Hexagon::Daemus::Builds::Base
         {
         private:
            std::string BUILDS_PENDING_FOLDER_LOCATION;

         public:
            ExtrapolateQuintessence();
            virtual ~ExtrapolateQuintessence();

            void set_BUILDS_PENDING_FOLDER_LOCATION(std::string BUILDS_PENDING_FOLDER_LOCATION);
            std::string get_BUILDS_PENDING_FOLDER_LOCATION();
            virtual void initiate() override;
            void write_build_file();
            void poll_for_progress();
            std::string generate_build_file_contents();
            std::string generate_build_filename();
            static std::string generate_time_now_string();
         };
      }
   }
}




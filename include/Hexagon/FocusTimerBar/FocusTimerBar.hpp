#pragma once


#include <ctime>


namespace Hexagon
{
   namespace FocusTimerBar
   {
      class FocusTimerBar
      {
      private:
         std::time_t focus_timer_started_at;
         float focus_timer_duration_sec;
         float warning_position_sec;

      protected:


      public:
         FocusTimerBar();
         ~FocusTimerBar();

         std::time_t get_focus_timer_started_at() const;
         float get_focus_timer_duration_sec() const;
         float get_warning_position_sec() const;
      };
   }
}




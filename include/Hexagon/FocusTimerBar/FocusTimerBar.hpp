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

      public:
         FocusTimerBar();
         ~FocusTimerBar();


         std::time_t get_focus_timer_started_at();
         float get_focus_timer_duration_sec();
      };
   }
}




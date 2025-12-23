#pragma once


#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>
#include <ctime>


namespace Hexagon
{
   namespace FocusTimerBar
   {
      class FocusTimerBar
      {
      public:

         enum Activity
         {
            ACTIVITY_UNDEF = 0,
            ACTIVITY_SITTING,
            ACTIVITY_STANDING,
            ACTIVITY_ENUM_END,
         };
      private:
         std::time_t focus_timer_started_at;
         float focus_timer_duration_sec;
         float warning_position_sec;

      protected:


      public:
         FocusTimerBar();
         ~FocusTimerBar();

         void set_focus_timer_started_at(std::time_t focus_timer_started_at);
         std::time_t get_focus_timer_started_at() const;
         float get_focus_timer_duration_sec() const;
         float get_warning_position_sec() const;
         float calc_warning_position_normalized();
         double calc_normalized_length();
         Hexagon::FocusTimerBar::FocusTimerBar::Activity infer_activity_type();
      };
   }
}






#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>

#include <cmath>


namespace Hexagon
{
namespace FocusTimerBar
{


FocusTimerBar::FocusTimerBar()
   : focus_timer_time_now(time(0))
   , focus_timer_duration_sec((60.0f * 30))
   , warning_position_sec((60.0f * 30.0f) - 300.0f)
{
}


FocusTimerBar::~FocusTimerBar()
{
}


void FocusTimerBar::set_focus_timer_time_now(std::time_t focus_timer_time_now)
{
   this->focus_timer_time_now = focus_timer_time_now;
}


std::time_t FocusTimerBar::get_focus_timer_time_now() const
{
   return focus_timer_time_now;
}


float FocusTimerBar::get_focus_timer_duration_sec() const
{
   return focus_timer_duration_sec;
}


float FocusTimerBar::get_warning_position_sec() const
{
   return warning_position_sec;
}


float FocusTimerBar::calc_warning_position_normalized()
{
   return warning_position_sec / focus_timer_duration_sec;
}

void FocusTimerBar::set_time_to_time_now()
{
   focus_timer_time_now = time(0);
}

double FocusTimerBar::calc_normalized_length()
{
   //std::time_t time_now = time(0);
   std::time_t time_now = focus_timer_time_now;
   struct tm now_tm = *localtime(&time_now);
   double seconds = difftime(time_now, mktime(0));
   double normal_length = std::fmod(seconds, focus_timer_duration_sec) / focus_timer_duration_sec;
   return normal_length;
}

Hexagon::FocusTimerBar::FocusTimerBar::Activity FocusTimerBar::infer_activity_type()
{
   //std::time_t time_now = time(0);
   std::time_t time_now = focus_timer_time_now;
   int num_activities = (ACTIVITY_ENUM_END - 1); 
   int activity = (int)(time_now / focus_timer_duration_sec) % num_activities + 1;
   return static_cast<Hexagon::FocusTimerBar::FocusTimerBar::Activity>(activity);
}

std::string FocusTimerBar::infer_activity_type_str()
{
   switch (infer_activity_type())
   {
      case ACTIVITY_SITTING: return "SITTING"; break;
      case ACTIVITY_STANDING: return "STANDING"; break;
      default: return "ACTIVITY_UNDEFINED"; break;
   }
}


} // namespace FocusTimerBar
} // namespace Hexagon



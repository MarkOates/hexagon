

#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>

#include <cmath>


namespace Hexagon
{
namespace FocusTimerBar
{


FocusTimerBar::FocusTimerBar()
   : focus_timer_started_at(0)
   , focus_timer_duration_sec((60.0f * 30))
   , warning_position_sec((60.0f * 30.0f) - 300.0f)
{
}


FocusTimerBar::~FocusTimerBar()
{
}


void FocusTimerBar::set_focus_timer_started_at(std::time_t focus_timer_started_at)
{
   this->focus_timer_started_at = focus_timer_started_at;
}


std::time_t FocusTimerBar::get_focus_timer_started_at() const
{
   return focus_timer_started_at;
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

double FocusTimerBar::calc_normalized_length()
{
   std::time_t time_now = time(0);
   struct tm now_tm = *localtime(&time_now);
   double seconds = difftime(time_now, mktime(0));
   double normal_length = std::fmod(seconds, focus_timer_duration_sec) / focus_timer_duration_sec;
   return normal_length;
}

Hexagon::FocusTimerBar::FocusTimerBar::Activity FocusTimerBar::infer_activity_type()
{
   int num_activities = (ACTIVITY_ENUM_END - 1); 
   int activity = (int)(focus_timer_started_at / focus_timer_duration_sec) % num_activities + 1;
   return static_cast<Hexagon::FocusTimerBar::FocusTimerBar::Activity>(activity);
}


} // namespace FocusTimerBar
} // namespace Hexagon



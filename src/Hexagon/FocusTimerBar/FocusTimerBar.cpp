

#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>




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




} // namespace FocusTimerBar
} // namespace Hexagon



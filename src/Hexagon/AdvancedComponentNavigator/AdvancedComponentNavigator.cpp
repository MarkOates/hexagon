

#include <Hexagon/AdvancedComponentNavigator/AdvancedComponentNavigator.hpp>
#include <Hexagon/AdvancedComponentNavigator/ComponentSearcher.hpp>
#include <Hexagon/ClipboardData.hpp>
#include <allegro_flare/useful_php.h>
#include <Hexagon/ClipboardData.hpp>


namespace Hexagon
{
namespace AdvancedComponentNavigator
{


AdvancedComponentNavigator::AdvancedComponentNavigator(std::string project_root)
   : project_root(project_root)
   , cursor_position(0)
   , cursor_position_static(false)
   , nodes({})
   , mode("navigating_list")
   , search_text("")
{
}


AdvancedComponentNavigator::~AdvancedComponentNavigator()
{
}


void AdvancedComponentNavigator::set_project_root(std::string project_root)
{
   this->project_root = project_root;
}


void AdvancedComponentNavigator::set_cursor_position_static(bool cursor_position_static)
{
   this->cursor_position_static = cursor_position_static;
}


void AdvancedComponentNavigator::set_nodes(std::vector<Blast::Project::Component> nodes)
{
   this->nodes = nodes;
}


void AdvancedComponentNavigator::set_mode(std::string mode)
{
   this->mode = mode;
}


void AdvancedComponentNavigator::set_search_text(std::string search_text)
{
   this->search_text = search_text;
}


std::string AdvancedComponentNavigator::get_project_root()
{
   return project_root;
}


int AdvancedComponentNavigator::get_cursor_position()
{
   return cursor_position;
}


bool AdvancedComponentNavigator::get_cursor_position_static()
{
   return cursor_position_static;
}


std::vector<Blast::Project::Component> AdvancedComponentNavigator::get_nodes()
{
   return nodes;
}


std::string AdvancedComponentNavigator::get_mode()
{
   return mode;
}


std::string AdvancedComponentNavigator::get_search_text()
{
   return search_text;
}


bool AdvancedComponentNavigator::is_mode_navigating_list()
{
   return this->mode == "navigating_list";
}

bool AdvancedComponentNavigator::is_mode_typing_in_search_bar()
{
   return this->mode == "typing_in_search_bar";
}

void AdvancedComponentNavigator::move_cursor_up()
{
   cursor_position -= 1;
}

void AdvancedComponentNavigator::move_cursor_down()
{
   cursor_position += 1;
}

void AdvancedComponentNavigator::move_cursor_to_top()
{
   cursor_position = 0;
}

bool AdvancedComponentNavigator::current_selection_is_valid()
{
   if (cursor_position < 0 || cursor_position >= nodes.size()) return false;
   return true;
}

void AdvancedComponentNavigator::set_mode_to_navigating_list()
{
   this->mode = "navigating_list";
}

void AdvancedComponentNavigator::set_mode_to_typing_in_search_bar()
{
   this->mode = "typing_in_search_bar";
}

std::string AdvancedComponentNavigator::get_current_selection_label_or_empty_string()
{
   if (!current_selection_is_valid()) return "";
   return nodes[get_cursor_position()].get_name();
}

void AdvancedComponentNavigator::refresh_list()
{
   Hexagon::AdvancedComponentNavigator::ComponentSearcher searcher(get_project_root(), search_text);
   nodes = searcher.components_sorted_by_most_recent();
}

void AdvancedComponentNavigator::yank_selected_text_label()
{
   std::string selected_text = get_current_selection_label_or_empty_string();
   ClipboardData::store(selected_text);
}

void AdvancedComponentNavigator::yank_selected_text_as_component_name()
{
   std::string selected_text = get_current_selection_label_or_empty_string();
   std::string filtered_text = php::str_replace("/", "::", selected_text);
   ClipboardData::store(filtered_text);
}
} // namespace AdvancedComponentNavigator
} // namespace Hexagon



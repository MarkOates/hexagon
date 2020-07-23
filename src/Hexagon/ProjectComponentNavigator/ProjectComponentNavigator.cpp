

#include <Hexagon/ProjectComponentNavigator/ProjectComponentNavigator.hpp>



namespace Hexagon
{
namespace ProjectComponentNavigator
{


ProjectComponentNavigator::ProjectComponentNavigator(std::string project_root)
   : project_root(project_root)
   , cursor_position(0)
   , cursor_position_static(false)
   , nodes({})
   , mode("navigating_list")
   , search_text("")
{
}


ProjectComponentNavigator::~ProjectComponentNavigator()
{
}


void ProjectComponentNavigator::set_project_root(std::string project_root)
{
   this->project_root = project_root;
}


void ProjectComponentNavigator::set_cursor_position_static(bool cursor_position_static)
{
   this->cursor_position_static = cursor_position_static;
}


void ProjectComponentNavigator::set_nodes(std::vector<Hexagon::Layout> nodes)
{
   this->nodes = nodes;
}


void ProjectComponentNavigator::set_mode(std::string mode)
{
   this->mode = mode;
}


void ProjectComponentNavigator::set_search_text(std::string search_text)
{
   this->search_text = search_text;
}


std::string ProjectComponentNavigator::get_project_root()
{
   return project_root;
}


int ProjectComponentNavigator::get_cursor_position()
{
   return cursor_position;
}


bool ProjectComponentNavigator::get_cursor_position_static()
{
   return cursor_position_static;
}


std::vector<Hexagon::Layout> ProjectComponentNavigator::get_nodes()
{
   return nodes;
}


std::string ProjectComponentNavigator::get_mode()
{
   return mode;
}


std::string ProjectComponentNavigator::get_search_text()
{
   return search_text;
}


bool ProjectComponentNavigator::is_mode_navigating_list()
{
return this->mode == "navigating_list";

}

bool ProjectComponentNavigator::is_mode_typing_in_search_bar()
{
return this->mode == "typing_in_search_bar";

}

void ProjectComponentNavigator::move_cursor_up()
{
cursor_position -= 1;

}

void ProjectComponentNavigator::move_cursor_down()
{
cursor_position += 1;

}

void ProjectComponentNavigator::move_cursor_to_top()
{
cursor_position = 0;

}

bool ProjectComponentNavigator::current_selection_is_valid()
{
if (cursor_position < 0 || cursor_position >= nodes.size()) return false;
return true;

}

void ProjectComponentNavigator::set_mode_to_navigating_list()
{
this->mode = "navigating_list";

}

void ProjectComponentNavigator::set_mode_to_typing_in_search_bar()
{
this->mode = "typing_in_search_bar";

}

std::string ProjectComponentNavigator::get_current_selection_label_or_empty_string()
{
if (!current_selection_is_valid()) return "";
return nodes[get_cursor_position()].get_concept_name();

}

void ProjectComponentNavigator::refresh_list()
{
return;

}
} // namespace ProjectComponentNavigator
} // namespace Hexagon


